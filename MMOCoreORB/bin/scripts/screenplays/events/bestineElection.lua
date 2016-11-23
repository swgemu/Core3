local ObjectManager = require("managers.object.object_manager")

BESTINE_ELECTION_ENABLED = 0

BestineElectionScreenPlay = ScreenPlay:new {
	CAMPAIGN_TIME = 24 * 60 * 60 * 1000,
	TUNE_TIME = 24 * 60  * 60 * 1000, -- 24 hours (TUNE = Time Until Next Election) Phase 2

	seanEvidence = {"object/tangible/loot/quest/sean_questp_ctestimony.iff", "object/tangible/loot/quest/sean_questp_mdisk.iff", "object/tangible/loot/quest/sean_questp_htestimony.iff"},
	victorEvidence = {"object/tangible/loot/quest/victor_questp_testimony.iff", "object/tangible/loot/quest/victor_questp_jregistry.iff", "object/tangible/loot/quest/victor_questp_receipt.iff"},

	candidates = {"victor", "sean"},

	electionMobiles = {
		{ template = "sean_trenwell", x = 19.46, z = 3.22, y = -35.97, direction = 10, cellID=926483, moodString = "neutral", breech = 0},
		{ template = "victor_visalis", x = -26.48, z = 3.23, y = 20.29, direction = 146, cellID = 926480, moodString = "neutral", breech = 0},
		{ template = "tour_aryon", x = -37.31, z = 1.29, y = 0.71, direction = -125, cellID = 926479, moodString = "neutral", breech = 10},

		{ template = "indigo_siyan", x = 24.64, z = 3.22, y = -30.71, direction = 341.212, cellID = 926483, moodString = "neutral", breech = 0},
		{ template = "keanna_likyna", x = -18.88, z = 3.22, y = 20.6, direction = 214.006, cellID = 926480, moodString = "neutral", breech = 0},

		{ template = "victor_questn_capitol", x = 6.1, z = 0.3, y = -0.49,direction = 96.7754, cellID = 926475, moodString = "npc_imperial", breech = 4},
		{ template = "victor_questn_cantina", x = 3.1, z = -0.9, y = 22.6, direction = 179, cellID = 1028651, moodString = "npc_sitting_chair", breech = 0},
		{ template = "victor_questp_slums", x= -1357, z=26, y=-3871, direction = -108, cellID=0, moodString = "neutral", breech = 4},

		{ template = "sean_questp_house", x = 3.0, z = .4, y = -0.2, direction = -111, cellID = 1528397, moodString = "neutral", breech = 4},
		{ template = "victor_questp_hospital", x = -1294, z = 12, y = -3500, direction = 45, cellID = 0, moodString = "neutral", breech = 4},
		{ template = "sean_questp_market", x = -1104, z = 12, y = -3705, direction = 20, cellID = 0, moodString = "neutral", breech = 4},
		{ template = "sean_questn_university", x = 3.6, z = 1.1, y = -4.6, direction = 0, cellID = 1028578, moodString = "neutral", breech = 8},

		{ template = "sean_contact_quest", x = -1448, z = 10, y = -3765, direction = 0, cellID = 0, moodString = "neutral", breech = 4},
		{ template = "seans_historian", x = -758, z = 10.5, y = -3907, direction = 0, cellID = 0, moodString = "neutral", breech = 4},
		--Rumor Mobiles
		{ template = "bestine_rumor01", x = -1095.68, z = 12, y = -3640.98, direction = 281, cellID=0, moodString = "neutral", breech = 6},
		{ template = "bestine_rumor02", x = -1205, z = 12, y = -3539, direction = 80, cellID=0, moodString = "neutral", breech = 6},
		{ template = "bestine_rumor03", x = -1211, z = 12, y = -3637.48, direction = 26, cellID=0, moodString = "neutral", breech = 4},
		{ template = "bestine_rumor04", x = -1145.53, z = 12, y = -3656.31, direction = 21, cellID=0, moodString = "neutral", breech = 6},
		{ template = "bestine_rumor05", x = -1013, z = 12, y = -3695, direction = 233, cellID=0, moodString = "neutral", breech = 6},
		{ template = "bestine_rumor06", x = -1088, z = 12, y = -3656, direction = 201, cellID=0, moodString = "neutral", breech = 4},
		{ template = "bestine_rumor07", x = -1048, z = 12, y = -3699, direction = 53, cellID=0, moodString = "neutral", breech = 4},
		{ template = "bestine_rumor08", x = -1174, z = 12, y = -3635.8, direction = 221, cellID=0, moodString = "neutral", breech = 4},
		{ template = "bestine_rumor09", x = 0.69, z = 0.5, y = -2.4 , direction = -107, cellID=1028169, moodString = "neutral", breech = 4},
		{ template = "bestine_rumor10", x = -1106.31, z = 14, y = -3697.59, direction = -177, cellID=0, moodString = "neutral", breech = 4},
		{ template = "bestine_rumor11", x = -1221, z = 12, y = -3650, direction = -49, cellID=0, moodString = "neutral", breech = 4},
		{ template = "bestine_rumor12", x = -1291, z = 12, y = -3634, direction = 301, cellID=0, moodString = "neutral", breech = 6},
		--Capitol Building NPCs
		{ template = "bestine_capitol01", x = -0.7, z = 3.22, y = 21.1, direction = 187, cellID=926474, moodString = "neutral", breech = 4},
		{ template = "bestine_capitol02", x = -23.29, z = 1.3, y = -10.39, direction = 234, cellID=926475, moodString = "neutral", breech = 4},
		{ template = "bestine_capitol03", x = -3.78, z = 2.27, y = -25.85, direction = 158, cellID=926475, moodString = "neutral", breech = 4},
		{ template = "bestine_capitol04", x = 2.26, z = 7.9, y = -37.38, direction = 304, cellID=926476, moodString = "neutral", breech = 4},
	},

	seanMerchants = {
		{template = "bestine_merchant", x = -1135.28, z = 12, y = -3688.03, direction = 61},
		{template = "bestine_merchant", x = -1136.64, z =  12, y =  -3667.40, direction = -175},
		{template = "bestine_merchant", x = -1115.29, z =  12, y =  -3709.47, direction = 7},
		{template = "bestine_merchant", x = -1133.53, z =  12, y =  -3693.98, direction = 90},
		{template = "bestine_stone_merchant", x = -1127, z =  12, y =  -3674, direction = -110},
	}
}

