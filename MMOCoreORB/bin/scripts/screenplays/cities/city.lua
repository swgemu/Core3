CityScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityScreenPlay",

	planet = "",

	gcwMobs = {},
}

function CityScreenPlay:spawnGcwMobiles()
	if (isZoneEnabled(self.planet)) then
		local controllingFaction = getControllingFaction(self.planet)

		for i = 1, #self.gcwMobs do
			self:spawnMob(i, controllingFaction)
		end
	end
end

function CityScreenPlay:spawnMob(num, controllingFaction)
	local mobsTable = self.gcwMobs

	if num <= 0 or num > #mobsTable then
		return
	end

	local mobTable = mobsTable[num]
	local pNpc = nil
	local npcTemplate = ""
	local npcMood = ""

	if controllingFaction == FACTIONIMPERIAL then
		npcTemplate = mobTable[1]
		npcMood = mobTable[8]
	elseif controllingFaction == FACTIONREBEL then
		npcTemplate = mobTable[2]
		npcMood = mobTable[9]
	end

	pNpc = spawnMobile(self.planet, npcTemplate, 0, mobTable[3], mobTable[4], mobTable[5], mobTable[6], mobTable[7])

	if pNpc ~= nil and npcMood ~= "" then
		self:setMoodString(pNpc, npcMood)
	end

	if pNpc ~= nil then
		createObserver(CREATUREDESPAWNED, self.screenplayName, "onDespawn", pNpc)
		writeData(SceneObject(pNpc):getObjectID(), num)
		writeData(self.planet .. self.screenplayName .. num, SceneObject(pNpc):getObjectID())
	end
end

function CityScreenPlay:onDespawn(pAiAgent)
	if pAiAgent == nil or not SceneObject(pAiAgent):isAiAgent() then
		printf("pAiAgent is nil or not an AiAgent")
		return
	end

	local oid = SceneObject(pAiAgent):getObjectID()
	local mobNumber = readData(oid)
	deleteData(oid)

	local controllingFaction = getControllingFaction(self.planet)

	local args = mobNumber .. "," .. controllingFaction
	createEvent(300000, self.screenplayName, "respawn", nil, args)

	return 1
end

function CityScreenPlay:respawn(pAiAgent, args)
	local mobNumber = 0
	local controllingFaction = 0
	local comma = string.find(args, ",")

	if comma ~= nil then
		mobNumber = tonumber(string.sub(args, 1, comma - 1))
		controllingFaction = tonumber(string.sub(args, comma + 1))
		self:spawnMob(mobNumber, controllingFaction)
	end
end
