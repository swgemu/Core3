local ObjectManager = require("managers.object.object_manager")

BestineElectionScreenPlay = ScreenPlay:new {}

BESTINE_ELECTION_ENABLED = 1

--local CAMPAIGN_TIME = 23 * 24 * 60 * 60 * 1000 -- 23 days Phase 1
--local TUNE_TIME = 7 * 24 * 60 * 60 * 1000 -- 7 days (TUNE = Time Until Next Election) Phase 2
local CAMPAIGN_TIME = 2 * 24 * 60 * 60 * 1000 -- 12 hours
local TUNE_TIME = 24 * 60 * 60 * 1000 -- 12 hours (TUNE = Time Until Next Election) Phase 2

local electionMobiles = {
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
}

local rumorMobiles = {
	{ template = "bestine_rumor01", x = -1068.17, z = 12, y = -3690.99, direction = 281, cellID=0, moodString = "neutral", breech = 6},
	{ template = "bestine_rumor02", x = -1205, z = 12, y = -3539, direction = 80, cellID=0, moodString = "neutral", breech = 6},
	{ template = "bestine_rumor03", x = -1211, z = 12, y = -3637.48, direction = 26, cellID=0, moodString = "neutral", breech = 4},
	{ template = "bestine_rumor04", x = -1074, z = 12, y = -3676, direction = 21, cellID=0, moodString = "neutral", breech = 6},
	{ template = "bestine_rumor05", x = -1013, z = 12, y = -3695, direction = 233, cellID=0, moodString = "neutral", breech = 6},
	{ template = "bestine_rumor06", x = -1088, z = 12, y = -3656, direction = 201, cellID=0, moodString = "neutral", breech = 4},
	{ template = "bestine_rumor07", x = -1048, z = 12, y = -3699, direction = 53, cellID=0, moodString = "neutral", breech = 4},
	{ template = "bestine_rumor08", x = -1145, z = 12, y = -3507, direction = 221, cellID=0, moodString = "neutral", breech = 4},
	{ template = "bestine_rumor09", x = 3.2, z = 0.5, y = -9.8 , direction = -107, cellID=1028169, moodString = "neutral", breech = 4},
	{ template = "bestine_rumor10", x = -1232, z = 14, y = -3525, direction = -177, cellID=0, moodString = "neutral", breech = 4},
	{ template = "bestine_rumor11", x = -1221, z = 12, y = -3650, direction = -49, cellID=0, moodString = "neutral", breech = 4},
	{ template = "bestine_rumor12", x = -1291, z = 12, y = -3634, direction = 301, cellID=0, moodString = "neutral", breech = 6},
}

local capitolMobiles = {
	{ template = "bestine_capitol01", x = -0.7, z = 3.22, y = 21.1, direction = 187, cellID=926474, moodString = "neutral", breech = 4},
	{ template = "bestine_capitol02", x = -23.29, z = 1.3, y = -10.39, direction = 234, cellID=926475, moodString = "neutral", breech = 4},
	{ template = "bestine_capitol03", x = -3.78, z = 2.27, y = -25.85, direction = 158, cellID=926475, moodString = "neutral", breech = 4},
	{ template = "bestine_capitol04", x = 2.26, z = 7.9, y = -37.38, direction = 0, cellID=926476, moodString = "neutral", breech = 4},
}

local merchMobiles = {
	{"bestine_merchant", -1135.28, 12,-3688.03, 61},
	{"bestine_merchant", -1136.64, 12, -3667.40, -175},
	{"bestine_merchant",-1115.29, 12, -3709.47, 7},
	{"bestine_merchant",-1133.53, 12, -3693.98, 90},
	{"bestine_stone_merchant", -1127, 12, -3674, -110},
}

registerScreenPlay("BestineElectionScreenPlay", true)

function BestineElectionScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:doPhaseInit()
		self:spawnMobiles()
		self:setupTerminals()
	end
end

