BestineElection = ScreenPlay:new {
	electionEnabled = true,

	electionDuration = 24 * 60 * 60 * 1000, -- Duration of the election phase
	timeTilNextElection = 24 * 60 * 60 * 1000, -- Time until next election, starts immediately after an election ends

	ELECTION_PHASE = 1,
	OFFICE_PHASE = 2,

	seanEvidence = { "object/tangible/loot/quest/sean_questp_ctestimony.iff", "object/tangible/loot/quest/sean_questp_mdisk.iff", "object/tangible/loot/quest/sean_questp_htestimony.iff" },
	seanRivalEvidence = { "object/tangible/loot/quest/sean_questn_alog.iff", "object/tangible/loot/quest/sean_questn_gpapers.iff", "object/tangible/loot/quest/sean_questn_tdisk.iff" },
	victorEvidence = { "object/tangible/loot/quest/victor_questp_testimony.iff", "object/tangible/loot/quest/victor_questp_jregistry.iff", "object/tangible/loot/quest/victor_questp_receipt.iff" },
	victorRivalEvidence = { "object/tangible/loot/quest/victor_questn_dseal.iff", "object/tangible/loot/quest/victor_questn_hlist.iff", "object/tangible/loot/quest/victor_questn_journal.iff" },

	-- Constants for candidates
	NONE = 0,
	SEAN = 1,
	VICTOR = 2,

	SEAN_MAIN_QUEST = 1,
	SEAN_HISTORY_QUEST = 2,
	SEAN_RIVAL_QUEST = 3,
	SEAN_HOUSE_EVIDENCE = 4,
	SEAN_CURATOR_EVIDENCE = 5,
	SEAN_MARKET_EVIDENCE = 6,
	SEAN_RIVAL_CAPITOL_EVIDENCE = 7,
	SEAN_RIVAL_CANTINA_EVIDENCE = 8,
	SEAN_MAIN_REWARD = 9,

	SEAN_HISTORY_QUEST_ACCEPTED = 1,
	SEAN_HISTORY_QUEST_STARTED_SEARCH = 2,
	SEAN_HISTORY_QUEST_FOUND_DISK = 3,
	SEAN_HISTORY_QUEST_DISK_SCREENED = 4,
	SEAN_HISTORY_QUEST_SENT_TO_CONTACT = 5,
	SEAN_HISTORY_QUEST_DISK_DESTROYED = 6,
	SEAN_HISTORY_QUEST_GAVE_TO_HUTT = 7,
	SEAN_HISTORY_QUEST_RECEIVED_REWARD = 8,

	SEAN_RIVAL_QUEST_ACCEPTED = 1,
	SEAN_RIVAL_QUEST_COMPLETED = 2,

	VICTOR_MAIN_QUEST = 1,
	VICTOR_RIVAL_QUEST = 2,
	VICTOR_TUSKEN_QUEST = 3,
	VICTOR_MAIN_REWARD = 4,
	VICTOR_TUSKEN_REWARD = 5,
	VICTOR_RIVAL_UNIVERSITY_EVIDENCE = 6,
	VICTOR_HOSPITAL_EVIDENCE = 7,
	VICTOR_SLUMS_EVIDENCE = 8,
	VICTOR_SMOOTH_STONE = 9,
	VICTOR_CARVED_STONE = 10,

	VICTOR_STONE_REWARD_RECEIVED = 1,

	VICTOR_TUSKEN_QUEST_ACCEPTED = 1,
	VICTOR_TUSKEN_QUEST_COMPLETED = 2,

	VICTOR_RIVAL_QUEST_ACCEPTED = 1,
	VICTOR_RIVAL_QUEST_COMPLETED = 2
}

registerScreenPlay("BestineElection", true)

function BestineElection:isElectionEnabled()
	return self.electionEnabled
end

function BestineElection:doPhaseInit()
	if (not self:isElectionEnabled()) then
		return
	end

	if (not hasServerEvent("ElectionPhaseChange")) then
		self:setCurrentPhase(1)
		self:createNewVoterList()
		createServerEvent(self.electionDuration, "BestineElection", "doPhaseChange", "ElectionPhaseChange")
	else
		local eventID = getServerEventID("ElectionPhaseChange")

		if (eventID == nil or getServerEventTimeLeft(eventID) == nil) then
			self:doPhaseChange()
		end
	end
