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

function seanTrenwellConvoHandler:seanNegQuest(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = readData(playerID..":bestine_election:seanNegQuest")
	return (playerCampaign ~= nil) and (playerCampaign >= electionNum)
end

function seanTrenwellConvoHandler:gaveDiskToHutt(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local playerCampaign = readData(playerID..":bestine_election:hutt")
	return (playerCampaign > 0)
end

function seanTrenwellConvoHandler:doNegativeQuests(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()
	writeData(playerID..":bestine_election:seanNegQuest",electionNum)
	deleteData(playerID..":bestine_election:VictorCampaign")
end

function seanTrenwellConvoHandler:hasNegativeEvidence(pPlayer)
	if pPlayer == nil then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	return (pInventory ~= nil) and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_hlist.iff" , true)
	or getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_dseal.iff", true)
	or getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", true)
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
	if (pPlayer == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
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
		writeData(playerID..":bestine_election:SeanCampaign",electionNum)
		deleteData(playerID..":bestine_election:VictorCampaign")
		deleteData(playerID..":bestine_election:victorNegQuest")
		deleteData(playerID..":bestine_election:seanNegQuest")
	end
	return
end

function seanTrenwellConvoHandler:giveElectionReward(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()

	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		electionNum = electionNum - 1
	end
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		createLoot(pInventory, "bestine_election_sean_trenwell_rewards", 0, true)
	end
	writeData(playerID .. ":bestine_election:receivedSeanReward", electionNum)
	deleteData(playerID..":bestine_election:VotedSean")
end

function seanTrenwellConvoHandler:GiveHistoryReward(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		local reward = giveItem(pInventory, "object/tangible/painting/bestine_history_quest_painting.iff", -1)
		if (reward == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item bestine_history_quest_painting.iff")
			return
		end
	end

	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		electionNum = electionNum - 1
	end

	writeData(playerID.."bestine_election:completedSeanHistoryQuest",electionNum)
	deleteData(playerID..":bestine_election:disk_destroyed")
	deleteData(playerID.."bestine_election:sean_historyreward_noroom")
end

function seanTrenwellConvoHandler:giveHistoryQuest(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	writeData(playerID .. ":bestine_election:SeanHistoryQuest",electionNum)
	deleteData(playerID.."bestine_election:completedSeanHistoryQuest")
	historyWaypointID = PlayerObject(pGhost):addWaypoint("tatooine", "Historical Site", "", -758, -3907, WAYPOINT_COLOR_BLUE, true, true, 0,0)
	writeData(playerID .. ":bestine_election:historyWaypointID", historyWaypointID)
end

function seanTrenwellConvoHandler:removeHistoryQuest(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	if (pGhost == nil) then
		return
	end
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local wayID = readData(playerID .. ":bestine:historyWaypointID")
	PlayerObject(pGhost):removeWaypoint(wayID, true)
	deleteData(playerID .. ":bestine_election:SeanHistoryQuest",electionNum)
	deleteData(playerID .. ":bestine_election:historyWaypointID")
end

function seanTrenwellConvoHandler:giveContactQuest(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	if (pGhost == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	writeData(playerID .. ":bestine_election:seanContact",1)
	deleteData(playerID .. ":bestine_election:itemFound")
	contactWaypointID = PlayerObject(pObj):addWaypoint("tatooine", "Sean's Contact", "", -1448, -3765, WAYPOINT_COLOR_BLUE, true, true, 0,0)
	writeData(playerID .. ":bestine_election:contactWaypointID", contactWaypointID)
end

function seanTrenwellConvoHandler:canDoHistoryQuest(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()
	if (readData(playerID .. ":bestine_election:SeanHistoryQuest") == 0) then
		if (readData(playerID .. ":bestine_election:find") == 0) then
			if (readData(playerID .. ":bestine_election:itemFound") == 0) then
				if (readData(playerID..":bestine_election:seanContact") == 0) then
					if (readData(playerID..":bestine_election:disk_destroyed")==0) then
						if (readData(playerID.."bestine_election:completedSeanHistoryQuest") == 0) then
							return true
						else
							local playerCampaign = readData(playerID..":bestine_election:completedSeanHistoryQuest")
							if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
								electionNum = electionNum - 1
							end
							if (playerCampaign < electionNum) then
								return true;
							end
						end
					end
				end
			end
		end
	end
	return false
end

function seanTrenwellConvoHandler:historyItemfound (pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	if (readData(playerID .. ":bestine_election:itemFound") == 1) then
		if getQuestStatus("bestine_election:electionWinner") == "Sean" then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if pInventory ~= nil then
				hasDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff", true)
				if hasDisk ~= nil then
					return true
				end
			end
		end
	end
	return false;
end

function seanTrenwellConvoHandler:checkForvoteReward(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()

	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		electionNum = electionNum - 1
	end
	local playerCampaign = readData(playerID..":bestine_election:VotedSean")
	return (playerCampaign <= electionNum)
end

function seanTrenwellConvoHandler:receivedElectionReward(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()

	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		electionNum = electionNum - 1
	end

	local playerCampaign = readData(playerID..":bestine_election:receivedSeanReward")
	return (playerCampaign <= electionNum)
end


function seanTrenwellConvoHandler:inOffice_newElection(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		if (not BestineElectionScreenPlay:votedSean(pPlayer)) and (notBestineElectionScreenPlay:votedVictor(pPlayer)) then
			return true
		end
	end
	return false
end

function seanTrenwellConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()

	if self:gaveDiskToHutt(pPlayer) then
		return convoTemplate:getScreen("disk_to_hutt")
	end

	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		if self:hasNoRoomVar(pPlayer) then
			return convoTemplate:getScreen("returned_noroom")
		end
		if BestineElectionScreenPlay:votedSean(pPlayer) then
			return convoTemplate:getScreen("voted_sean_this_election")
		end
		if BestineElectionScreenPlay:joinedSeanCampaign(pPlayer) then
			return convoTemplate:getScreen("ask_voted")
		end
		if BestineElectionScreenPlay:votedVictor(pPlayer) then
			return convoTemplate:getScreen("voted_victor_this_election")
		end
		if BestineElectionScreenPlay:joinedVictorCampaign(pPlayer) then
			return convoTemplate:getScreen("rival_player")
		end
		if self:seanNegQuest(pPlayer) then
			return convoTemplate:getScreen("nquest_return")
		end
		if BestineElectionScreenPlay:votedSean(pPlayer) then
			return convoTemplate:getScreen("voted_sean_this_election")
		end

		if BestineElectionScreenPlay:votedVictor(pPlayer) then
			return convoTemplate:getScreen("voted_victor_this_election")
		end
	end

	if (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		if getQuestStatus("bestine_election:electionWinner") == "Sean" then
			if BestineElectionScreenPlay:votedVictor(pPlayer) then
				return convoTemplate:getScreen("voted_victor_this_election")
			end
		 return convoTemplate:getScreen("sean_inOffice")
		end

		if getQuestStatus("bestine_election:electionWinner") == "Victor" then
			if BestineElectionScreenPlay:votedVictor(pPlayer) then
				return convoTemplate:getScreen("voted_victor_this_election")
			end
			return convoTemplate:getScreen("notInOffice_noElection")
		end
	end
	return convoTemplate:getScreen("convo_start")
end


function seanTrenwellConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(conversingPlayer):getObjectID()
	--if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
	if screenID == "returned_noroom" then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_ff7aeed7","noroom_returned_noroom")-- Yes, that was me. (noroom)
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
		writeData(playerID..":bestine_blection:sean_noroom",electionNum)
	end

	if screenID == "action_nquest" then
		self:doNegativeQuests(conversingPlayer)
	end
	--end -- PHASE1

	--if (BestineElectionScreenPlay:getCurrentPhase() == 2) then
	if screenID == "sean_inOffice" then
		if seanTrenwellConvoHandler:checkForvoteReward(conversingPlayer) then
			if self:receivedElectionReward(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_alreadyReceivedReward") --Now that you're in office, I've come to ask about the reward you promised.
			elseif BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward_noroom") --Now that you're in office, I've come to ask about the reward you promised.
			else
				clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward") --Now that you're in office, I've come to ask about the reward you promised.
			end
		end

		if readData(playerID .. ":bestine_election:disk_destroyed") > 0 then
			if (readData(playerID.."bestine_election:sean_historyreward_noroom") > 0) then
				if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
					clonedConversation:addOption("@conversation/sean_trenwell:s_9fa98668","inOffice_giveHistoryReward_noroom_returned")--You said to return for a reward. For destroying that dis
				else
					clonedConversation:addOption("@conversation/sean_trenwell:s_9fa98668","inOffice_giveHistoryReward")--You said to return for a reward. For destroying that disk.
				end
			else
				clonedConversation:addOption("@conversation/sean_trenwell:s_a3734170","historyQuest_SpokeToContact")--I spoke to your contact about the disk from the crash site.
			end
		end

		if (readData(playerID..":bestine_election:seanContact") > 0) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_49368633","historyQuest_HasDisk")--What was I supposed to do with this disk from the crash site?
		end

		if readData(playerID .. ":bestine_election:itemFound") > 0 then
			clonedConversation:addOption("@conversation/sean_trenwell:s_238ef4f6","historyQuest_SearchedCrashSite")--I've searched the crash site.
		end

		if (readData(playerID .. ":bestine_election:find") > 0) then
			if getQuestStatus("bestine_election:electionWinner") == "Sean" then
				clonedConversation:addOption("@conversation/sean_trenwell:s_a068d8f2","historyQuest_SeanHistorian")--Who do I let screen anything I find at the crash site?
			end
		end

		if (readData(playerID .. ":bestine_election:SeanHistoryQuest") > 0) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_35bc21ba","historyQuest_CrashSite")--What did you want me to do at the crash site?
		end

		if self:canDoHistoryQuest(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_6a0bba8c","inOffice_yourPlans")-- Do you have any special plans for while you're in office?
		end

		if BestineElectionScreenPlay:votedSean(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_811e4ed1","inOffice_playerVoted")
		end
		clonedConversation:addOption("@conversation/sean_trenwell:s_81f9db80","inOffice_HowsWork")--Just thought I'd see what the local government was up to.

		if self:inOffice_newElection(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_3ab76f84","inOffice_newElection")--I hear you're up for re-election. How's the campaign going
		end
	end

	if screenID == "inOffice_giveReward" then
		self:GiveHistoryReward(conversingPlayer)
	end

	if screenID == "historyQuest_SpokeToContact" then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_a907268e","historyQuest_DestroyedDisk_noroom")--Yes, the disk has been taken care of.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_a907268e","historyQuest_DestroyedDisk")--Yes, the disk has been taken care of.
		end
	end
	if (screenID == "historyQuest_DestroyedDisk_noroom") then
		writeData(playerID.."bestine_election:sean_historyreward_noroom",1)
	end
	if (screenID == "historyQuest_DestroyedDisk") then
		self:GiveHistoryReward(conversingPlayer)
	end

	if (screenID == "HistoryQuest_SeansContact") then
		self:giveContactQuest(conversingPlayer)
	end

	if (screenID == "historyQuest_SearchedCrashSite") then
		if (readData(playerID .. ":bestine_election:itemFound") > 0) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_b30bd73c","SearchedCrashSite_Found")--Yes, I did.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_c8a36ac7","SearchedCrashSite_NotFound") --No, unfortunately. Nothing of use.
		end
	end

	if screenID == "inOffice_accept_HQuest" then
		self:giveHistoryQuest(conversingPlayer)
	end

	if screenID == "historyQuest_CrashSite_quit" then
		self:removeHistoryQuest(conversingPlayer)
	end
	--end
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