function BestineElectionScreenPlay:spawnMobiles()
 	for i = 1, #electionMobiles do
		local npcData = electionMobiles[i]
		local pNpc = spawnMobile("tatooine", npcData.template, 60, npcData.x, npcData.z, npcData.y, npcData.direction, npcData.cellID)
		if (pNpc ~= nil) then
			self:setMoodString(pNpc, npcData.moodString)
			if npcData.template == "tour_aryon" then
				SceneObject(pNpc):setContainerComponent("TourContainerComponent")
			end
			if npcData.breech > 0 then
				local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pNpc):getWorldPositionX(),SceneObject(pNpc):getWorldPositionZ(),SceneObject(pNpc):getWorldPositionY(), npcData.breech, 0)
				if pActiveArea ~= nil then
					local areaID = SceneObject(pActiveArea):getObjectID()
					writeData(areaID .. ":OwnerID", SceneObject(pNpc):getObjectID())
					createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "spawnApproach", pActiveArea)
				end
			end
		end
	end

	for i = 1, #capitolMobiles do
		local npcData = capitolMobiles[i]
		pNpc = spawnMobile("tatooine", npcData.template, 60, npcData.x, npcData.z, npcData.y, npcData.direction, npcData.cellID)
		if (pNpc ~= nil) then
			self:setMoodString(pNpc, npcData.moodString)
			if npcData.breech > 0 then
				local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pNpc):getWorldPositionX(),SceneObject(pNpc):getWorldPositionZ(),SceneObject(pNpc):getWorldPositionY(), npcData.breech, 0)
				if pActiveArea ~= nil then
					local areaID = SceneObject(pActiveArea):getObjectID()
					writeData(areaID .. ":OwnerID", SceneObject(pNpc):getObjectID())
					createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "spawnApproach", pActiveArea)
				end
			end
		end
	end

	for i = 1, #rumorMobiles do
		local npcData = rumorMobiles[i]
		pNpc = spawnMobile("tatooine", npcData.template, 60, npcData.x, npcData.z, npcData.y, npcData.direction, npcData.cellID)
		if pNpc ~= nil then
			self:setMoodString(pNpc, npcData.moodString)
			if npcData.breech > 0 then
				local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pNpc):getWorldPositionX(),SceneObject(pNpc):getWorldPositionZ(),SceneObject(pNpc):getWorldPositionY(), npcData.breech, 0)
				if pActiveArea ~= nil then
					local areaID = SceneObject(pActiveArea):getObjectID()
					writeData(areaID .. ":OwnerID", SceneObject(pNpc):getObjectID())
					createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "spawnApproach", pActiveArea)
				end
			end
		end
	end

	--Hutt informant quest for Sean
	local pNpc = spawnMobile("tatooine", "hutt_informant_quest", 1, -1120, 12,-3639, 160, 0)
	if (pNpc ~= nil) then
		writeData("bestine_election:hutt_informant", SceneObject(pNpc):getObjectID())
		local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", -1120, 12, -3639, 15,0)
		if pActiveArea ~= nil then
			createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "informantApproach", pActiveArea)
		end
	end
end

function BestineElectionScreenPlay:spawnMerchants()
for i = 1, #merchMobiles do
local merchData = merchMobiles[i]
local pNpc = spawnMobile("tatooine", merchData[1], 0, merchData[2], merchData[3], merchData[4], merchData[5], 0)
if (pNpc ~= nil) then
			local mobileID = SceneObject(pNpc):getObjectID()
			writeData("bestine_election:merchants:" .. i, mobileID)
		end
end
	local pSnd = spawnSceneObject("tatooine", "object/soundobject/soundobject_marketplace_large.iff", -1124.35, 12.0, -3695.85, 0, 1, 0, 0, 0)
	if (pSnd ~= nil) then
		mobileID = SceneObject(pSnd):getObjectID()
		writeData("bestine_election:merchants:marketsound", mobileID)
	end
end