end

function BestineElection:start()
	if (isZoneEnabled("tatooine")) then
		local currentPhase = self:getCurrentPhase()
		self:doPhaseInit()
		self:spawnElectionMobiles()
		self:initTerminals()
	end
end

function BestineElection:doPhaseChange()
	if (not self:isElectionEnabled()) then
		return
	end

	local electionNum = self:getElectionNumber()
	local currentPhase = self:getCurrentPhase()

	if (currentPhase == 1) then
		self:determineWinner()
		self:setCurrentPhase(2)

		if (not hasServerEvent("ElectionPhaseChange")) then
			createServerEvent(self.timeTilNextElection, "BestineElection", "doPhaseChange", "ElectionPhaseChange")
		else
			rescheduleServerEvent("ElectionPhaseChange", self.timeTilNextElection)
		end
	elseif (currentPhase == 2) then
		local newNum = electionNum + 1
		self:setElectionNumber(newNum)
		self:setCurrentPhase(1)
		self:createNewVoterList()

		if (not hasServerEvent("ElectionPhaseChange")) then
			createServerEvent(self.electionDuration, "BestineElection", "doPhaseChange", "ElectionPhaseChange")
		else
			rescheduleServerEvent("ElectionPhaseChange", self.electionDuration)
		end
	end
end

function BestineElection:spawnElectionMobiles()
	local mobileTable = electionMobiles

	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]

		local pMobile = spawnMobile("tatooine", mobile[1], 0, mobile[2], mobile[3], mobile[4], mobile[5], mobile[6])

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)

			if (mobile[7] ~= "") then
				self:setMoodString(pMobile, mobile[7])
			end

			--spawn trigger area for FaceTo & conversations (only if election is enabled)
			if (self:isElectionEnabled()) then
				if (mobile[8] > 0) then
					local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), SceneObject(pMobile):getWorldPositionZ(), SceneObject(pMobile):getWorldPositionY(), mobile[8], 0)

					if (pActiveArea ~= nil) then
						if (mobile[1] == "hutt_informant_quest") then
							createObserver(ENTEREDAREA, "BestineElection", "enteredInformantArea", pActiveArea)
						else
							createObserver(ENTEREDAREA, "BestineElection", "enteredMobileArea", pActiveArea)
						end
						local areaID = SceneObject(pActiveArea):getObjectID()
						local mobileID = SceneObject(pMobile):getObjectID()
						writeData(mobileID .. ":activeArea", areaID)
						writeData(areaID .. ":mobileID", mobileID)
					end
				end

				if (mobile[1] == "tour_aryon") then
					SceneObject(pMobile):setContainerComponent("TourContainerComponent")
				end

				if (mobile[9] ~= "") then
					CreatureObject(pMobile):setOptionsBitmask(136)
					AiAgent(pMobile):setConvoTemplate(mobile[9])
				end
			end
		end
	end

	local electionNum = self:getElectionNumber()
	local electionWinner = self:getElectionWinner(electionNum)
	local curPhase = BestineElection:getCurrentPhase()

	if (curPhase == BestineElection.ELECTION_PHASE) then
		electionWinner = BestineElection:getElectionWinner(electionNum - 1)
	end

	self:spawnCandidateMobiles(electionWinner)
end

function BestineElection:spawnCandidateMobiles(candidate)
	local candidateTable

	if (candidate == self.SEAN) then
		candidateTable = seanMerchants
	else
		candidateTable = victorImperials
	end

	for i = 1, #candidateTable do
		local npcData = candidateTable[i]
		local pMobile = spawnMobile("tatooine", npcData[1], 0, npcData[2], npcData[3], npcData[4], npcData[5], 0)

		if (pMobile ~= nil) then
			local mobileID = SceneObject(pMobile):getObjectID()
			writeData("bestineElection:candidateMobile:" .. i, mobileID)
		end
	end

	if (candidate == self.SEAN) then
		local pSnd = spawnSceneObject("tatooine", "object/soundobject/soundobject_marketplace_large.iff", -1124, 12, -3695, 0, 0)

		if (pSnd ~= nil) then
			local soundID = SceneObject(pSnd):getObjectID()
			writeData("bestineElection:marketSound", soundID)
		end
	end
end

