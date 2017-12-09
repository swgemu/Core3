local ObjectManager = require("managers.object.object_manager")

BestineElection = ScreenPlay:new {
	electionEnabled = true,

	electionDuration = 24 * 60 * 60 * 1000, -- Duration of the election phase
	timeTilNextElection = 24 * 60 * 60 * 1000, -- Time until next election, starts immediately after an election ends

	seanEvidence = {"object/tangible/loot/quest/sean_questp_ctestimony.iff", "object/tangible/loot/quest/sean_questp_mdisk.iff", "object/tangible/loot/quest/sean_questp_htestimony.iff"},
	victorEvidence = {"object/tangible/loot/quest/victor_questp_testimony.iff", "object/tangible/loot/quest/victor_questp_jregistry.iff", "object/tangible/loot/quest/victor_questp_receipt.iff"},


	-- Constants for candidates
	NONE = 0,
	SEAN = 1,
	VICTOR = 2
}

registerScreenPlay("BestineElection", true)

function BestineElection:isElectionEnabled()
	return self.electionEnabled
end

function BestineElection:doPhaseInit()
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
		self:spawnStaticMobiles()
		self:spawnPhaseMobiles(currentPhase)
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
		self:despawnPhaseMobiles(1)
		self:spawnPhaseMobiles(2)
		self:setCurrentPhase(2)

		if (not hasServerEvent("ElectionPhaseChange")) then
			createServerEvent(self.timeTilNextElection, "BestineElection", "doPhaseChange", "ElectionPhaseChange")
		else
			rescheduleServerEvent("ElectionPhaseChange", self.timeTilNextElection)
		end
	elseif (currentPhase == 2) then
		self:despawnPhaseMobiles(2)
		self:spawnPhaseMobiles(1)
		self:setSeanVotes(0)
		self:setVictorVotes(0)

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

function BestineElection:spawnStaticMobiles()
	local mobileTable = electionMobiles[0]

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
						createObserver(ENTEREDAREA, "BestineElection", "enteredMobileArea", pActiveArea)
						local areaID = SceneObject(pActiveArea):getObjectID()
						local mobileID = SceneObject(pMobile):getObjectID()
						writeData(mobileID .. ":activeArea", areaID)
						writeData(areaID .. ":mobileID", mobileID)
					end
				end

				if (mobile[9] ~= "") then
					CreatureObject(pMobile):setOptionsBitmask(136)
					AiAgent(pMobile):setConvoTemplate(mobile[9])
				end
			end
		end
	end
end

function BestineElection:spawnPhaseMobiles(currentPhase)
	local mobileTable = electionMobiles[currentPhase]

	if (mobileTable == nil) then
		return
	end

	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]

		local pMobile = spawnMobile("tatooine", mobile[1], 0, mobile[2], mobile[3], mobile[4], mobile[5], mobile[6])

		if (pMobile ~= nil) then
			local mobileID = SceneObject(pMobile):getObjectID()

			if (mobile[8] > 0) then
				local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), SceneObject(pMobile):getWorldPositionZ(), SceneObject(pMobile):getWorldPositionY(), mobile[8], 0)

				if (pActiveArea ~= nil) then
					local areaID = SceneObject(pActiveArea):getObjectID()

					if (mobile[1] == "hutt_informant") then
						createObserver(ENTEREDAREA, "BestineElection", "enteredInformantArea", pActiveArea)
						writeData("bestineElection:npc:hutt_informant",mobileID)
					else
						createObserver(ENTEREDAREA, "BestineElection", "enteredMobileArea", pActiveArea)
						writeData("bestineElection:npc:" .. i, mobileID)
					end

					writeData(areaID .. ":mobileID", mobileID)
					writeData(mobileID .. ":areaID", areaID)
				end
			end

			CreatureObject(pMobile):setPvpStatusBitmask(0)

			if (mobile[7] ~= "") then
				self:setMoodString(pMobile, mobile[7])
			end

			if (BestineElection:isElectionEnabled()) then
				if (mobile[1] == "tour_aryon") then
					SceneObject(pMobile):setContainerComponent("TourContainerComponent")
				end

				if (mobile[9] ~= nil and mobile[9] ~= "") then
					CreatureObject(pMobile):setOptionsBitmask(136)
					AiAgent(pMobile):setConvoTemplate(mobile[9])
				end
			end
		end
	end
