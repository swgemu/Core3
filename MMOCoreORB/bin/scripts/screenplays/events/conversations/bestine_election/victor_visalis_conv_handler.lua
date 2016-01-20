local ObjectManager = require("managers.object.object_manager")

victorVisalisConvoHandler = Object:new {
		themePark = nil
}

function victorVisalisConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function victorVisalisConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()	
	local electionPhase = BestineElectionScreenPlay:getCurrentPhase()

	if electionPhase == 1 then
		if self:hasNoRoomVar(pPlayer) then 
			return convoTemplate:getScreen("returned_noroom")
		elseif self:hasNQuestVar(pPlayer) then
			return convoTemplate:getScreen("nquest_return")
		elseif tonumber(getQuestStatus(playerID..":bestine_election:SeanCampaign")) == electionNum then
			return convoTemplate:getScreen("rival_player")
		elseif tonumber(getQuestStatus(playerID..":bestine_election:VictorCampaign")) == electionNum then
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

function victorVisalisConvoHandler:hasNQuestVar(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:VictorNegativeQuests"))
	return (playerCampaign == electionNum)
end

function victorVisalisConvoHandler:hasNoRoomVar(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:victor_noroom"))
	return (playerCampaign == electionNum)
end


function victorVisalisConvoHandler:doNegativeQuests(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	setQuestStatus(playerID..":bestine_election:VictorNegativeQuests",electionNum)
	setQuestStatus(playerID..":bestine_election:SeanCampaign",0)
	removeQuestStatus(playerID..":bestine_election:searched")
	removeQuestStatus(playerID..":bestine_election:already_searched")
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
	setQuestStatus(playerID..":bestine_election:VictorCampaign",electionNum)
	removeQuestStatus(playerID..":bestine_election:SeanCampaign")
	removeQuestStatus(playerID..":bestine_election:victor_noroom")
	removeQuestStatus(playerID..":bestine_election:VictorNegativeQuests")
	removeQuestStatus(playerID..":bestine_election:searched")
	removeQuestStatus(playerID..":bestine_election:already_searched")
	return
end

function victorVisalisConvoHandler:checkVictorVote(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if tonumber(getQuestStatus(playerID..":bestine_election:VictorCampaign")) == electionNum then
		local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:votedVictor"))
		return (playerCampaign == electionNum)
	end			
end

function victorVisalisConvoHandler:GiveMainReward(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	
	if (pPlayer == nil) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return
	end
	createLoot(pInventory, victor_visalis_rewards, 0, true)
	setQuestStatus(playerID.."bestine_election:RewardGivenVictor",electionNum)
	removeQuestStatus(playerID.."bestine_election:votedVictor")
	return
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
			setQuestStatus(playerID..":bestine_election:victor_noroom",electionNum)
	end

	if screenID == "ask_voted" then
		if self:checkVictorVote(conversingPlayer) == true then	
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7","checkForVote_true") -- Yes and I voted for you.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7","checkForVote_false") -- Yes and I voted for you.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_6cf7afee","need_to_go")--I should go.
		clonedConversation:addOption("@conversation/victor_visalis:s_700330a5","cant_find_evidence")--I can't find evidence.	
	end
	if screenID == "returned_stillnoroom" then
		setQuestStatus(playerID..":bestine_election:victor_noroom",electionNum)
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

