local ObjectManager = require("managers.object.object_manager")


BESTINE_ELECTION_ENABLED = 1

BestineElectionScreenPlay = ScreenPlay:new {
	CAMPAIGN_TIME = 1 * 60 * 1000,
	TUNE_TIME = 3 * 60 * 1000, -- 24 hours (TUNE = Time Until Next Election) Phase 2

	seanEvidence = {"object/tangible/loot/quest/sean_questp_ctestimony.iff", "object/tangible/loot/quest/sean_questp_mdisk.iff", "object/tangible/loot/quest/sean_questp_htestimony.iff"},
	victorEvidence = {"object/tangible/loot/quest/victor_questp_testimony.iff", "object/tangible/loot/quest/victor_questp_jregistry.iff", "object/tangible/loot/quest/victor_questp_receipt.iff"},
}

registerScreenPlay("BestineElectionScreenPlay", true)

function BestineElectionScreenPlay:isElectionEnabled()
	return (BESTINE_ELECTION_ENABLED == 1)
end

function BestineElectionScreenPlay:doPhaseInit()
	if (not hasServerEvent("ElectionPhaseChange")) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		setQuestStatus("bestine:election:currentPhase", 1)
		createServerEvent(self.CAMPAIGN_TIME, "BestineElectionScreenPlay", "doPhaseChange", "ElectionPhaseChange")
	else
		local eventID = getServerEventID("ElectionPhaseChange")
		if (eventID == nil) then
			BestineElectionScreenPlay:doPhaseChange()
		end
	end
end

function BestineElectionScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		local currentPhase = BestineElectionScreenPlay:getCurrentPhase()
		BestineElectionScreenPlay:doPhaseInit()
		BestineElectionScreenPlay:spawnMobiles(currentPhase,true)
		BestineElectionScreenPlay:initTerminals()
	end
end

function BestineElectionScreenPlay:doPhaseChange()
	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return
	end
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local currentPhase = BestineElectionScreenPlay:getCurrentPhase()

	if (currentPhase == 1) then
		printf("[BestineElection] Election Ending - determining Winner\n")
		BestineElectionScreenPlay:determineWinner()
		setQuestStatus("bestine:election:currentPhase", 2)
		BestineElectionScreenPlay:updateMobiles(2)

		if (not hasServerEvent("ElectionPhaseChange")) then
			createServerEvent(self.TUNE_TIME, "BestineElectionScreenPlay", "doPhaseChange", "ElectionPhaseChange")
		else
			rescheduleServerEvent("ElectionPhaseChange", self.TUNE_TIME)
		end
	end

	if (currentPhase == 2) then
		setQuestStatus("bestine:election:currentPhase", 1)
		if (not hasServerEvent("ElectionPhaseChange")) then
			createServerEvent(self.CAMPAIGN_TIME, "BestineElectionScreenPlay", "doPhaseChange", "ElectionPhaseChange")
		else
			rescheduleServerEvent("ElectionPhaseChange", self.CAMPAIGN_TIME)
		end
		electionNum = electionNum + 1
		setQuestStatus("bestine:election:election_num", electionNum)
		setQuestStatus("bestine:election:seanVotes", 0)
		setQuestStatus("bestine:election:victorVotes", 0)
		BestineElectionScreenPlay:updateMobiles(1)
		printf("[BestineElection] New Election Starting - Election #" ..electionNum .."\n" )
	end
end

function BestineElectionScreenPlay:getCurrentPhase()
	local curPhase = tonumber(getQuestStatus("bestine:election:currentPhase"))

	if (curPhase == nil) then
		return 1
	end

	return curPhase
end