registerScreenPlay("BestineElectionScreenPlay", true)

function BestineElectionScreenPlay:tableHas(t, el)
	for _,v in pairs(t) do
		if v == el then return true end
	end

	return false
end

function BestineElectionScreenPlay:parseString(str, pat)
	local t = {}
	local fpat = "(.-)" .. pat
	local last_end = 1
	local s, e, cap = str:find(fpat, 1)

	while s do
		if s ~= 1 or cap ~= "" then
			table.insert(t,cap)
		end
		last_end = e+1
		s, e, cap = str:find(fpat, last_end)
	end

	if last_end <= #str then
		cap = str:sub(last_end)
		table.insert(t, cap)
	end

	return t
end

function BestineElectionScreenPlay:isElectionEnabled()
	if (BESTINE_ELECTION_ENABLED == 1) then
		return true
	end
	return false
end

function BestineElectionScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:setupTerminals()
		self:doPhaseInit()
	end
end

function BestineElectionScreenPlay:spawnMobiles()
	for i = 1, #self.electionMobiles do
		local npcData = self.electionMobiles[i]
		local pNpc = spawnMobile("tatooine", npcData.template, 60, npcData.x, npcData.z, npcData.y, npcData.direction, npcData.cellID)
		if (pNpc ~= nil) then
			self:setMoodString(pNpc, npcData.moodString)

			if (self:isElectionEnabled()) then
				if npcData.template == "tour_aryon" then
					SceneObject(pNpc):setContainerComponent("TourContainerComponent")
				end

				if npcData.breech > 0 then
					local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pNpc):getWorldPositionX(), SceneObject(pNpc):getWorldPositionZ(), SceneObject(pNpc):getWorldPositionY(), npcData.breech, 0)
					if pActiveArea ~= nil then
						local areaID = SceneObject(pActiveArea):getObjectID()
						writeData(areaID .. ":OwnerID", SceneObject(pNpc):getObjectID())
						createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "spawnApproach", pActiveArea)
					end
				end
			end
		end
	end

	--Hutt informant quest for Sean
	local pNpc = spawnMobile("tatooine", "hutt_informant_quest", 1, -1120, 12,-3639, 160, 0)
	if (pNpc ~= nil and self:isElectionEnabled()) then
		writeData("bestine_election:hutt_informant", SceneObject(pNpc):getObjectID())
		local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", -1120, 12, -3639, 15,0)
		if pActiveArea ~= nil then
			createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "informantApproach", pActiveArea)
		end
	end

	local electionWinner = getQuestStatus("bestine_election:electionWinner")
	if electionWinner == "sean" then
		self:spawnMerchants()
	end