function BestineElection:despawnCandidateMobiles()
	for i = 1, #seanMerchants do
		local objectID = readData("bestineElection:candidateMobile:" .. i)
		local pMobile = getSceneObject(objectID)

		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
		end

		deleteData("bestineElection:candidateMobile:" .. i)
	end

	for i = 1, #victorImperials do
		local objectID = readData("bestineElection:candidateMobile:" .. i)
		local pMobile = getSceneObject(objectID)

		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
		end

		deleteData("bestineElection:candidateMobile:" .. i)
	end

	local marketSoundID = readData("bestineElection:marketSound")

	local pSnd = getSceneObject(marketSoundID)

	if (pSnd ~= nil) then
		SceneObject(pSnd):destroyObjectFromWorld()
	end

	deleteData("bestineElection:marketSound")
end

function BestineElection:initTerminals()
	if (not self:isElectionEnabled()) then
		return
	end

	local pTerminal = getSceneObject(5565564) --terminal in victors office gives object/tangible/loot/quest/victor_questp_jregistry.iff

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineEvidenceMenuComponent")
		writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "victor_questp_jregistry")
	end

	pTerminal = getSceneObject(4475517) --4475517 victors desk - gives object/tangible/loot/quest/victor_questn_journal.iff

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineEvidenceMenuComponent")
		writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "victor_questn_journal")
	end

	pTerminal = getSceneObject(5565563) --terminal in seans office gives "object/tangible/loot/quest/sean_questn_tdisk.iff"

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineEvidenceMenuComponent")
		writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "sean_questn_tdisk")
	end

	pTerminal = getSceneObject(5565562) --desk in seans office gives "object/tangible/loot/quest/sean_questn_alog.iff"

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineEvidenceMenuComponent")
		writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "sean_questn_alog")
	end

	pTerminal = getSceneObject(3195507)

	if (pTerminal ~= nil) then
		local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pTerminal):getWorldPositionX(), SceneObject(pTerminal):getWorldPositionZ(), SceneObject(pTerminal):getWorldPositionY(), 2, 0)

		if pActiveArea ~= nil then
			createObserver(ENTEREDAREA, "BestineElection", "enteredHistoryTerminalArea", pActiveArea)
		end
	end
end