function BestineElectionScreenPlay:getElectionNumber()
	local electionNum = tonumber(getQuestStatus("bestine:election:election_num"))

	if (electionNum == nil) then
		setQuestStatus("bestine:election:election_num", 1)
		return 1
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
	local seanVotes = tonumber(getQuestStatus("bestine:election:seanVotes"))
	if (seanVotes == nil) then
		seanVotes = 0
	end

	local victorVotes = tonumber(getQuestStatus("bestine:election:victorVotes"))
	if (victorVotes == nil) then
		victorVotes = 0
	end
	---test
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if (electionNum % 2 == 0) then
		seanVotes = 55
	else
		victorVotes = 55
	end

	local electionWinner = ""

	if (seanVotes > victorVotes) then
		electionWinner = "sean"
		BestineElectionScreenPlay:despawnImperials()
		BestineElectionScreenPlay:spawnMerchants()
	elseif (seanVotes == victorVotes) then
		local chance = getRandomNumber(1, 2) --fixes Tie
		if (chance == 1) then
			electionWinner = "sean"
		end
	else electionWinner = "victor"
		BestineElectionScreenPlay:spawnImperials()
		BestineElectionScreenPlay:despawnMerchants()
	end
	setQuestStatus("bestine:election:electionWinner", electionWinner)
	printf("[BestineElection] Determining Winner: " ..electionWinner.. "!\n")
end


function BestineElectionScreenPlay:spawnMobiles(currentPhase,spawnStaticMobs)
	if (spawnStaticMobs == true) then
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
				if (BestineElectionScreenPlay:isElectionEnabled()) then
					if (mobile[8] > 0) then
						local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), SceneObject(pMobile):getWorldPositionZ(), SceneObject(pMobile):getWorldPositionY(), mobile[8], 0)
						if (pActiveArea ~= nil) then
							createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "spawnApproach", pActiveArea)
							local areaID = SceneObject(pActiveArea):getObjectID()
							local mobileID = SceneObject(pMobile):getObjectID()
							writeData(areaID..":activeArea",mobileID)
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

	local mobileTable = electionMobiles[currentPhase]
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
						createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "informantApproach", pActiveArea)
						writeData("bestine:npc:hutt_informant",mobileID)
					else
						createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "spawnApproach", pActiveArea)
						writeData("bestine:npc:object:" .. i, mobileID)
					end
					writeData(areaID .. ":activeArea",mobileID)
				end
			end

			CreatureObject(pMobile):setPvpStatusBitmask(0)
			if (mobile[7] ~= "") then
				self:setMoodString(pMobile, mobile[7])
			end
			if (BestineElectionScreenPlay:isElectionEnabled()) then
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

-- Despawn and cleanup current phase mobiles.
function BestineElectionScreenPlay:despawnMobiles(currentPhase)
	local mobileTable = electionMobiles[currentPhase]
	for i = 1, #mobileTable, 1 do
		local objectID = readData("bestine:npc:object:" .. i)
		local areaID = readData(objectID .. ":activeArea")
		local pMobile = getSceneObject(objectID)
		local pArea = getSceneObject(areaID)

		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
			deleteData("bestine:npc:object:" .. i)
		end
		if (pArea ~= nil) then
			SceneObject(pArea):destroyObjectFromWorld()
			deleteData(objectID .. ":activeArea")
		end
	end
end

function BestineElectionScreenPlay:spawnApproach(pActiveArea, pMovingObject)
	if (pActiveArea == nil) or (pMovingObject == nil) or (not SceneObject(pActiveArea):isActiveArea()) or (not SceneObject(pMovingObject):isCreatureObject()) then
		return 0
	end
	local areaID = SceneObject(pActiveArea):getObjectID()
	local mobileID = readData(areaID .. ":activeArea")
	local pMobile = getSceneObject(mobileID)
	if (pMobile ~= nil) then
		SceneObject(pMobile):faceObject(pMovingObject, true)
	end
	return 0
end