end

function BestineElectionScreenPlay:spawnApproach(pActiveArea, pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isPlayerCreature()) then
		return 0
	end

	local pNpc = getSceneObject(readData(SceneObject(pActiveArea):getObjectID() .. ":OwnerID"))
	if (pNpc ~= nil) then
		SceneObject(pNpc):faceObject(pMovingObject, true)
	end

	return 0
end

function BestineElectionScreenPlay:informantApproach(pActiveArea, pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isPlayerCreature()) then
		return 0
	end

	local pInformant = getSceneObject(readData("bestine_election:hutt_informant"))
	if (pInformant ~= nil) then
		local pInventory = CreatureObject(pMovingObject):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true) ~= nil) then
				SceneObject(pInformant):faceObject(pMovingObject, true)
				spatialChat(pInformant, "@bestine:come_here") -- Hey... c'mere a second. I think we can help one another.
			end
		end
	end
	return 0
end

function BestineElectionScreenPlay:spawnMerchants()
	for i = 1, #self.seanMerchants do
		local npcData = self.seanMerchants[i]
		local pNpc = spawnMobile("tatooine", npcData.template, 0, npcData.x, npcData.z, npcData.y, npcData.direction, 0)
		if (pNpc ~= nil) then
			local mobileID = SceneObject(pNpc):getObjectID()
			writeData("bestine_election:merchants:" .. i, mobileID)
		end
	end

	local pSnd = spawnSceneObject("tatooine", "object/soundobject/soundobject_marketplace_large.iff", -1124, 12, -3695, 0, 0)
	if (pSnd ~= nil) then
		local mobileID = SceneObject(pSnd):getObjectID()
		writeData("bestine_election:merchants:marketsound", mobileID)
	end
end

function BestineElectionScreenPlay:despawnMerchants()
	for i = 1, #self.seanMerchants do
		local objectID = readData("bestine_election:merchants:" .. i)
		local pMobile = getSceneObject(objectID)
		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
			deleteData("bestine_election:merchants:" .. i)
		end
	end

	local marketSoundID = readData("bestine_election:merchants:marketsound")
	local pSnd = getSceneObject(marketSoundID)
	if (pSnd ~= nil) then
		SceneObject(pSnd):destroyObjectFromWorld()
		deleteData("bestine_election:merchants:object:marketsound")
	end
end

function BestineElectionScreenPlay:setupTerminals()
	if (not self:isElectionEnabled()) then
		return
	end

	local pTerminal = getSceneObject(5565564) --terminal in victors office gives object/tangible/loot/quest/victor_questp_jregistry.iff
	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionTerminalMenuComponent")
		writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "victor_questp_jregistry")
	end

	pTerminal = getSceneObject(4475517) --4475517 victors desk - gives object/tangible/loot/quest/victor_questn_journal.iff
	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionDeskMenuComponent")
		writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "victor_questn_journal")
	end

	pTerminal = getSceneObject(5565563) --terminal in seans office gives "object/tangible/loot/quest/sean_questn_tdisk.iff"
	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionTerminalMenuComponent")
		writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "sean_questn_tdisk")
	end

	pTerminal = getSceneObject(5565562) --desk in seans office gives "object/tangible/loot/quest/sean_questn_alog.iff"
	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionDeskMenuComponent")
		writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "sean_questn_alog")
	end

	pTerminal = getSceneObject(3195507)
	local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pTerminal):getWorldPositionX(), SceneObject(pTerminal):getWorldPositionZ(), SceneObject(pTerminal):getWorldPositionY(), 2, 0)
	if pActiveArea ~= nil then
		createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "triggerHistoryTerminal", pActiveArea)
	end
