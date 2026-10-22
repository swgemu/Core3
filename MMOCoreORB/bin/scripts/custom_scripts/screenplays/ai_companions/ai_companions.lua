-- AiCompanions: player-like NPCs that talk back (via the LLM sidecar), roam, "level up",
-- and can be recruited to follow and fight beside a player.
--
-- Chat bridge (no C++ needed, uses Lua io like other Core3 screenplays):
--   requests : log/ai_companions_requests.tsv   id \t botKey \t player \t level \t activity \t zone \t following \t message
--   responses: log/ai_companions_responses.tsv  id \t botKey \t text
-- tools/ai_companions_sidecar/sidecar.py reads requests and appends responses.

AiCompanions = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "AiCompanions",

	requestFile = "log/ai_companions_requests.tsv",
	responseFile = "log/ai_companions_responses.tsv",

	TICK_MS = 2000,            -- how often responses are polled and bots are updated
	REPLY_COOLDOWN_MS = 3000,  -- per-bot minimum time between LLM requests
	HEAR_RANGE = 25,           -- matches the server's spatial chat observer range
	OWNER_LOSE_RANGE = 200,    -- companion gives up following past this distance
	ASSIST_RANGE = 60,
	MAX_PARTY = 3,             -- most companions one player can have following at once

	nextRequestId = 1,
	responseOffset = 0,
	tickCount = 0,
	state = {},     -- botKey -> runtime state
	idToKey = {},   -- spawned object id -> botKey
	cfgByKey = {},  -- botKey -> config
	allBots = {},   -- hand-written bots below + generated roster (roster.lua)

	-- Add or edit bots here. Each needs a matching template in custom_scripts/mobile/ai_companions.lua
	-- and a persona of the same key in tools/ai_companions_sidecar/personas.json
	bots = {
		{
			key = "kessa", template = "ai_companion_kessa", name = "Kessa Vor",
			zone = "tatooine", x = 3535, z = 5, y = -4800, heading = 90, roam = 12, level = 38,
			activities = {"watching the crowd", "checking her blaster", "scanning the bounty board", "sharpening a vibroblade"},
			acks = {
				follow = {"Lead the way.", "Right behind you.", "Finally, some action."},
				stay = {"Holding here.", "I'll keep the seat warm.", "Waiting."},
				attack = {"Spotted. Engaging.", "I've got your back.", "On it."},
				dismiss = {"Call me when you need me.", "Back to the cantina, then."},
			},
		},
		{
			key = "dax", template = "ai_companion_dax", name = "Dax Morrow",
			zone = "tatooine", x = 3524, z = 5, y = -4808, heading = 200, roam = 8, level = 18,
			activities = {"haggling over spice prices", "counting his credits", "complaining about the heat", "polishing a trade ledger"},
			acks = {
				follow = {"Fine, fine, but you're buying.", "Lead on."},
				stay = {"I'll be right here, counting.", "Not going anywhere."},
				attack = {"Oh, if I must!", "Hope this pays well."},
				dismiss = {"Back to business, then.", "Good doing business."},
			},
		},
		{
			key = "jinx", template = "ai_companion_jinx", name = "Jinx Telaro",
			zone = "tatooine", x = 3544, z = 5, y = -4812, heading = 300, roam = 14, level = 12,
			activities = {"looking for a first big score", "practicing a fast draw", "eyeing the exits", "boasting about a run that never happened"},
			acks = {
				follow = {"Oh! Yes! Following! Coolly!", "Adventure! I mean... sure."},
				stay = {"Staying. Totally relaxed.", "I'll just... wait."},
				attack = {"Watch this!", "Got 'em!"},
				dismiss = {"Aw. Okay.", "See you around, boss."},
			},
		},
	},
}

registerScreenPlay("AiCompanions", true)

---------------------------------------------------------------------------
-- helpers
---------------------------------------------------------------------------
local function clean(s)
	s = tostring(s or "")
	s = string.gsub(s, "[\t\r\n]", " ")
	return s
end