function BestineElectionScreenPlay:despawnMerchants()
	for i = 1, #merchMobiles, 1 do
		local objectID = readData("bestine_election:merchants:" .. i)
		local pMobile = getSceneObject(objectID)
		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
			deleteData("bestine_election:merchants:" .. i)
		end
	end
	local marketSoundID = readData("bestine_election:merchants:marketsound")
	local pSnd = getSceneObject(marketSoundID)
	SceneObject(pSnd):destroyObjectFromWorld()
	deleteData("bestine_election:merchants:object:marketsound")
end

function BestineElectionScreenPlay:createEvent(duration)
	local eventID = createServerEvent(duration, "BestineElectionScreenPlay", "doPhaseChange", "ElectionPhaseChange")
	setQuestStatus("bestine_election:event_id", eventID)
end

function BestineElectionScreenPlay:doPhaseInit()
	if (not self:isElectionEnabled()) then
		return
	end

	local phase = self:getCurrentPhase()
	if (phase == nil) then
		self:setCurrentPhase(1)
	end

	if (not hasServerEvent("ElectionPhaseChange")) then
		BestineElectionScreenPlay:createEvent(CAMPAIGN_TIME)
	end
end

function BestineElectionScreenPlay:doPhaseChange()
	if (not self:isElectionEnabled()) then
		return
	end

	local electionNum = tonumber(getQuestStatus("bestine_election:election_num"))
	if (electionNum == nil) then
		electionNum = 1
		setQuestStatus("bestine_election:election_num", electionNum)
	end

	local currentPhase = self:getCurrentPhase()
	if (currentPhase == 1) then
		self:setCurrentPhase(2)
		self:determineWinner()
		if (not hasServerEvent("ElectionPhaseChange")) then
			BestineElectionScreenPlay:createEvent(TUNE_TIME)
		end
	else
		self:setCurrentPhase(1)
		if (not hasServerEvent("ElectionPhaseChange")) then
			BestineElectionScreenPlay:createEvent(CAMPAIGN_TIME)
			electionNum = electionNum + 1
			setQuestStatus("bestine_election:election_num",electionNum)
			setQuestStatus("bestine_election:votesForSean",0)
			setQuestStatus("bestine_election:votesForVictor",0)
		end
	end
	printf("[BestineElection] Initiating phase change.\n")
end


function BestineElectionScreenPlay:getCurrentPhase()
	return tonumber(getQuestStatus("bestine_election:currentPhase"))
end

function BestineElectionScreenPlay:setCurrentPhase(phase)
	if (phase >= 3) or (phase <= 0) or (phase == nil) then
		phase = 1
	end
	setQuestStatus("bestine_election:currentPhase", phase)
end

function BestineElectionScreenPlay:getElectionNumber()
	local electionNum = tonumber(getQuestStatus("bestine_election:election_num"))
	if (electionNum == nil) then
		electionNum = 1
		setQuestStatus("bestine_election:election_num",electionNum)
 	end
	return electionNum
end

function BestineElectionScreenPlay:isElectionEnabled()
	return BESTINE_ELECTION_ENABLED
end

function BestineElectionScreenPlay:determineWinner()
	local votesForSean = tonumber(getQuestStatus("bestine_election:votesForSean"))
	local votesForVictor = tonumber(getQuestStatus("bestine_election:votesForVictor"))
	local electionWinner = ""
	if (votesForSean == votesForVictor) then
		local chance = getRandomNumber(1,2)
		if (chance == 1) then
			electionWinner = "Sean"
		else electionWinner = "Victor"
		end
	end
	if (votesForSean > votesForVictor) then
		electionWinner = "Sean"
		self:spawnMerchants()
	end
	if (votesForSean < votesForVictor) then
		electionWinner = "Victor"
		self:despawnMerchants()
	end
	setQuestStatus("bestine_election:electionWinner",electionWinner)
end

function BestineElectionScreenPlay:voteForVictor(pPlayer)
	local votes = getQuestStatus("bestine_election:votesForVictor")
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()
	if (votes == nil) then
		votes = 0
		setQuestStatus("bestine_election:votesForVictor",votes)
	end
	votes = votes + 1
	setQuestStatus("bestine_election:votesForVictor",votes)
	writeData(playerID..":bestine_election:VotedVictor",electionNum)
end