end

function BestineElectionScreenPlay:triggerHistoryTerminal(pActiveArea, pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isPlayerCreature()) then
		return 0
	end

	if CreatureObject(pMovingObject):hasScreenPlayState(4, "bestine_history_quest") then
		CreatureObject(pMovingObject):sendSystemMessage("@city/bestine/terminal_items:history_disk_found_already") -- You search the area, but find nothing else of interest.
		return 0
	end

	if CreatureObject(pMovingObject):hasScreenPlayState(2, "bestine_history_quest") then
		local pInventory = CreatureObject(pMovingObject):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pDisk = giveItem(pInventory,"object/tangible/loot/quest/sean_history_disk.iff", -1)
			if (pDisk == nil) then
				CreatureObject(pMovingObject):sendSystemMessage("Error: Unable to generate item:sean_history_disk.iff")
				return 0
			end
			CreatureObject(pMovingObject):sendSystemMessage("@city/bestine/terminal_items:history_disk_found") -- As you approach the terminal, you notice something sticking out of a dataslot and you take it. The object appears to be an aged datadisk, but it looks like it might still be readable
			CreatureObject(pMovingObject):removeScreenPlayState(2, "bestine_history_quest")
			CreatureObject(pMovingObject):setScreenPlayState(4, "bestine_history_quest")
		end
	end

	return 0
end

function BestineElectionScreenPlay:createEvent(duration)
	createServerEvent(duration, "BestineElectionScreenPlay", "doPhaseChange", "ElectionPhaseChange")
end

function BestineElectionScreenPlay:doPhaseInit()
	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return
	end

	local phase = tonumber(getQuestStatus("bestine_election:currentPhase"))
	if (phase == nil) then
		setQuestStatus("bestine_election:currentPhase", 1)
	end

	if (not hasServerEvent("ElectionPhaseChange")) then
		BestineElectionScreenPlay:createEvent(self.CAMPAIGN_TIME)
	end
end

function BestineElectionScreenPlay:doPhaseChange()
	if (not self:isElectionEnabled()) then
		return
	end

	local electionNum = self:getElectionNumber()
	local currentPhase = self:getCurrentPhase()

	if (currentPhase == 1) then
		setQuestStatus("bestine_election:currentPhase", 2)
		self:determineWinner()
		if (not hasServerEvent("ElectionPhaseChange")) then
			self:createEvent(self.TUNE_TIME)
		end
	else
		setQuestStatus("bestine_election:currentPhase", 1)
		if (not hasServerEvent("ElectionPhaseChange")) then
			self:createEvent(self.CAMPAIGN_TIME)
			electionNum = electionNum + 1
			setQuestStatus("bestine_election:election_num", electionNum)
			removeQuestStatus("bestine_election:votesForSean")
			removeQuestStatus("bestine_election:votesForVictor")
			setQuestStatus("bestine_election:votesForsean", 0)
			setQuestStatus("bestine_election:votesForvictor", 0)
		end
	end
	printf("[BestineElection] Initiating phase change: Phase " .. getQuestStatus("bestine_election:currentPhase") .. ", Election Number: " .. getQuestStatus("bestine_election:election_num") .. "\n")
end

function BestineElectionScreenPlay:getCurrentPhase()
	return tonumber(getQuestStatus("bestine_election:currentPhase"))
end