function BestineElection:enteredHistoryTerminalArea(pActiveArea, pPlayer)
	if (pPlayer == nil or pActiveArea == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	if (self:getQuestStep(pPlayer, self.SEAN, self.SEAN_HISTORY_QUEST) == self.SEAN_HISTORY_QUEST_FOUND_DISK) then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:history_disk_found_already") -- You search the area, but find nothing else of interest.
		return 0
	end

	if (self:getQuestStep(pPlayer, self.SEAN, self.SEAN_HISTORY_QUEST) == self.SEAN_HISTORY_QUEST_STARTED_SEARCH) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")

			return 0
		end

		local pDisk = giveItem(pInventory, "object/tangible/loot/quest/sean_history_disk.iff", -1)

		if (pDisk == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item:sean_history_disk.iff")
			return 0
		end

		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:history_disk_found") -- As you approach the terminal, you notice something sticking out of a dataslot and you take it. The object appears to be an aged datadisk, but it looks like it might still be readable
		self:setQuestStep(pPlayer, self.SEAN, self.SEAN_HISTORY_QUEST, self.SEAN_HISTORY_QUEST_FOUND_DISK)
	end

	return 0
end

function BestineElection:determineWinner()
	local electionNum = self:getElectionNumber()
	local pMap = self:getVoterList(electionNum)

	if (pMap == nil) then
		printLuaError("Error in BestineElection:determineWinner, attempting to get non existant vote map.")
		return false
	end

	local voterMap = LuaQuestVectorMap(pMap)

	local victorVotes = 0
	local seanVotes = 0
	local electionWinner = self.NONE

	local totalPlayers = voterMap:getMapSize()

	if (totalPlayers > 0) then
		for i = 1, totalPlayers, 1 do
			local playerID = voterMap:getMapKeyAtIndex(i - 1)
			local playerVote = tonumber(voterMap:getMapRow(playerID))

			if (playerVote == self.SEAN) then
				seanVotes = seanVotes + 1
			elseif (playerVote == self.VICTOR) then
				victorVotes = victorVotes + 1
			end
		end
	end

	if (seanVotes > victorVotes) then
		electionWinner = self.SEAN
	elseif (seanVotes == victorVotes) then
		local chance = getRandomNumber(0, 200) --fixes Tie

		if (chance <= 100) then
			electionWinner = self.SEAN
		else
			electionWinner = self.VICTOR
		end
	else
		electionWinner = self.VICTOR
	end

	self:despawnCandidateMobiles()
	self:spawnCandidateMobiles(electionWinner)

	self:setElectionWinner(electionNum, electionWinner)
end

function BestineElection:enteredMobileArea(pActiveArea, pPlayer)
	if (pActiveArea == nil or pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local areaID = SceneObject(pActiveArea):getObjectID()
	local mobileID = readData(areaID .. ":mobileID")
	local pMobile = getSceneObject(mobileID)

	if (pMobile == nil) then
		return 1
	end

	SceneObject(pMobile):faceObject(pPlayer, true)

	return 0
end

function BestineElection:enteredInformantArea(pActiveArea, pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isPlayerCreature()) then
		return 0
	end

	local areaID = SceneObject(pActiveArea):getObjectID()
	local mobileID = readData(areaID .. ":mobileID")

	local pMobile = getSceneObject(mobileID)

	if (pMobile == nil) then
		return 1
	end

	local electionNum = self:getElectionNumber()
	local electionWinner = self:getElectionWinner(electionNum)

	local curPhase = BestineElection:getCurrentPhase()
	if (curPhase == BestineElection.ELECTION_PHASE) then
		electionWinner = BestineElection:getElectionWinner(electionNum - 1)
	end

	if (electionWinner ~= BestineElection.SEAN or BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) ~= BestineElection.SEAN_HISTORY_QUEST_SENT_TO_CONTACT) then
		return 0
	end

	local pInventory = CreatureObject(pMovingObject):getSlottedObject("inventory")

	if (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true) ~= nil) then
		SceneObject(pMobile):faceObject(pMovingObject, true)
		spatialChat(pMobile, "@bestine:come_here") -- Hey... c'mere a second. I think we can help one another.
	end

	return 0
end

function BestineElection:hasCandidateEvidence(pPlayer, candidate, rivalEvidence)
	if (pPlayer == nil) then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if(pInventory == nil) then
		return false
	end

	local templates = {}

	if (candidate == self.SEAN) then
		if (rivalEvidence) then
			templates = self.victorRivalEvidence
		else
			templates = self.seanEvidence
		end
	elseif (candidate == self.VICTOR) then
		if (rivalEvidence) then
			templates = self.seanRivalEvidence
		else
			templates = self.victorEvidence
		end
	else
		return false
	end

	for i = 1, #templates, 1 do
		local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)

		if (pInvItem ~= nil) then
			return true
		end
	end

	return false
end

function BestineElection:canVoteForCandidate(pPlayer, candidate)
	return self:hasJoinedCampaign(pPlayer, candidate) and self:hasCandidateEvidence(pPlayer, candidate)
end

function BestineElection:removeCandidateEvidence(pPlayer, candidate)
	if (pPlayer == nil) then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if(pInventory == nil) then
		return false
	end

	local templates = {}

	if (candidate == self.SEAN) then
		templates = self.seanEvidence
	elseif (candidate == self.VICTOR) then
		templates = self.victorEvidence
	else
		return false
	end

	local foundEvidence = false

	for i = 1, #templates, 1 do
		local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)

		if (pInvItem ~= nil) then
			SceneObject(pInvItem):destroyObjectFromWorld()
			SceneObject(pInvItem):destroyObjectFromDatabase()
			foundEvidence = true
		end
	end

	return foundEvidence
end

function BestineElection:hasFullInventory(pPlayer)
	if (pPlayer == nil) then
		return true
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	return pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()
end

function BestineElection:hasItemInInventory(pPlayer, template)
	if (pPlayer == nil) then
		return false
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	return pInventory ~= nil and getContainerObjectByTemplate(pInventory, template, true)
end