end

function BestineElection:despawnPhaseMobiles(currentPhase)
	local mobileTable = electionMobiles[currentPhase]

	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]
		local objectID

		if (mobileTable[1] == "hutt_informant") then
			objectID = readData("bestineElection:npc:hutt_informant")
			deleteData("bestineElection:npc:hutt_informant")
		else
			objectID = readData("bestineElection:npc:" .. i)
			deleteData("bestineElection:npc:" .. i)
		end

		local areaID = readData(objectID .. ":activeArea")

		deleteData(objectID .. ":areaID")
		deleteData(areaID .. ":mobileID")

		local pMobile = getSceneObject(objectID)

		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
		end

		local pArea = getSceneObject(areaID)

		if (pArea ~= nil) then
			SceneObject(pArea):destroyObjectFromWorld()
		end
	end
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
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionTerminalMenuComponent")
		--writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "victor_questp_jregistry")
	end

	pTerminal = getSceneObject(4475517) --4475517 victors desk - gives object/tangible/loot/quest/victor_questn_journal.iff
	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionDeskMenuComponent")
		--writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "victor_questn_journal")
	end

	pTerminal = getSceneObject(5565563) --terminal in seans office gives "object/tangible/loot/quest/sean_questn_tdisk.iff"
	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionTerminalMenuComponent")
		--writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "sean_questn_tdisk")
	end

	pTerminal = getSceneObject(5565562) --desk in seans office gives "object/tangible/loot/quest/sean_questn_alog.iff"
	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("BestineElectionDeskMenuComponent")
		--writeStringData(SceneObject(pTerminal):getObjectID() .. ":name", "sean_questn_alog")
	end

	pTerminal = getSceneObject(3195507)
	local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pTerminal):getWorldPositionX(), SceneObject(pTerminal):getWorldPositionZ(), SceneObject(pTerminal):getWorldPositionY(), 2, 0)
	if pActiveArea ~= nil then
	--createObserver(ENTEREDAREA, "BestineElection", "triggerHistoryTerminal", pActiveArea)
	end
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
			local playerVote = voterMap:getMapRow(playerID)

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

	local pInventory = CreatureObject(pMovingObject):getSlottedObject("inventory")

	if (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true) ~= nil) then
		SceneObject(pMobile):faceObject(pMovingObject, true)
		spatialChat(pMobile, "@bestine:come_here") -- Hey... c'mere a second. I think we can help one another.
	end

	return 0
end

function BestineElection:hasCandidateEvidence(pPlayer, candidate)
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

	for i = 1, #templates, 1 do
		local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)

		if (pInvItem ~= nil) then
			return true
		end
	end

	return false
end

function BestineElection:canVoteForCandidate(pPlayer, candidate)
	--return self:hasJoinedCampaign(pPlayer, candidate) and self:hasCandidateEvidence(pPlayer, candidate)
	return self:hasCandidateEvidence(pPlayer, candidate)
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

--------------------------------------------------------------------------
-- Functions below handle reading/writing of the main screenplay variables
--------------------------------------------------------------------------
function BestineElection:getCurrentPhase()
	local curPhase = tonumber(getQuestStatus("bestineElection:currentPhase"))

	if (curPhase == nil) then
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

function BestineElection:getPlayerVote(pPlayer)
	local electionNum = self:getElectionNumber()
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
	local electionNum = self:getElectionNumber()

	local keyString

	if (candidate == self.SEAN) then
		keyString = "votedForSean"
	elseif (candidate == self.VICTOR) then
		keyString = "votedForVictor"
	else
		return
	end

	writeScreenPlayData(pPlayer, "BestineElection", keyString, electionNum)
end

function BestineElection:hasJoinedCampaign(pPlayer, candidate)
	local electionNum = self:getElectionNumber()

	local keyString

	if (candidate == self.SEAN) then
		keyString = "votedForSean"
	elseif (candidate == self.VICTOR) then
		keyString = "votedForVictor"
	else
		return
	end

	local lastVoteNum = tonumber(readScreenPlayData(pPlayer, "BestineElection", keyString))

	return lastVoteNum ~= nil and lastVoteNum == electionNum
end