function BestineElectionScreenPlay:getElectionNumber()
	local electionNum = tonumber(getQuestStatus("bestine_election:election_num"))

	if (electionNum == nil) then
		electionNum = 1
		setQuestStatus("bestine_election:election_num", electionNum)
	end

	return electionNum
end

function BestineElectionScreenPlay:getPhaseTimeLeft()
	local eventID = getServerEventID("ElectionPhaseChange")
	if (eventID == nil) then
		return 0
	end

	return getServerEventTimeLeft(eventID) / 1000
end

function BestineElectionScreenPlay:determineWinner()
	local votesForSean = tonumber(getQuestStatus("bestine_election:votesForsean"))
	if (votesForSean == nil) then
		votesForSean = 0
	end

	local votesForVictor = tonumber(getQuestStatus("bestine_election:votesForvictor"))
	if (votesForVictor == nil) then
		votesForVictor = 0
	end

	local electionWinner = ""

	if (votesForSean > votesForVictor) then
		electionWinner = "sean"
	elseif (votesForSean < votesForVictor) then
		electionWinner = "victor"
	else
		local chance = getRandomNumber(1, 2)
		if (chance == 1) then
			electionWinner = "sean"
		else
			electionWinner = "victor"
		end
	end

	if electionWinner == "sean" then
		self:spawnMerchants()
		-- TODO: remove some imperial guards
	elseif electionWinner == "victor" then
		self:despawnMerchants()
		-- TODO:--spawn more imperials
		-- TODO: start bestine raid script
	end

	setQuestStatus("bestine_election:electionWinner", electionWinner)
end

function BestineElectionScreenPlay:joinedCampaign(pPlayer, who)
	if (pPlayer ~= nil)  then
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", who .. "Campaign"))

		if (playerCampaign ~= nil) then
			local electionNum = self:getElectionNumber()
			return (playerCampaign >= electionNum)
		end
	end

	return false
end

function BestineElectionScreenPlay:votedCurrentElection(pPlayer, who)
	if (pPlayer ~= nil)  then
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "voted" .. who))

		if (playerCampaign ~= nil) then
			local electionNum = self:getElectionNumber()
			return (playerCampaign == electionNum)
		end
	end
	return false
end


function BestineElectionScreenPlay:votingrewardCheck(pPlayer,who)
	if (pPlayer ~= nil) then
		local electionNum =  self:getElectionNumber()
		if (self:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "voted" .. who))
		if (playerCampaign ~= nil) then
			if (playerCampaign == electionNum) then
				return true
			end
		end
	end
	return false
end

function BestineElectionScreenPlay:hasVoted(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	if self:votedCurrentElection(pPlayer, "sean") or self:votedCurrentElection(pPlayer, "victor") then
		return true
	end

	return false
end

function BestineElectionScreenPlay:canVote(pPlayer, who)
	if (pPlayer == nil) or (self:hasVoted(pPlayer)) then
		return false
	end

	local templates = {}

	if self:joinedCampaign(pPlayer, who) then
		if who == "sean" then
			templates = self.seanEvidence
		elseif who == "victor" then
			templates = self.victorEvidence
		end

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			for i = 1, # templates do
				local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)
				if pInvItem ~= nil then
					return true
				end
			end
		end
	end

	return false
end

function BestineElectionScreenPlay:castVote(pPlayer, who)
	if (pPlayer ~= nil)  then
		local votes = tonumber(getQuestStatus("bestine_election:votesFor" .. who))
		if (votes == nil) then
			votes = 0
		end

		votes = votes + 1
		setQuestStatus("bestine_election:votesFor" .. who, votes)

		local electionNum = self:getElectionNumber()
		if who == "sean" then
			writeScreenPlayData(pPlayer, "BestineElection", "votedsean", electionNum)
		elseif who == "victor" then
			writeScreenPlayData(pPlayer, "BestineElection", "votedvictor", electionNum)
		end

		self:removeEvidence(pPlayer, who)
		self:clearPoliticianData(pPlayer)
	end
end