function BestineElection:giveCampaignReward(pPlayer, candidate)
	if (self:getPlayerVote(pPlayer) ~= candidate) then
		return
	end

	local rewardChance = getRandomNumber(1, 1000)
	local rewardTemplate

	-- No evidence of these rewards being given during 14.1.
	--[[	if (rewardChance <= 50) then
		if (candidate == self.SEAN) then
			rewardTemplate = "object/tangible/painting/bestine_quest_painting.iff"
		else
			rewardTemplate = "object/weapon/melee/sword/bestine_quest_sword.iff"
		end
	else ]]

	if (rewardChance <= 300) then
		if (candidate == self.SEAN) then
			rewardTemplate = "object/tangible/furniture/modern/bestine_quest_rug.iff"
		else
			rewardTemplate = "object/tangible/furniture/all/bestine_quest_imp_banner.iff"
		end
	else
		if (candidate == self.SEAN) then
			rewardTemplate = "object/tangible/furniture/all/bestine_quest_statue.iff"
		else
			rewardTemplate = "object/tangible/wearables/necklace/bestine_quest_badge.iff"
		end
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pReward = giveItem(pInventory, rewardTemplate, -1)

	if (pReward == nil) then
		printLuaError("Error creating campaign reward for player " .. CreatureObject(pPlayer):getFirstName() .. " for candidate " .. candidate)
		return
	end

	self:setReceivedElectionReward(pPlayer)
end

function BestineElection:notifyKilledCreature(pPlayer, pVictim)
	if (pVictim == nil) then
		return 0
	end

	if (pPlayer == nil) then
		return 1
	end

	if (not self:isElectionEnabled()) then
		return 1
	end

	if (self:getQuestStep(pPlayer, self.VICTOR, self.VICTOR_TUSKEN_QUEST) ~= self.VICTOR_TUSKEN_QUEST_ACCEPTED) then
		return 1
	end

	local pVictimInv = CreatureObject(pVictim):getSlottedObject("inventory")

	if (pVictimInv == nil) then
		return 0
	end

	local victimName = SceneObject(pVictim):getObjectName()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (victimName == "tusken_executioner" and not self:hasItemInInventory(pPlayer, "object/tangible/loot/quest/tusken_head.iff")) then
		SceneObject(pVictimInv):setContainerOwnerID(playerID)
		createLoot(pVictimInv, "bestine_election_tusken_head", 0, true)
	end

	if (victimName == "tusken_executioner" or victimName == "tusken_observer" or victimName == "tusken_witch_doctor") then
		SceneObject(pVictimInv):setContainerOwnerID(playerID)
		local chance = getRandomNumber(10000)

		if (chance < 100) then
			createLoot(pVictimInv, "bestine_election_carved_stone", 0, true)
		elseif (chance < 400) then
			createLoot(pVictimInv, "bestine_election_smooth_stone", 0, true)
		elseif (chance < 800) then
			createLoot(pVictimInv, "bestine_election_baton", 0, true)
		end
	end

	return 0
end

function BestineElection:playerLoggedIn(pPlayer)
	if (self:getQuestStep(pPlayer, self.VICTOR, self.VICTOR_TUSKEN_QUEST) == self.VICTOR_TUSKEN_QUEST_ACCEPTED) then
		dropObserver(KILLEDCREATURE, "BestineElection", "notifyKilledCreature", pPlayer)
		createObserver(KILLEDCREATURE, "BestineElection", "notifyKilledCreature", pPlayer)
	end
end

--------------------------------------------------------------------------
-- Functions below handle reading/writing of the main screenplay variables
--------------------------------------------------------------------------
function BestineElection:getCurrentPhase()
	local curPhase = tonumber(getQuestStatus("bestineElection:currentPhase"))

	if (curPhase == nil or curPhase == 0) then
		self:setCurrentPhase(1)
		return 1
	end

	return curPhase
end

function BestineElection:setCurrentPhase(newPhase)
	setQuestStatus("bestineElection:currentPhase", newPhase)
end

function BestineElection:getElectionNumber()
	local electionNum = tonumber(getQuestStatus("bestineElection:electionNumber"))

	if (electionNum == nil) then
		self:setElectionNumber(1)
		return 1
	end

	return electionNum
end

function BestineElection:setElectionNumber(newNum)
	setQuestStatus("bestineElection:electionNumber", newNum)
end

function BestineElection:getElectionWinner(electionNumber)
	if (electionNumber <= 0) then
		return self.NONE
	end

	local winner = tonumber(getQuestStatus("bestineElection:electionWinner:" .. electionNumber))

	if (winner == nil) then
		self:setElectionWinner(electionNumber, self.NONE)
		return self.NONE
	end

	return winner
end

