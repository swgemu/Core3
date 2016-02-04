local ObjectManager = require("managers.object.object_manager")

seanTrenwellConvoHandler = Object:new {
		themePark = nil
}

function seanTrenwellConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function seanTrenwellConvoHandler:hasNoRoomVar(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	playerCampaign = readData(playerID..":bestine_election:sean_noroom")
	return (playerCampaign ~= nil) and (playerCampaign >= electionNum)
end

function seanTrenwellConvoHandler:hasNQuestVar(pPlayer)
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		local playerID = CreatureObject(pPlayer):getObjectID()
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local playerCampaign = tonumber(readScreenPlayData(pPlayer,"BestineElection","SeanNegativeQuests"))
		if (playerCampaign ~= nil) then 
			return (playerCampaign >= electionNum)
		end
	end
	return false
end

function seanTrenwellConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()	
	local playerID = CreatureObject(pPlayer):getObjectID()

	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		if seanTrenwellConvoHandler:gaveDiskToHutt(pPlayer) then
			return convoTemplate:getScreen("disk_to_hutt")
		end

		if seanTrenwellConvoHandler:hasNoRoomVar(pPlayer) then
			return convoTemplate:getScreen("returned_noroom")
		end
		if BestineElectionScreenPlay:votedSean(pPlayer) then
			return convoTemplate:getScreen("voted_sean_this_election")
		end
		if BestineElectionScreenPlay:SeanCampaign(pPlayer) then
			return convoTemplate:getScreen("ask_voted")
		end
		if BestineElectionScreenPlay:votedVictor(pPlayer) then
			return convoTemplate:getScreen("voted_victor_this_election")
		end
		if BestineElectionScreenPlay:VictorCampaign(pPlayer) then
			return convoTemplate:getScreen("rival_player")
		end
		if seanTrenwellConvoHandler:hasNQuestVar(pPlayer) then
			return convoTemplate:getScreen("nquest_return")
		end
		if BestineElectionScreenPlay:votedSean(pPlayer) then
			return convoTemplate:getScreen("voted_sean_this_election")
		end

		if BestineElectionScreenPlay:votedVictor(pPlayer) then
			return convoTemplate:getScreen("voted_victor_this_election")
		end
		return convoTemplate:getScreen("convo_start")
	end
	if electionPhase == 2 then
		--TODO: Phase 2
	 	return convoTemplate:getScreen("notInOffice_noElection")
	end
	return convoTemplate:getScreen("notInOffice_noElection")
end

function seanTrenwellConvoHandler:gaveDiskToHutt(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(readScreenPlayData(pPlayer,"BestineElection","hutt"))
	if (playerCampaign ~= nil) then 
		return (playerCampaign >= electionNum)
	end
	return false
end

function seanTrenwellConvoHandler:doNegativeQuests(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	writeScreenPlayData(pPlayer,"BestineElection","SeanNegativeQuests", electionNum)
	deleteScreenPlayData(pPlayer,"BestineElection","VictorCampaign")
	deleteScreenPlayData(pPlayer,"BestineElection","nquest_searched")
end

function seanTrenwellConvoHandler:hasNegativeEvidence(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		if getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_hlist.iff" , true) then
			return true
		elseif getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_dseal.iff", true) then
			return true
		elseif getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", true) then
			return true
		end
	end
	return false
end

function seanTrenwellConvoHandler:removeEvidence(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		local evidenceItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_hlist.iff" , true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
		evidenceItem = getContainerObjectByTemplate(pInventory,"object/tangible/loot/quest/victor_questn_dseal.iff", true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
		evidenceItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", true)
		if evidenceItem ~= nil then
			SceneObject(evidenceItem):destroyObjectFromWorld()
			SceneObject(evidenceItem):destroyObjectFromDatabase()
		end
	end
	return
end

function seanTrenwellConvoHandler:giveDiskandJoinCampaign(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory == nil) then
		return
	end
	local pDisk = giveItem(pInventory, "object/tangible/loot/quest/sean_campaign_disk.iff", -1)
	if (pDisk == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item sean_campaign_disk.iff")
		return
	end
	local rivalDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_campaign_disk.iff" , true)
	if rivalDisk ~= nil then
		SceneObject(rivalDisk):destroyObjectFromWorld()
		SceneObject(rivalDisk):destroyObjectFromDatabase()
	end
	seanTrenwellConvoHandler:removeEvidence(pPlayer)
	writeScreenPlayData(pPlayer,"BestineElection","SeanCampaign", electionNum)
	deleteScreenPlayData(pPlayer,"BestineElection","VictorCampaign")
	deleteScreenPlayData(pPlayer,"BestineElection","sean_noroom")
	deleteScreenPlayData(pPlayer,"BestineElection","victor_noroom")
	deleteScreenPlayData(pPlayer,"BestineElection","VictorNegativeQuests")
	deleteScreenPlayData(pPlayer,"BestineElection","SeanNegativeQuests")
	deleteScreenPlayData(pPlayer,"BestineElection","nquest_searched")
	deleteScreenPlayData(pPlayer,"BestineElection","history_searched")
	return
end

function seanTrenwellConvoHandler:GiveMainReward(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			createLoot(pInventory, sean_trenwell_rewards, 0, true)
			writeScreenPlayData(pPlayer,"BestineElection","RewardGivenSean", electionNum)
			deleteScreenPlayData(pPlayer,"BestineElection","VotedSean")
			return
		end
	end
end

function seanTrenwellConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(conversingPlayer):getObjectID()


	if screenID == "returned_noroom" then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_ff7aeed7","returned_noroom_still")-- Yes, that was me. (noroom)
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_ff7aeed7","join_campaign") -- Yes, that was me. (maderoom)
		end
		clonedConversation:addOption("@conversation/sean_trenwell:s_5ef87080","returned_noroom_nojoin")--I've thought about it and no longer want to join your campaign.
	end

	if screenID == "ask_voted" then
		if BestineElectionScreenPlay:votedSean(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_d1f385de","checkForVote_true") --It went well. I voted for you.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_d1f385de","checkForVote_false") --It went well. I voted for you.
		end
		clonedConversation:addOption("@conversation/sean_trenwell:s_e7ffff2","get_going")--I think I'm going to get going.
		clonedConversation:addOption("@conversation/sean_trenwell:s_8b63bfe1","cant_find_evidence")--I can't find evidence.
	end

	if screenID == "nquest_return" then
		if self:hasNegativeEvidence(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_338ea1e3","nquest_found") --Yes, I did. Here you are.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_da9a29e9","nquest_notfound") --No, not yet.
	 	end
	end

	if screenID == "nquest_found" then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_641d98d5","joincampaign_noroom") --Yes, of course!
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_641d98d5","join_campaign") --Yes, of course!
		end
			clonedConversation:addOption("@conversation/sean_trenwell:s_fe8dd35a","nquest_nojoin")--No, I changed my mind.
	end
	if screenID == "here_to_vote2" then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_ef067f71","no_inventory_space")--Alright. I want to join your campaign.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_ef067f71","join_campaign")--Alright. I want to join your campaign.
			removeQuestStatus(playerID..":bestine_election:sean_noroom")
		end
			clonedConversation:addOption("@conversation/sean_trenwell:s_5c46daeb","changed_my_mind")--I've changed my mind.
			clonedConversation:addOption("@conversation/sean_trenwell:s_dea56128","have_to_go")--I have to go.
	end

	if screenID == "join_campaign" then
		self:giveDiskandJoinCampaign(conversingPlayer)
	end
	if screenID == "no_inventory_space" then
		writeScreenPlayData(conversingPlayer,"BestineElection","sean_noroom",electionNum)
	end

	if screenID == "action_nquest" then
			self:doNegativeQuests(conversingPlayer)
	end
	return conversationScreen
end

function seanTrenwellConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

