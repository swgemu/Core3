local ObjectManager = require("managers.object.object_manager")

BestineElectionScreenPlay = ScreenPlay:new {
	BESTINE_ELECTION_ENABLED = 1,
	CAMPAIGN_TIME = 2 * 60 * 1000,
	TUNE_TIME = 2 * 60 * 1000,

	seanEvidence = {"object/tangible/loot/quest/sean_questp_ctestimony.iff", "object/tangible/loot/quest/sean_questp_mdisk.iff", "object/tangible/loot/quest/sean_questp_htestimony.iff"},
	victorEvidence = {"object/tangible/loot/quest/victor_questp_testimony.iff","object/tangible/loot/quest/victor_questp_jregistry.iff", "object/tangible/loot/quest/victor_questp_receipt.iff"},

	candidates = {"Victor", "Sean"},

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

function BestineElectionScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:doPhaseInit()
		self:spawnMobiles()
		self:setupTerminals()
	end
end

function BestineElectionScreenPlay:spawnMobiles()
	for i = 1, #self.electionMobiles do
		local npcData = self.electionMobiles[i]
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

	--Hutt informant quest for Sean
	local pNpc = spawnMobile("tatooine", "hutt_informant_quest", 1, -1120, 12,-3639, 160, 0)
	if (pNpc ~= nil) then
		writeData("bestine_election:hutt_informant", SceneObject(pNpc):getObjectID())
		local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", -1120, 12, -3639, 15,0)
		if pActiveArea ~= nil then
			createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "informantApproach", pActiveArea)
		end
	end

	local electionWinner = getQuestStatus("bestine_election:electionWinner")
	if electionWinner == "Sean" then
		self:spawnMerchants()
	end

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

function BestineElectionScreenPlay:createEvent(duration)
	createServerEvent(duration, "BestineElectionScreenPlay", "doPhaseChange", "ElectionPhaseChange")
end

function BestineElectionScreenPlay:doPhaseInit()
	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return
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
	printf("[BestineElection] Initiating phase change: Phase "..currentPhase.." "..electionNum.."\n")

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
			setQuestStatus("bestine_election:election_num",electionNum)
			setQuestStatus("bestine_election:votesForSean",0)
			setQuestStatus("bestine_election:votesForVictor",0)
		end
	end
end

function BestineElectionScreenPlay:getCurrentPhase()
	local phase = tonumber(getQuestStatus("bestine_election:currentPhase"))
	if phase == nil then
		phase = 1
		setQuestStatus("bestine_election:currentPhase", phase)
	end
	return phase
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
	return self.BESTINE_ELECTION_ENABLED
end

function BestineElectionScreenPlay:determineWinner()
	local votesForSean = tonumber(getQuestStatus("bestine_election:votesForSean"))
	if (votesForSean == nil) then
		votesForSean = 0
	end

	local votesForVictor = tonumber(getQuestStatus("bestine_election:votesForVictor"))
	if (votesForVictor == nil) then
		votesForVictor = 0
	end

	local electionWinner = ""
	if (votesForSean == votesForVictor) then
		local chance = getRandomNumber(1,2)
		if (chance == 1) then
			electionWinner = "Sean"
			self:spawnMerchants()
		else electionWinner = "Victor"
			self:despawnMerchants()
		end
	elseif (votesForSean > votesForVictor) then
		electionWinner = "Sean"
		self:spawnMerchants()
		--remove some imperial guards
	elseif (votesForSean < votesForVictor) then
		electionWinner = "Victor"
		self:despawnMerchants()
		--spawn more imperials
		--start bestine raid script
	end
	setQuestStatus("bestine_election:electionWinner",electionWinner)
end

function BestineElectionScreenPlay:castVote(pPlayer, who)
	if (pPlayer ~= nil) and (self:tableHas(self.candidates, who)) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local votes = tonumber(getQuestStatus("bestine_election:votesFor"..who))
		if (votes == nil) then
			votes = 0
		end
		votes = votes + 1
		setQuestStatus("bestine_election:votesFor"..who,votes)
		writeScreenPlayData(pPlayer, "BestineElection", "Voted"..who,electionNum)
		self:removeEvidence(pPlayer, who)
		if who == "Sean" then
			CreatureObject(pPlayer):setScreenPlayState(2,"bestine_history_quest")
		end
	end
end

function BestineElectionScreenPlay:joinedCampaign(pPlayer, who)
	if (pPlayer ~= nil) and (self:tableHas(self.candidates, who)) then
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", who.."Campaign"))
		local electionNum = self:getElectionNumber()
		return (playerCampaign ~= nil) and (playerCampaign == electionNum)
	end
	return false
end

function BestineElectionScreenPlay:votedForWho(pPlayer,who)
	if (pPlayer ~= nil) and (self:tableHas(self.candidates, who)) then
		local electionNum = self:getElectionNumber()
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "Voted"..who))
		return (playerCampaign ~= nil) and (playerCampaign == electionNum)
	end
	return false