function BestineElectionScreenPlay:informantApproach(pActiveArea, pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isPlayerCreature()) then
		return 0
	end
	local areaID = SceneObject(pActiveArea):getObjectID()
	local mobileID = readData(areaID .. ":activeArea")
	--local mobileID = readData("bestine:npc:hutt_informant")
	local pMobile = getSceneObject(mobileID)
	if (pMobile ~= nil) then
		local pInventory = CreatureObject(pMovingObject):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true) ~= nil) then
				SceneObject(pMobile):faceObject(pMovingObject, true)
				spatialChat(pMobile, "@bestine:come_here") -- Hey... c'mere a second. I think we can help one another.
			end
		end
	end
	return 0
end

function BestineElectionScreenPlay:updateMobiles(phase)
	local currentPhase = BestineElectionScreenPlay:getCurrentPhase()
	local mobileTable = electionMobiles[phase]
	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]
		local objectID = readData("bestine:npc:object:" .. i)
		local pMobile = getSceneObject(objectID)
		if (pMobile ~= nil) then
			if (mobile[9] ~= "") then
				CreatureObject(pMobile):setOptionsBitmask(136)
				AiAgent(pMobile):setConvoTemplate(mobile[9])
			end
		end
	end
end

function BestineElectionScreenPlay:spawnMerchants()
	for i = 1, #seanMerchants do
		local npcData = seanMerchants[i]
		local pMobile = spawnMobile("tatooine", npcData[1], 0, npcData[2], npcData[3], npcData[4], npcData[5], 0)
		if (pMobile ~= nil) then
			local mobileID = SceneObject(pMobile):getObjectID()
			writeData("bestine:npc:merchants:" .. i, mobileID)
		end
	end
	local pSnd = spawnSceneObject("tatooine", "object/soundobject/soundobject_marketplace_large.iff", -1124, 12, -3695, 0, 0)
	if (pSnd ~= nil) then
		local mobileID = SceneObject(pSnd):getObjectID()
		writeData("bestine:object:marketsound", mobileID)
	end
end

function BestineElectionScreenPlay:despawnMerchants()
	for i = 1, #seanMerchants do
		local objectID = readData("bestine:npc:merchants:" .. i)
		local pMobile = getSceneObject(objectID)
		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
			deleteData("bestine:npc:merchants:" .. i)
		end
	end

	local marketSoundID = readData("bestine:object:marketsound")
	local pSnd = getSceneObject(marketSoundID)
	if (pSnd ~= nil) then
		SceneObject(pSnd):destroyObjectFromWorld()
		deleteData("bestine:object:marketsound")
	end
end

function BestineElectionScreenPlay:despawnImperials()
	for i = 1, #victorImperials do
		local objectID = readData("bestine:npc:imperials:" .. i)
		local pMobile = getSceneObject(objectID)
		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
			deleteData("bestine:npc:imperials:" .. i)
			deleteStringData(SceneObject(pMobile):getObjectID() .. ":name")
			deleteData(SceneObject(pMobile):getObjectID() .. ":currentLoc")
		end
	end
end

function BestineElectionScreenPlay:spawnImperials()
	for i = 1, #victorImperials do
		local npcData = victorImperials[i]
		local pMobile = spawnMobile("tatooine", npcData[1], 60, npcData[2], npcData[3], npcData[4], npcData[5], 0)
		if (pMobile ~= nil) then
			local mobileID = SceneObject(pMobile):getObjectID()
			writeData("bestine:npc:imperials:" .. i, mobileID)
			if (npcData[6] ~= "") then
				writeData(mobileID .. ":currentLoc", 1)
				writeStringData(mobileID .. ":name", npcData[6])
				createEvent(getRandomNumber(25,45) * 100, "BestineElectionScreenPlay", "BestinePatrol", pMobile, "")
				createObserver(DESTINATIONREACHED, "BestineElectionScreenPlay", "bestinePatrolDestReached", pMobile)
				AiAgent(pMobile):setAiTemplate("manualescortwalk") -- Don't move unless patrol point is added to list, walking speed
				AiAgent(pMobile):setFollowState(4) -- Patrolling
			end
		end
	end