function BestineElectionScreenPlay:removeEvidence(pPlayer, who)
	if (pPlayer ~= nil) then
		local templates = { }
		if who == "sean" then
			templates = self.seanEvidence
		elseif who == "victor" then
			templates = self.victorEvidence
		end

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			for i = 1, # templates do
				local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)
				if pInvItem ~= nil then
					SceneObject(pInvItem):destroyObjectFromWorld()
					SceneObject(pInvItem):destroyObjectFromDatabase()
				end
			end
		end
	end
end

function BestineElectionScreenPlay:clearPoliticianData(pPlayer)
	deleteScreenPlayData(pPlayer, "BestineElection", "seanCampaign")
	deleteScreenPlayData(pPlayer, "BestineElection", "victorCampaign")
	deleteScreenPlayData(pPlayer, "BestineElection", "seanNegQuest")
	deleteScreenPlayData(pPlayer, "BestineElection", "victorNegQuest")
	deleteScreenPlayData(pPlayer, "BestineElection", "questp_term_searched")
	deleteScreenPlayData(pPlayer, "BestineElection", "questp_desk_searched")

	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:university_noroom")
	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:house_noroom")
	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:market_noroom")
	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:sean_noroom")
	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:victor_noroom")
	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:cantina_noroom")
	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:capitol_noroom")
	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:hospital_noroom")
	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:slums_noroom")
	deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:museum_noroom")
end

function BestineElectionScreenPlay:hasFullInventory(pPlayer)
	if (pPlayer == nil) then
		return true
	end
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
	return (pInventory == nil) or SceneObject(pInventory):isContainerFullRecursive()
end

function BestineElectionScreenPlay:noroomReturned(pPlayer, quest)
	if (pPlayer == nil or quest == "") then
		return false
	end

	local electionNum = self:getElectionNumber()
	local playerCampaign = readData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:" .. quest .. "_noroom")

	if (playerCampaign ~= nil) then
		return (playerCampaign == electionNum)
	end

	return false
end

function BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, who)
	if (pPlayer ~= nil) then
		if self:votedCurrentElection(pPlayer, who) then
			return false
		end

		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", who .. "NegQuest"))

		if (playerCampaign ~= nil) then
			return (playerCampaign == electionNum)
		end
	end

	return false
end

function BestineElectionScreenPlay:canSearch(pSceneObject, pPlayer)
	if (pPlayer == nil or pSceneObject == nil) then
		return false
	end

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = self:parseString(strTerminalName,"_")

	if (tblQuest[2] == "questn" and self:isOnNegativeQuest(pPlayer, tblQuest[1])) then
		return true
	elseif (tblQuest[2] == "questp" and self:joinedCampaign(pPlayer,tblQuest[1])) then
		return true
	end
	return false
end

TourContainerComponent = {}

function TourContainerComponent:transferObject(pContainer, pObj, slot)
	local template = SceneObject(pObj):getTemplateObjectPath()

	if BestineElectionScreenPlay:tableHas(BestineElectionScreenPlay.seanEvidence, template) or BestineElectionScreenPlay:tableHas(BestineElectionScreenPlay.victorEvidence, template) then
		spatialChat(pContainer, "@bestine:give_governor_item") -- What's this? Please, if you wish to present evidence or whatnot, don't just thrust these things at me. Speak to me in a manner suited to civilized beings such as ourselves.
	end

	return 0
end

victor_visalis_conv_handler = victorVisalisConvoHandler:new {}
--sean_trenwell_conv_handler = seanTrenwellConvoHandler:new {}
tour_aryon_conv_handler = tourAryonConvoHandler:new {}
hutt_informant_conv_handler = huttInformantConvoHandler:new {}
seans_historian_conv_handler = seansHistorianConvoHandler:new {}
sean_contact_conv_handler = seanContactConvoHandler:new {}
bestine_election_questn_conv_handler = BestineElectionQuestnConvoHandler:new {}
bestine_election_questp_conv_handler = BestineElectionQuestpConvoHandler:new {}
bestine_election_conv_handler = bestineElectionConvoHandler:new {}
stone_merchant_conv_handler = StoneMerchantConvoHandler:new {}