function BestineElectionScreenPlay:voteForSean(pPlayer)
	local votes = getQuestStatus("bestine_election:votesForSean")
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()
	if (votes == nil) then
		votes = 0
		setQuestStatus("bestine_election:votesForSean",votes)
	end
	votes = votes + 1
	setQuestStatus("bestine_election:votesForSean",votes)
	writeData(playerID..":bestine_election:VotedSean",electionNum)
end

function BestineElectionScreenPlay:joinedVictorCampaign(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local playerCampaign = readData(playerID..":bestine_election:VictorCampaign")
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if (playerCampaign ~= nil) then
		return (playerCampaign >= electionNum)
	end
	return false
end

function BestineElectionScreenPlay:joinedSeanCampaign(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local playerCampaign = readData(playerID..":bestine_election:SeanCampaign")
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if (playerCampaign ~= nil) then
		return (playerCampaign >= electionNum)
	end
	return false
end

function BestineElectionScreenPlay:votedVictor(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = self:getElectionNumber()
	if (self:getCurrentPhase() == 1) then
		electionNum = self:getElectionNumber() -1
	end
	local playerCampaign = readData(playerID..":bestine_election:VotedVictor")
	if(playerCampaign == 0) or (playerCampaign == nil) then
		return false
	end
	return (playerCampaign == electionNum)
end

function BestineElectionScreenPlay:votedSean(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = self:getElectionNumber()
	if (self:getCurrentPhase() == 1) then
		electionNum = self:getElectionNumber() -1
	end
	local playerCampaign = readData(playerID..":bestine_election:VotedSean")
	if(playerCampaign == 0) or (playerCampaign == nil) then
		return false
	end
	return (playerCampaign == electionNum)
end

function BestineElectionScreenPlay:canVote(pPlayer)
	return (not BestineElectionScreenPlay:hasAlreadyVoted(pPlayer)) and (BestineElectionScreenPlay:canVoteForSean(pPlayer) or BestineElectionScreenPlay:canVoteForVictor(pPlayer))
end

function BestineElectionScreenPlay:hasAlreadyVoted(pPlayer)
	return self:votedVictor(pPlayer) or self:votedSean(pPlayer)
end

function BestineElectionScreenPlay:canVoteForSean(pPlayer)
	if self:joinedSeanCampaign(pPlayer) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			if getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_ctestimony.iff" , true) then
				return true
			elseif getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_mdisk.iff", true) then
				return true
			elseif getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_htestimony.iff", true) then
				return true
			end
		end
	end
	return false
end

function BestineElectionScreenPlay:canVoteForVictor(pPlayer)
	if self:joinedVictorCampaign(pPlayer) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			if getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_testimony.iff" , true) then
				return true
			elseif getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_jregistry.iff", true) then
				return true
			elseif getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_receipt.iff", true) then
				return true
			end
		end
	end
	return false
end

function BestineElectionScreenPlay:removeSeanEvidence(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		local evidenceItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_ctestimony.iff" , true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
		evidenceItem = getContainerObjectByTemplate(pInventory,"object/tangible/loot/quest/sean_questp_mdisk.iff", true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
		evidenceItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_htestimony.iff", true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
	end
	return
end

function BestineElectionScreenPlay:removeVictorEvidence(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		local evidenceItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_testimony.iff" , true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
		evidenceItem = getContainerObjectByTemplate(pInventory,"object/tangible/loot/quest/victor_questp_jregistry.iff", true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
		evidenceItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_receipt.iff", true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
	end
	return
end

function BestineElectionScreenPlay:getPhaseTimeLeft()
	local eventID = getServerEventID("ElectionPhaseChange")
	if (eventID == nil) then
		return
	end
	local timeLeft = getServerEventTimeLeft(eventID) / 1000
	return timeLeft
end

function BestineElectionScreenPlay:hasFullInventory(pPlayer)
	if (pPlayer == nil) then
		return true
	end
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
	if (pInventory == nil) then
		return true
	end
	return SceneObject(pInventory):isContainerFullRecursive()
end

function BestineElectionScreenPlay:setupTerminals()
	local pTerminal = getSceneObject(5565564) --terminal in victors office gives object/tangible/loot/quest/victor_questp_jregistry.iff
	if pTerminal ~= nil then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionVictorTerminalMenuComponent_Registry")
	end
	pTerminal = getSceneObject(5565562) --desk in seans office
	if pTerminal ~= nil then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionSeanDeskMenuComponent")
	end
	pTerminal = getSceneObject(5565563) --terminal in seans office
	if pTerminal ~= nil then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionSeanTerminalMenuComponent")
	end

	pTerminal = getSceneObject(4475579) --other desk in seans office
	if pTerminal ~= nil then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionSeanDesk2MenuComponent")
	end
	--4475571 SEans table
	pTerminal = getSceneObject(4475571) --other desk in seans office
	if pTerminal ~= nil then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionFakeSearchMenuComponent")
	end

	pTerminal = getSceneObject(4475517) --4475517 victors desk - gives object/tangible/loot/quest/victor_questn_journal.iff
	if pTerminal ~= nil then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionSearchMenuComponent_Journal")
	end

	pTerminal = getSceneObject(5565565) --5565565 victors table
	if pTerminal ~= nil then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionFakeSearchMenuComponent")
	end

	pTerminal = getSceneObject(3195507) --terminal for seans history quest.
	if pTerminal ~= nil then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionHistoryQuestMenuComponent")
	end

end

function BestineElectionScreenPlay:spawnApproach(pActiveArea, pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isCreatureObject()) then
		return 0
	end

	local npcID = readData(SceneObject(pActiveArea):getObjectID() .. ":OwnerID")
	local pNpc = getSceneObject(npcID)
	if (pNpc ~= nil) then
		SceneObject(pNpc):faceObject(pMovingObject, true)
	end
	return 0
end

function BestineElectionScreenPlay:informantApproach(pActiveArea, pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isCreatureObject()) then
		return 0
	end
	local informantId = readData("bestine_election:hutt_informant")
	local pInformant = getSceneObject(informantId)
	if pInformant ~= nil then
		local pInventory = CreatureObject(pMovingObject):getSlottedObject("inventory")
		if pInventory ~= nil then
			if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true) ~= nil) then
				SceneObject(pInformant):faceObject(pMovingObject, true)
				spatialChat(pInformant, "@bestine:come_here")
			end
		end
	end
	return 0
end

tour_aryon_conv_handler = tourAryonConvoHandler:new {
themePark = BestineElection
}
hutt_informant_conv_handler = huttInformantConvoHandler:new {
themePark = BestineElection
}
victor_visalis_conv_handler = victorVisalisConvoHandler:new {
themePark = BestineElection
}
sean_trenwell_conv_handler = seanTrenwellConvoHandler:new {
themePark = BestineElection
}
seans_historian_conv_handler = seansHistorianConvoHandler:new {
themePark = BestineElection
}
sean_contact_conv_handler = seanContactConvoHandler:new {
themePark = BestineElection
}
keanna_likyna_conv_handler = keannaLikynaConvoHandler:new {
themePark = BestineElection
}
indigo_siyan_conv_handler = indigoSiyanConvoHandler:new {
themePark = BestineElection
}
victor_questn_cantina_conv_handler = victorQuestnCantinaConvoHandler:new {
themePark = BestineElection
}
victor_questn_capitol_conv_handler = victorQuestnCapitolConvoHandler:new {
themePark = BestineElection
}
sean_questn_university_conv_handler = seanQuestnUniversityConvoHandler:new {
themePark = BestineElection
}
bestine_rumor_conv_handler = bestineRumorConvoHandler:new {
themePark = BestineElection
}
bestine_capitol_conv_handler = bestineCapitolConvoHandler:new {
themePark = BestineElection
}
bestine_election_questp_conv_handler = BestineElectionQuestpConvoHandler:new {
themePark = BestineElection
}
stone_merchant_conv_handler = StoneMerchantConvoHandler:new {
themePark = BestineElection
}