end

function BestineElectionScreenPlay:bestinePatrolDestReached(pMobile)
	if (pMobile == nil) then
		return 0
	end

	local curLoc = readData(SceneObject(pMobile):getObjectID() .. ":currentLoc")

	if (curLoc == 1) then
		writeData(SceneObject(pMobile):getObjectID() .. ":currentLoc", 2)
	else
		writeData(SceneObject(pMobile):getObjectID() .. ":currentLoc", 1)
	end

	createEvent(1000, "BestineElectionScreenPlay", "BestinePatrol", pMobile, "")
	return 0
end



function BestineElectionScreenPlay:BestinePatrol(pMobile)
	if (pMobile == nil) then
		return
	end
	local mobileID = SceneObject(pMobile):getObjectID()
	local name = readStringData(mobileID .. ":name")
	local curLoc = readData(mobileID .. ":currentLoc")
	local nextLoc = {}

	if (name == "imp0") then
		if (curLoc == 1) then
			nextLoc = {-1117, 12, -3641, 0}
			elseif (curLoc == 2) then
			nextLoc = {-1086, 12, -3603, 0}
			--		elseif (curLoc == 3) then
			--		writeData(mobileID .. ":currentLoc", 4)
			--		elseif (curLoc == 4) then
			--		writeData(mobileID .. ":currentLoc", 1)
		end
	end

	if (name == "imp1") then
		if (curLoc == 1) then
			nextLoc = {-1166, 12, -3527, 0}
			else
			nextLoc = {-1088, 12, -3583, 0}
			end
	end

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):setNextPosition(nextLoc[1], nextLoc[2], nextLoc[3], nextLoc[4])
	AiAgent(pMobile):executeBehavior()
end

function BestineElectionScreenPlay:initTerminals()
	if (not BestineElectionScreenPlay:isElectionEnabled()) then
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


----Common Functions used by all the bestine election convo scripts
function BestineElectionScreenPlay:joinedCampaign(pPlayer, who)
	if (pPlayer ~= nil)  then
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", who .. "Campaign"))

		if (playerCampaign ~= nil) then
			local electionNum = BestineElectionScreenPlay:getElectionNumber()
			return (playerCampaign == electionNum)
		end
	end
	return false
end

function BestineElectionScreenPlay:votedCurrentElection(pPlayer, who)
	if (pPlayer ~= nil)  then
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "voted" .. who))

		if (playerCampaign ~= nil) then
			local electionNum = BestineElectionScreenPlay:getElectionNumber()
			return (playerCampaign == electionNum)
		end
	end
	return false
end


function BestineElectionScreenPlay:votingrewardCheck(pPlayer,who)
	if (pPlayer ~= nil) then
		local electionNum =  BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
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

	if BestineElectionScreenPlay:votedCurrentElection(pPlayer, "sean") or BestineElectionScreenPlay:votedCurrentElection(pPlayer, "victor") then
		return true
	end

	return false
end

function BestineElectionScreenPlay:canVote(pPlayer, who)
	if (pPlayer == nil) or (BestineElectionScreenPlay:hasVoted(pPlayer)) then
		return false
	end

	local templates = {}

	if BestineElectionScreenPlay:joinedCampaign(pPlayer, who) then
		if (who == "sean") then
			templates = self.seanEvidence
		elseif (who == "victor") then
			templates = self.victorEvidence
		end

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if(pInventory ~= nil) then
			for i = 1, # templates do
				local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)
				if (pInvItem ~= nil) then
					return true
				end
			end
		end
	end
	return false
end