end

function BestineElectionScreenPlay:hasVoted(pPlayer)
	if (pPlayer == nil) then
		return false
	end
	return self:votedForWho(pPlayer,"Sean") or self:votedForWho(pPlayer,"Victor")
end

function BestineElectionScreenPlay:canVote(pPlayer, who)
	if (pPlayer == nil) then
		return false
	end
	local templates = {}

	if self:joinedCampaign(pPlayer, who) then
		if who == "Sean" then
			templates = self.seanEvidence
		elseif who == "Victor" then
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

function BestineElectionScreenPlay:removeEvidence(pPlayer, who)
	if (pPlayer ~= nil) and (self:tableHas(self.candidates, who)) then
		local templates = { }
		if who == "Sean" then
			templates = self.seanEvidence
		elseif who == "Victor" then
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

function BestineElectionScreenPlay:getPhaseTimeLeft()
	local eventID = getServerEventID("ElectionPhaseChange")
	if (eventID == nil) then
		return 0
	end
	return getServerEventTimeLeft(eventID) / 1000
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

function BestineElectionScreenPlay:noroomReturned(pPlayer, quest)
	if (pPlayer == nil or quest == "") then
		return false
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = self:getElectionNumber()
	local playerCampaign = readData(playerID..":bestine_election:"..quest.."_noroom")
	return (playerCampaign == electionNum)
end

function BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, who)
	if (pPlayer == nil) or (not self:tableHas(self.candidates, who))then
		return false
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", who.."NegQuest"))
	return (playerCampaign ~= nil) and (playerCampaign == electionNum)
end



function BestineElectionScreenPlay:setupTerminals()

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

	pTerminal = getSceneObject(3195507) --terminal for seans history quest.
	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionHistoryQuestMenuComponent")
		writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "sean_quest_history")
	end
end

function BestineElectionScreenPlay:spawnApproach(pActiveArea, pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isCreatureObject()) then
		return 0
	end

	local pNpc = getSceneObject(readData(SceneObject(pActiveArea):getObjectID() .. ":OwnerID"))
	if (pNpc ~= nil) then
		SceneObject(pNpc):faceObject(pMovingObject, true)
	end
	return 0
end

function BestineElectionScreenPlay:informantApproach(pActiveArea, pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isCreatureObject()) then
		return 0
	end

	local pInformant = getSceneObject(readData("bestine_election:hutt_informant"))
	if (pInformant ~= nil) then
		local pInventory = CreatureObject(pMovingObject):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true) ~= nil) then
				SceneObject(pInformant):faceObject(pMovingObject, true)
				spatialChat(pInformant, "@bestine:come_here")
			end
		end
	end
	return 0
end

function BestineElectionScreenPlay:canSearch(pSceneObject, pPlayer)
	if (pPlayer == nil or pSceneObject == nil) then
		return false
	end

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = self:parseString(strTerminalName,"_")
	if (tblQuest[1] == "victor") then
		if (tblQuest[2] == "questn" and self:isOnNegativeQuest(pPlayer, "Victor")) then
			return true
		elseif (tblQuest[2] == "questp" and self:joinedCampaign(pPlayer, "Victor")) then
			return true
		end
	elseif (tblQuest[1] == "sean") then
		if (tblQuest[2] == "questn" and self:isOnNegativeQuest(pPlayer, "Sean")) then
			return true
		elseif (tblQuest[2] == "questp" and self:joinedCampaign(pPlayer, "Sean")) then
			return true
		end
		return false
	end
end

TourContainerComponent = {}

function TourContainerComponent:transferObject(pContainer, pObj, slot)
	local pItem = SceneObject(pObj):getTemplateObjectPath()
	if BestineElectionScreenPlay:tableHas(BestineElectionScreenPlay.seanEvidence, pItem )
		or BestineElectionScreenPlay:tableHas(BestineElectionScreenPlay.victorEvidence, pItem)
	then spatialChat(pContainer, "@bestine:give_governor_item")
	end
	return 0
end


victor_visalis_conv_handler = victorVisalisConvoHandler:new {}
sean_trenwell_conv_handler = seanTrenwellConvoHandler:new {}
tour_aryon_conv_handler = tourAryonConvoHandler:new {}
hutt_informant_conv_handler = huttInformantConvoHandler:new {}
seans_historian_conv_handler = seansHistorianConvoHandler:new {}
sean_contact_conv_handler = seanContactConvoHandler:new {}
bestine_election_questn_conv_handler = BestineElectionQuestnConvoHandler:new {}
bestine_election_questp_conv_handler = BestineElectionQuestpConvoHandler:new {}
bestine_election_conv_handler = bestineElectionConvoHandler:new {}
stone_merchant_conv_handler = StoneMerchantConvoHandler:new {}