function BestineElection:setElectionWinner(electionNumber, newWinner)
	setQuestStatus("bestineElection:electionWinner:" .. electionNumber, newWinner)
end

function BestineElection:getPhaseTimeLeft()
	local eventID = getServerEventID("ElectionPhaseChange")

	if (eventID == nil) then
		return 0
	end

	return getServerEventTimeLeft(eventID) / 1000
end

function BestineElection:createNewVoterList()
	local electionNum = self:getElectionNumber()
	return createQuestVectorMap("BestineElectionVoterList" .. electionNum)
end

function BestineElection:getVoterList(electionNum)
	return getQuestVectorMap("BestineElectionVoterList" .. electionNum)
end

function BestineElection:addPlayerVote(pPlayer, vote)
	local electionNum = self:getElectionNumber()
	local pMap = self:getVoterList(electionNum)

	if (pMap == nil) then
		pMap = self:createNewVoterList()
	end

	local voterMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	if (not voterMap:hasMapRow(playerID)) then
		voterMap:addMapRow(playerID, tostring(vote))
	else
		printLuaError("Error in BestineElection:addPlayerVote, attempting to add existing player " .. SceneObject(pPlayer):getCustomObjectName() .. " to bestine election voter map.")
	end
end

function BestineElection:hasPlayerVoted(pPlayer)
	local electionNum = self:getElectionNumber()
	local pMap = self:getVoterList(electionNum)

	if (pMap == nil) then
		printLuaError("Error in BestineElection:hasPlayerVoted, attempting to get vote status for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on a non existant vote map.")
		return false
	end

	local voterMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	return voterMap:hasMapRow(playerID)
end

function BestineElection:getPlayerVote(pPlayer, electionNumOverride)
	local electionNum = self:getElectionNumber()

	if (electionNumOverride ~= nil and electionNumOverride ~= "") then
		electionNum = electionNumOverride
	end

	local pMap = self:getVoterList(electionNum)

	if (pMap == nil) then
		printLuaError("Error in BestineElection:getPlayerVote, attempting to get vote result for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on a non existant vote map.")
		return self.NONE
	end

	local voterMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	if (not voterMap:hasMapRow(playerID)) then
		return self.NONE
	end

	local playerVote = voterMap:getMapRow(playerID)

	return tonumber(playerVote)
end