function BestineElectionScreenPlay:castVote(pPlayer, who)
	if (pPlayer ~= nil)  then
		local votes = tonumber(getQuestStatus("bestine:election:" .. who.."Votes"))
		if (votes == nil) then
			votes = 0
		end

		votes = votes + 1
		setQuestStatus("bestine:election:" .. who.."Votes", votes)

		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (who == "sean") then
			writeScreenPlayData(pPlayer, "BestineElection", "votedsean", electionNum)
		elseif(who == "victor") then
			writeScreenPlayData(pPlayer, "BestineElection", "votedvictor", electionNum)
		end

		BestineElectionScreenPlay:removeEvidence(pPlayer, who)
		BestineElectionScreenPlay:clearPoliticianData(pPlayer)
	end
end

function BestineElectionScreenPlay:removeEvidence(pPlayer, who)
	if (pPlayer ~= nil) then
		local templates = { }
		if (who == "sean") then
			templates = self.seanEvidence
		elseif (who == "victor") then
			templates = self.victorEvidence
		end

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			for i = 1, # templates do
				local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)
				if (pInvItem ~= nil) then
					SceneObject(pInvItem):destroyObjectFromWorld()
					SceneObject(pInvItem):destroyObjectFromDatabase()
				end
			end
		end
	end
end

function BestineElectionScreenPlay:clearPoliticianData(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	deleteScreenPlayData(pPlayer, "BestineElection", "seanCampaign")
	deleteScreenPlayData(pPlayer, "BestineElection", "victorCampaign")
	deleteScreenPlayData(pPlayer, "BestineElection", "seanNegQuest")
	deleteScreenPlayData(pPlayer, "BestineElection", "victorNegQuest")
	deleteScreenPlayData(pPlayer, "BestineElection", "questp_term_searched")
	deleteScreenPlayData(pPlayer, "BestineElection", "questp_desk_searched")

	deleteData(playerID..":bestine:election:university_noroom")
	deleteData(playerID..":bestine:election:house_noroom")
	deleteData(playerID..":bestine:election:market_noroom")
	deleteData(playerID..":bestine:election:sean_noroom")
	deleteData(playerID..":bestine:election:victor_noroom")
	deleteData(playerID..":bestine:election:cantina_noroom")
	deleteData(playerID..":bestine:election:capitol_noroom")
	deleteData(playerID..":bestine:election:hospital_noroom")
	deleteData(playerID..":bestine:election:slums_noroom")
	deleteData(playerID..":bestine:election:museum_noroom")
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

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = readData(CreatureObject(pPlayer):getObjectID() .. ":bestine:election:" .. quest .. "_noroom")

	if (playerCampaign ~= nil) then
		return (playerCampaign == electionNum)
	end

	return false
end

function BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, who)
	if (pPlayer ~= nil) then
		if BestineElectionScreenPlay:votedCurrentElection(pPlayer, who) then
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
	local tblQuest = BestineElectionScreenPlay:parseString(strTerminalName,"_")

	if (tblQuest[2] == "questn" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, tblQuest[1])) then
		return true
	elseif (tblQuest[2] == "questp" and BestineElectionScreenPlay:joinedCampaign(pPlayer,tblQuest[1])) then
		return true
	end
	return false
end

function BestineElectionScreenPlay.has(theTable, theElement)
	for _,v in pairs(theTable) do
		if v == theElement then
			return true
		end
	end
	return false
end

function BestineElectionScreenPlay.parseString(str, pattern)
	local t = {}
	local fpat = "(.-)" .. pattern
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

--when players try to drop evidence on Tour
TourContainerComponent = {}

function TourContainerComponent:transferObject(pContainer, pObj, slot)
	local template = SceneObject(pObj):getTemplateObjectPath()

	if BestineElectionScreenPlay.has(BestineElectionScreenPlay.seanEvidence, template) or BestineElectionScreenPlay.has(BestineElectionScreenPlay.victorEvidence, template) then
		spatialChat(pContainer, "@bestine:give_governor_item") -- What's this? Please, if you wish to present evidence or whatnot, don't just thrust these things at me. Speak to me in a manner suited to civilized beings such as ourselves.
	end
	return 0
end