local function pick(list)
	if list == nil or #list == 0 then return "" end
	return list[getRandomNumber(#list)]
end

local function hasWord(msg, words)
	for i = 1, #words do
		if string.find(msg, words[i], 1, true) then return true end
	end
	return false
end

function AiCompanions:botCfg(key)
	return self.cfgByKey[key]
end

function AiCompanions:getBot(key)
	local st = self.state[key]
	if st == nil or st.id == nil then return nil end
	local pBot = getSceneObject(st.id)
	if pBot == nil or not SceneObject(pBot):isAiAgent() or CreatureObject(pBot):isDead() then
		return nil
	end
	return pBot
end

---------------------------------------------------------------------------
-- lifecycle
---------------------------------------------------------------------------
function AiCompanions:start()
	-- skip any stale responses left over from before this boot
	local f = io.open(self.responseFile, "r")
	if f ~= nil then
		self.responseOffset = f:seek("end") or 0
		f:close()
	end

	-- merge hand-written bots with the generated roster; roster bots take their chat flavour from an archetype
	self.allBots = {}
	for i = 1, #self.bots do
		self.allBots[#self.allBots + 1] = self.bots[i]
	end
	if AiCompanionsRoster ~= nil then
		local seen = {}
		for i = 1, #self.bots do seen[self.bots[i].key] = true end
		for i = 1, #AiCompanionsRoster.bots do
			local b = AiCompanionsRoster.bots[i]
			local arch = AiCompanionsRoster.archetypes[b.arch]
			if arch ~= nil and not seen[b.key] then
				seen[b.key] = true
				b.activities, b.acks, b.customName = arch.activities, arch.acks, b.name
				self.allBots[#self.allBots + 1] = b
			end
		end
	end

	for i = 1, #self.allBots do
		local cfg = self.allBots[i]
		self.cfgByKey[cfg.key] = cfg
		self.state[cfg.key] = {
			id = nil, mode = "roam", owner = nil,
			level = cfg.level, xp = 0, activity = pick(cfg.activities),
			lastRequest = 0, quietTicks = 0,
		}
		if isZoneEnabled(cfg.zone) then
			self:spawnBot(cfg)
		end
	end

	createEvent(self.TICK_MS, "AiCompanions", "tick", nil, "")
end

function AiCompanions:spawnBot(cfg)
	local pBot = spawnMobile(cfg.zone, cfg.template, 0, cfg.x, cfg.z, cfg.y, cfg.heading, 0)
	if pBot == nil then
		printf("AiCompanions: failed to spawn %s\n", cfg.key)
		return
	end

	local st = self.state[cfg.key]
	if st.id ~= nil then self.idToKey[st.id] = nil end
	st.id = SceneObject(pBot):getObjectID()
	self.idToKey[st.id] = cfg.key
	st.mode = "roam"
	st.owner = nil

	-- roster bots share archetype templates, so the individual name is applied here
	if cfg.customName ~= nil then
		CreatureObject(pBot):setCustomObjectName(cfg.customName)
	end

	AiAgent(pBot):setHomeLocation(cfg.x, cfg.z, cfg.y, 0)
	createObserver(SPATIALCHAT, "AiCompanions", "onChat", pBot)
end

---------------------------------------------------------------------------
-- hearing players
---------------------------------------------------------------------------
-- Observer callback. Return 0 to stay registered, 1 to drop the observer.
function AiCompanions:onChat(pBot, pChatMessage, playerID)
	if pBot == nil or pChatMessage == nil then return 1 end
	if SceneObject(pBot):getObjectID() == playerID then return 0 end

	local pPlayer = getSceneObject(playerID)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then return 0 end

	local key = self:keyForBot(SceneObject(pBot):getObjectID())
	if key == nil then return 0 end
	local cfg, st = self:botCfg(key), self.state[key]

	local raw = getChatMessage(pChatMessage)
	local msg = string.lower(raw or "")
	local firstName = string.lower(string.match(cfg.name, "^(%S+)"))
	-- whole-word match so short names ("Una", "Nia") don't fire on words like "fun" or "tennis"
	local addressed = string.find(msg, "%f[%a]" .. firstName .. "%f[%A]") ~= nil
	local isOwner = (st.owner == playerID)

	-- only react if spoken to by name, or spoken to by our current partner
	if not addressed and not isOwner then return 0 end

	if self:handleCommand(cfg, st, pBot, pPlayer, playerID, msg, isOwner) then
		return 0
	end

	self:requestReply(cfg, st, pBot, pPlayer, raw)
	return 0
end

function AiCompanions:keyForBot(botID)
	return self.idToKey[botID]
end

function AiCompanions:partySize(playerID)
	local n = 0
	for _, st in pairs(self.state) do
		if st.owner == playerID then n = n + 1 end
	end
	return n
end

local FOLLOW_WORDS  = {"follow me", "come with me", "come along", "let's go", "lets go", "join me", "join us", "adventure", "tag along"}
local STAY_WORDS    = {"stay", "wait here", "hold here", "hold position", "stop following"}
local DISMISS_WORDS = {"go home", "dismissed", "you can go", "go back", "see you later", "farewell", "goodbye"}
local ATTACK_WORDS  = {"attack", "assist", "help me fight", "kill that", "get 'em", "get em"}

function AiCompanions:handleCommand(cfg, st, pBot, pPlayer, playerID, msg, isOwner)
	-- Someone else's companion: only chat with them, don't take orders.
	if st.owner ~= nil and not isOwner then return false end

	if hasWord(msg, FOLLOW_WORDS) then
		if not isOwner and self:partySize(playerID) >= self.MAX_PARTY then
			spatialChat(pBot, "You've got a crowd already. Maybe next time.")
			return true
		end
		st.owner = playerID
		st.mode = "follow"
		self:applyFollow(pBot, pPlayer)
		spatialChat(pBot, pick(cfg.acks.follow))
		return true
	elseif isOwner and hasWord(msg, DISMISS_WORDS) then
		self:release(cfg, st, pBot)
		spatialChat(pBot, pick(cfg.acks.dismiss))
		return true
	elseif isOwner and hasWord(msg, STAY_WORDS) then
		st.mode = "stay"
		self:clearFollow(pBot)
		spatialChat(pBot, pick(cfg.acks.stay))
		return true
	elseif isOwner and hasWord(msg, ATTACK_WORDS) then
		if self:assist(pBot, pPlayer) then
			spatialChat(pBot, pick(cfg.acks.attack))
		else
			spatialChat(pBot, "Show me a target first.")
		end
		return true
	end
	return false
end

---------------------------------------------------------------------------
-- movement / combat
---------------------------------------------------------------------------
function AiCompanions:applyFollow(pBot, pPlayer)
	-- same pattern the server uses for escorted NPCs (ThemeParkLogic:followPlayer)
	AiAgent(pBot):removeObjectFlag(AI_STATIONARY)
	AiAgent(pBot):addObjectFlag(AI_FOLLOW)
	AiAgent(pBot):addObjectFlag(AI_ESCORT)
	AiAgent(pBot):setFollowObject(pPlayer)
	AiAgent(pBot):setAITemplate()
	AiAgent(pBot):setMovementState(AI_FOLLOWING)
end

function AiCompanions:clearFollow(pBot)
	AiAgent(pBot):setFollowObject(nil)
	AiAgent(pBot):removeObjectFlag(AI_FOLLOW)
	AiAgent(pBot):removeObjectFlag(AI_ESCORT)
	AiAgent(pBot):clearPatrolPoints()
	AiAgent(pBot):setAITemplate()
end

function AiCompanions:release(cfg, st, pBot)
	st.owner = nil
	st.mode = "roam"
	self:clearFollow(pBot)
	AiAgent(pBot):setNextPosition(cfg.x, getTerrainHeight(pBot, cfg.x, cfg.y), cfg.y, 0)
end

-- Make the bot attack whatever its owner is fighting. Returns true if it found a target.
function AiCompanions:assist(pBot, pPlayer)
	local targetID = CreatureObject(pPlayer):getTargetID()
	if targetID == nil or targetID == 0 then return false end

	local pTarget = getSceneObject(targetID)
	if pTarget == nil or not SceneObject(pTarget):isCreatureObject() then return false end
	if SceneObject(pTarget):isPlayerCreature() then return false end -- never auto-attack players
	if CreatureObject(pTarget):isDead() then return false end

	AiAgent(pBot):setDefender(pTarget)
	return true
end

---------------------------------------------------------------------------
-- LLM bridge
---------------------------------------------------------------------------
function AiCompanions:requestReply(cfg, st, pBot, pPlayer, rawMsg)
	local now = getTimestampMilli()
	if now - st.lastRequest < self.REPLY_COOLDOWN_MS then return end
	st.lastRequest = now

	local msg = string.sub(clean(rawMsg), 1, 200)
	local id = self.nextRequestId
	self.nextRequestId = id + 1

	local f = io.open(self.requestFile, "a")
	if f == nil then
		printf("AiCompanions: cannot open %s (does the log/ directory exist?)\n", self.requestFile)
		return
	end
	f:write(string.format("%d\t%s\t%s\t%d\t%s\t%s\t%d\t%s\n",
		id, cfg.key,
		clean(CreatureObject(pPlayer):getFirstName()),
		st.level, clean(st.activity), cfg.zone,
		(st.mode == "follow") and 1 or 0,
		msg))
	f:close()
end

function AiCompanions:pollResponses()
	local f = io.open(self.responseFile, "r")
	if f == nil then return end
	f:seek("set", self.responseOffset)
	local chunk = f:read("*a")
	f:close()
	if chunk == nil or chunk == "" then return end

	-- only consume complete lines; a half-written line waits for the next tick
	local lastNewline = nil
	local idx = 0
	while true do
		idx = string.find(chunk, "\n", idx + 1, true)
		if idx == nil then break end
		lastNewline = idx
	end
	if lastNewline == nil then return end

	local complete = string.sub(chunk, 1, lastNewline)
	self.responseOffset = self.responseOffset + lastNewline

	for line in string.gmatch(complete, "([^\n]*)\n") do
		local _, key, text = string.match(line, "^([^\t]*)\t([^\t]*)\t(.*)$")
		if key ~= nil and text ~= nil and text ~= "" then
			local pBot = self:getBot(key)
			if pBot ~= nil then
				spatialChat(pBot, string.sub(text, 1, 250))
			end
		end
	end
end

---------------------------------------------------------------------------
-- world tick: replies, respawns, roaming, "levelling", assist
---------------------------------------------------------------------------
function AiCompanions:tick()
	self.tickCount = self.tickCount + 1
	self:pollResponses()

	for i = 1, #self.allBots do
		local cfg = self.allBots[i]
		local st = self.state[cfg.key]
		local pBot = self:getBot(cfg.key)

		if pBot == nil then
			-- dead or despawned: respawn at home roughly every 60s (staggered per bot)
			if isZoneEnabled(cfg.zone) and (self.tickCount + i) % 30 == 0 then
				st.owner, st.mode = nil, "roam"
				self:spawnBot(cfg)
			end
		else
			self:tickBot(cfg, st, pBot, i)
		end
	end

	createEvent(self.TICK_MS, "AiCompanions", "tick", nil, "")
end

function AiCompanions:tickBot(cfg, st, pBot, index)
	local phase = self.tickCount + index -- staggers work across bots so they don't all act on the same tick

	if st.owner ~= nil then
		local pOwner = getSceneObject(st.owner)
		local lost = (pOwner == nil)
			or SceneObject(pBot):getDistanceTo(pOwner) > self.OWNER_LOSE_RANGE
			or CreatureObject(pOwner):isDead()
		if lost then
			spatialChat(pBot, "Lost you. Heading back.")
			self:release(cfg, st, pBot)
			return
		end

		-- auto-assist whatever the owner is fighting
		if st.mode == "follow" and CreatureObject(pOwner):isInCombat() and not CreatureObject(pBot):isInCombat()
			and SceneObject(pBot):getDistanceTo(pOwner) < self.ASSIST_RANGE then
			self:assist(pBot, pOwner)
		end
		return
	end

	-- ambient life: every ~20s pick a new activity, wander, earn "xp" and occasionally level up
	if phase % 10 == 0 then
		st.activity = pick(cfg.activities)
		st.xp = st.xp + getRandomNumber(5, 20)
		if st.xp >= st.level * 40 then
			st.xp = 0
			st.level = st.level + 1
			spatialChat(pBot, "Finally hit level " .. st.level .. "!")
		end
	end

	if phase % 5 == 0 and AiAgent(pBot):getPatrolPointsSize() == 0 and getRandomNumber(100) <= 60 then
		local nx = cfg.x + getRandomNumber(-cfg.roam, cfg.roam)
		local ny = cfg.y + getRandomNumber(-cfg.roam, cfg.roam)
		AiAgent(pBot):setNextPosition(nx, getTerrainHeight(pBot, nx, ny), ny, 0)
	end
end