function BestineElection:joinCampaign(pPlayer, candidate)
	if (pPlayer == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local electionNum = self:getElectionNumber()

	local keyString
	local campObj

	if (candidate == self.SEAN) then
		keyString = "joinedSeanCampaign"
		campObj = "object/tangible/loot/quest/sean_campaign_disk.iff"
	elseif (candidate == self.VICTOR) then
		keyString = "joinedVictorCampaign"
		campObj = "object/tangible/loot/quest/victor_campaign_disk.iff"
	else
		return
	end

	local pCampObj = giveItem(pInventory, campObj, -1)

	if (pCampObj == nil) then
		printLuaError("Error creating campaign disk for player " .. CreatureObject(pPlayer):getFirstName() .. " joining campaign " .. candidate)
		return
	end

	if (candidate == self.SEAN and BestineElection:hasJoinedCampaign(pPlayer, self.VICTOR)) then
		deleteScreenPlayData(pPlayer, "BestineElection", "joinedVictorCampaign")
	elseif (candidate == self.VICTOR and BestineElection:hasJoinedCampaign(pPlayer, self.SEAN)) then
		deleteScreenPlayData(pPlayer, "BestineElection", "joinedSeanCampaign")
	end

	writeScreenPlayData(pPlayer, "BestineElection", keyString, electionNum)
end

function BestineElection:hasJoinedCampaign(pPlayer, candidate)
	local electionNum = self:getElectionNumber()

	local keyString

	if (candidate == self.SEAN) then
		keyString = "joinedSeanCampaign"
	elseif (candidate == self.VICTOR) then
		keyString = "joinedVictorCampaign"
	else
		return
	end

	local lastVoteNum = tonumber(readScreenPlayData(pPlayer, "BestineElection", keyString))

	return lastVoteNum ~= nil and lastVoteNum == electionNum
end

function BestineElection:setReceivedElectionReward(pPlayer)
	local electionNum = self:getElectionNumber()
	writeScreenPlayData(pPlayer, "BestineElection", "ReceivedReward", electionNum)
end

function BestineElection:hasReceivedElectionReward(pPlayer)
	local curPhase = self:getCurrentPhase()

	if (curPhase ~= self.OFFICE_PHASE) then
		return true
	end

	local electionNum = self:getElectionNumber()

	return tonumber(readScreenPlayData(pPlayer, "BestineElection", "ReceivedReward")) == electionNum
end

function BestineElection:setInvFull(pPlayer, candidate, quest)
	if (pPlayer == nil) then
		return
	end

	local electionNum = BestineElection:getElectionNumber()

	local keyString

	if (candidate == self.SEAN) then
		keyString = "invFullSean"
	elseif (candidate == self.VICTOR) then
		keyString = "invFullVictor"
	else
		return
	end

	writeScreenPlayData(pPlayer, "BestineElection", keyString .. tostring(quest), tostring(electionNum))
end

function BestineElection:hadInvFull(pPlayer, candidate, quest)
	if (pPlayer == nil) then
		return false
	end

	local electionNum = BestineElection:getElectionNumber()

	local keyString

	if (candidate == self.SEAN) then
		keyString = "invFullSean"
	elseif (candidate == self.VICTOR) then
		keyString = "invFullVictor"
	else
		return
	end

	if (readScreenPlayData(pPlayer, "BestineElection", keyString .. tostring(quest)) ~= tostring(electionNum)) then
		self:clearInvFull(pPlayer, candidate, quest)
		return false
	else
		return true
	end
end

function BestineElection:clearInvFull(pPlayer, candidate, quest)
	if (pPlayer == nil) then
		return
	end

	local keyString

	if (candidate == self.SEAN) then
		keyString = "invFullSean"
	elseif (candidate == self.VICTOR) then
		keyString = "invFullVictor"
	else
		return
	end

	deleteScreenPlayData(pPlayer, "BestineElection", keyString .. tostring(quest))
end

function BestineElection:setQuestStep(pPlayer, candidate, quest, questStep)
	if (pPlayer == nil) then
		return
	end

	local keyString

	if (candidate == self.SEAN) then
		keyString = "seanQuest"
	elseif (candidate == self.VICTOR) then
		keyString = "victorQuest"
	else
		return
	end

	keyString = keyString .. ":" .. tostring(quest)

	local electionNum = BestineElection:getElectionNumber()

	if (readScreenPlayData(pPlayer, "BestineElection", keyString) ~= tostring(electionNum)) then
		writeScreenPlayData(pPlayer, "BestineElection", keyString, tostring(electionNum))
	end

	writeScreenPlayData(pPlayer, "BestineElection", keyString .. "Step", tostring(questStep))
end

function BestineElection:getQuestStep(pPlayer, candidate, quest)
	if (pPlayer == nil) then
		return 0
	end

	local keyString

	if (candidate == self.SEAN) then
		keyString = "seanQuest"
	elseif (candidate == self.VICTOR) then
		keyString = "victorQuest"
	else
		return
	end

	local electionNum = BestineElection:getElectionNumber()

	keyString = keyString .. ":" .. tostring(quest)

	if (readScreenPlayData(pPlayer, "BestineElection", keyString) ~= tostring(electionNum)) then
		return 0
	end

	local questStep = readScreenPlayData(pPlayer, "BestineElection", keyString .. "Step")

	if (questStep == nil or questStep == "") then
		return 0
	end

	return tonumber(questStep)
end

function BestineElection:setSearchedObject(pPlayer, objectName)
	local electionNum = self:getElectionNumber()
	writeScreenPlayData(pPlayer, "BestineElection", "searched_" .. objectName, electionNum)
end

function BestineElection:hasSearchedObject(pPlayer, objectName)
	local electionNum = self:getElectionNumber()

	return tonumber(readScreenPlayData(pPlayer, "BestineElection", "searched_" .. objectName)) == electionNum
end

TourContainerComponent = {}

function TourContainerComponent:transferObject(pContainer, pObj, slot)
	if (pContainer == nil) then
		return 0
	end

	spatialChat(pContainer, "@bestine:give_governor_item") -- What's this? Please, if you wish to present evidence or whatnot, don't just thrust these things at me. Speak to me in a manner suited to civilized beings such as ourselves.
	return 0
end

function TourContainerComponent:canAddObject(pContainer, pObj, slot)
	return false
end
