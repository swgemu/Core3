local ObjectManager = require("managers.object.object_manager")

victorVisalisConvoHandler = Object:new {
		themePark = nil
}

function victorVisalisConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function victorVisalisConvoHandler:hasNoRoomVar(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	playerCampaign = readData(playerID..":bestine_election:victor_noroom")
	return (playerCampaign ~= nil) and (playerCampaign >= electionNum)
end

function victorVisalisConvoHandler:hasNQuestVar(pPlayer)
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		local playerID = CreatureObject(pPlayer):getObjectID()
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local playerCampaign = tonumber(readScreenPlayData(pPlayer,"BestineElection","VictorNegativeQuests"))
		if (playerCampaign ~= nil) then 
			return (playerCampaign >= electionNum)
		end
	end
	return false
end


function victorVisalisConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()
	
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		if self:hasNoRoomVar(pPlayer) then
			return convoTemplate:getScreen("returned_noroom")
		end

		if self:hasNQuestVar(pPlayer) then
			return convoTemplate:getScreen("nquest_return")
		end
		
		if BestineElectionScreenPlay:SeanCampaign(pPlayer) then
			return convoTemplate:getScreen("rival_player")
		end

		if BestineElectionScreenPlay:votedSean(pPlayer) then
			return convoTemplate:getScreen("voted_sean_this_election")
		end

		if BestineElectionScreenPlay:VictorCampaign(pPlayer) then		
			return convoTemplate:getScreen("ask_voted")
		end

		return convoTemplate:getScreen("convo_start")
	end

	if electionPhase == 2 then
		--TODO: Phase 2
	 	return convoTemplate:getScreen("noOffice_noElection")
	end
	return convoTemplate:getScreen("noOffice_noElection")
end

function victorVisalisConvoHandler:doNegativeQuests(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	writeScreenPlayData(pPlayer,"BestineElection","VictorNegativeQuests", electionNum)
	deleteScreenPlayData(pPlayer,"BestineElection","SeanCampaign")
	deleteScreenPlayData(pPlayer,"BestineElection","nquest_searched")
end

function victorVisalisConvoHandler:hasNegativeEvidence(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		if getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_gpapers.iff" , true) then
			return true
	 elseif getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff", true) then
			return true
      elseif getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_alog.iff", true) then
			return true
		end
	end
	return false
end

function victorVisalisConvoHandler:removeNegativeEvidence(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		local evidenceItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_gpapers.iff", true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
		evidenceItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff", true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
		evidenceItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_alog.iff", true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
	end
end

function victorVisalisConvoHandler:giveDiskandJoinCampaign(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return
	end

	local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_campaign_disk.iff", -1)
	if (pDisk == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item victor_campaign_disk.iff")
		return
	end
	self:removeNegativeEvidence(pPlayer)
	writeScreenPlayData(pPlayer,"BestineElection","VictorCampaign", electionNum)
	deleteScreenPlayData(pPlayer,"BestineElection","SeanCampaign")
	deleteScreenPlayData(pPlayer,"BestineElection","victor_noroom")
	deleteScreenPlayData(pPlayer,"BestineElection","sean_noroom")
	deleteScreenPlayData(pPlayer,"BestineElection","VictorNegativeQuests")
	deleteScreenPlayData(pPlayer,"BestineElection","SeanNegativeQuests")
	deleteScreenPlayData(pPlayer,"BestineElection","nquest_searched")
	deleteScreenPlayData(pPlayer,"BestineElection","already_searched")
	return
end

function victorVisalisConvoHandler:GiveMainReward(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			createLoot(pInventory, victor_visalis_rewards, 0, true)
			writeScreenPlayData(pPlayer,"BestineElection","RewardGivenVictor", electionNum)
			deleteScreenPlayData(pPlayer,"BestineElection","votedVictor")
			return
		end
	end
end

function victorVisalisConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(conversingPlayer):getObjectID()

	if screenID == "nquest_return" then
		if self:hasNegativeEvidence(conversingPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_6ac98e49","nquest_found") --I have it, yes.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_da9a29e9","nquest_notfound")--No, not yet.
	 	end
	end

	if screenID == "nquest_found" then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_9e0196ed","joincampaign_noroom") --Yes, I am sure.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_9e0196ed","nquest_joincampaign") --Yes, I am sure.
		end
			clonedConversation:addOption("@conversation/victor_visalis:s_5c46daeb","neg_quests_changed_mind")--I've changed my mind.
	end

	if screenID == "givedisk_joincampaign" then
		self:giveDiskandJoinCampaign(conversingPlayer)
	end

	if screenID == "nquest_joincampaign" then
		self:giveDiskandJoinCampaign(conversingPlayer)
	end

	if screenID == "here_to_vote3" then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_5492e753","joincampaign_noroom") --I wish to join your campaign.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_5492e753","givedisk_joincampaign")--I wish to join your campaign.
		end
			clonedConversation:addOption("@conversation/victor_visalis:s_d041eb82","changed_mind")--I don't want to join your campaign.
			clonedConversation:addOption("@conversation/victor_visalis:s_9201d81b","need_to_go")--I have to go. Bye!
	end

	if screenID == "returned_noroom" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_c82e9a2f","returned_stillnoroom")--Yes, please.
			else
				clonedConversation:addOption("@conversation/victor_visalis:s_c82e9a2f","returned_maderoom") -- Yes, please.
			end
				clonedConversation:addOption("@conversation/victor_visalis:s_ee26e33e","need_to_go")--No thanks!
	end

	if screenID == "returned_maderoom" then
			giveDiskandJoinCampaign(conversingPlayer)
	end

	if screenID == "joincampaign_noroom" then
			readData(playerID..":bestine_election:victor_noroom")
	end

	if screenID == "ask_voted" then
		if BestineElectionScreenPlay:votedVictor(conversingPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7","checkForVote_true") -- Yes and I voted for you.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7","checkForVote_false") -- Yes and I voted for you.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_6cf7afee","need_to_go")--I should go.
		clonedConversation:addOption("@conversation/victor_visalis:s_700330a5","cant_find_evidence")--I can't find evidence.
	end
	if screenID == "returned_stillnoroom" then
		writeData(playerID..":bestine_election:victor_noroom")
	end

	if screenID == "action_nquest" then
			self:doNegativeQuests(conversingPlayer)
	end

	return conversationScreen
end

function victorVisalisConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()

	local pLastConversationScreen = nil

	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)

		return conversationTemplate:getScreen(optionLink)
	end

	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end

