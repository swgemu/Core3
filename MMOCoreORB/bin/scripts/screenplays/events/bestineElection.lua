local ObjectManager = require("managers.object.object_manager")

BESTINE_ELECTION_ENABLED = 1

BestineElectionScreenPlay = ScreenPlay:new {
	CAMPAIGN_TIME = 3 * 60 * 1000,
	TUNE_TIME = 3 * 60 * 1000, -- 24 hours (TUNE = Time Until Next Election) Phase 2

	seanEvidence = {"object/tangible/loot/quest/sean_questp_ctestimony.iff", "object/tangible/loot/quest/sean_questp_mdisk.iff", "object/tangible/loot/quest/sean_questp_htestimony.iff"},
	victorEvidence = {"object/tangible/loot/quest/victor_questp_testimony.iff", "object/tangible/loot/quest/victor_questp_jregistry.iff", "object/tangible/loot/quest/victor_questp_receipt.iff"},
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
		self:spawnMobiles(1,true)
		self:setupTerminals()
		self:doPhaseInit()
	end
end

function BestineElectionScreenPlay:spawnMobiles(currentPhase,spawnStaticMobs)
	if (spawnStaticMobs == true) then
		local mobileTable = electionMobiles[0]

		for i = 1, #mobileTable, 1 do
			local mobile = mobileTable[i]
			--pNpc =        spawnMobile("lok", "mercenary",60,-24.251,-0.894991,22.5325,360.011,8145387)
			--{"bestine_rumor01",-1095.68,12,-3640.98,281, 0,"neutral",6,"bestineRumor01ConvoTemplate"},
			local pMobile = spawnMobile("tatooine", mobile[1], 0, mobile[2], mobile[3], mobile[4], mobile[5], mobile[6])
			if (pMobile ~= nil) then
				CreatureObject(pMobile):setPvpStatusBitmask(0)
				if (mobile[7] ~= "") then
					self:setMoodString(pMobile, mobile[7])
				end
				if (mobile[8] > 0) then
					local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), SceneObject(pMobile):getWorldPositionZ(), SceneObject(pMobile):getWorldPositionY(), mobile[8], 0)
					if (pActiveArea ~= nil) then
						local areaID = SceneObject(pActiveArea):getObjectID()
						writeData(areaID .. ":OwnerID", SceneObject(pMobile):getObjectID())
						createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "spawnApproach", pActiveArea)
					end
				end
				if (mobile[9] ~= "") then
					CreatureObject(pMobile):setOptionsBitmask(136)
					AiAgent(pMobile):setConvoTemplate(mobile[9])
				end
			end
		end
	end

	local mobileTable = electionMobiles[currentPhase]
	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]
		local pMobile = spawnMobile("tatooine", mobile[1], 0, mobile[2], mobile[3], mobile[4], mobile[5], mobile[6])
		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			if (mobile[7] ~= "") then
				self:setMoodString(pMobile, mobile[7])
			end
			if (self:isElectionEnabled()) then
				if (mobile[1] == "tour_aryon") then
					SceneObject(pMobile):setContainerComponent("TourContainerComponent")
				end
				if (mobile[1] == "hutt_informant") then
					writeData("bestine_election:hutt_informant", SceneObject(pMobile):getObjectID())
					local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", -1120, 12, -3639, 15,0)
					if (pActiveArea ~= nil) then
						createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "informantApproach", pActiveArea)
					end
				end
				if (mobile[8] > 0) then
					local pActiveArea = spawnActiveArea("tatooine", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), SceneObject(pMobile):getWorldPositionZ(), SceneObject(pMobile):getWorldPositionY(), mobile[8], 0)
					if (pActiveArea ~= nil) then
						local areaID = SceneObject(pActiveArea):getObjectID()
						writeData(areaID .. ":OwnerID", SceneObject(pMobile):getObjectID())
						createObserver(ENTEREDAREA, "BestineElectionScreenPlay", "spawnApproach", pActiveArea)
					end
				end
				if (mobile[9] ~= nil and mobile[9] ~= "") then
					CreatureObject(pMobile):setOptionsBitmask(136)
					AiAgent(pMobile):setConvoTemplate(mobile[9])
				end
			end

			local mobileID = SceneObject(pMobile):getObjectID()
			writeData("bestine:npc:object:" .. i, mobileID)
		end
	end
end

--local electionWinner = getQuestStatus("bestine_election:electionWinner")
--if (electionWinner == "sean") then
--self:spawnMerchants()
--end




-- Despawn and cleanup current phase mobiles.
function BestineElectionScreenPlay:despawnMobiles(currentPhase)
	local mobileTable = electionMobiles[currentPhase]
	for i = 1, #mobileTable, 1 do
		local objectID = readData("bestine:npc:object:" .. i)
		local pMobile = getSceneObject(objectID)

		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
			deleteData("bestine:npc:object:" .. i)
		end
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
	for i = 1, #seanMerchants do
		local npcData = seanMerchants[i]
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
	for i = 1, #seanMerchants do
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
	local mobileTable = electionMobiles[currentPhase]
	if (currentPhase == 1) then
		--self:despawnMobiles(currentPhase)
		setQuestStatus("bestine_election:currentPhase", 2)
		self:determineWinner()
		--self:spawnMobiles(2,false)
		if (not hasServerEvent("ElectionPhaseChange")) then
			self:createEvent(self.TUNE_TIME)
		end
	else
		--self:despawnMobiles(currentPhase)
		setQuestStatus("bestine_election:currentPhase", 1)
		--self:spawnMobiles(1,false)
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
			return (playerCampaign == electionNum)
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
		local votes = tonumber(getQuestStatus("bestine_election:votesFor" .. who))
		if (votes == nil) then
			votes = 0
		end

		votes = votes + 1
		setQuestStatus("bestine_election:votesFor" .. who, votes)

		local electionNum = self:getElectionNumber()
		if (who == "sean") then
			writeScreenPlayData(pPlayer, "BestineElection", "votedsean", electionNum)
		elseif(who == "victor") then
			writeScreenPlayData(pPlayer, "BestineElection", "votedvictor", electionNum)
		end

		self:removeEvidence(pPlayer, who)
		self:clearPoliticianData(pPlayer)
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
