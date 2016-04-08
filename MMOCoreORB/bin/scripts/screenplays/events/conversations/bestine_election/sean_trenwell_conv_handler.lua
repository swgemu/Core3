local ObjectManager = require("managers.object.object_manager")

seanTrenwellConvoHandler = Object:new {	}


local negativeEvidence = {"object/tangible/loot/quest/victor_questn_hlist.iff","object/tangible/loot/quest/victor_questn_dseal.iff","object/tangible/loot/quest/victor_questn_journal.iff"}
local historyReward = "object/tangible/painting/bestine_history_quest_painting.iff"

function seanTrenwellConvoHandler:gaveDiskToHutt(pPlayer)
	if (pPlayer ~= nil) then
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "hutt"))
		return (playerCampaign ~= nil) and (playerCampaign > 0)
	end
	return false
end

function seanTrenwellConvoHandler:inOffice_newElection(pPlayer)
	local playerCampaign = 0
	if (BestineElectionScreenPlay:getCurrentPhase() ~= 1) then
		return false
	end

	if (not BestineElectionScreenPlay:votedForWho(pPlayer,"Sean")) and (not BestineElectionScreenPlay:votedForWho(pPlayer,"Victor")) then
		return true
	end

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "VotedSean"))
	if playerCampaign == nil then
		playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "VotedVictor"))
		if playerCampaign == nil then
			return false
		end
		if ( electionNum ~= playerCampaign ) then
			return true
		end
	end
	return false;
end

function seanTrenwellConvoHandler:hasNegativeEvidence(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			for i = 1, #negativeEvidence do
				local pInvItem = getContainerObjectByTemplate(pInventory, negativeEvidence[i], true)
				if pInvItem ~= nil then
					return true
				end
			end
		end
	end
	return false
end

function seanTrenwellConvoHandler:removeEvidence(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			for i = 1, #negativeEvidence do
				local pInvItem = getContainerObjectByTemplate(pInventory, negativeEvidence[i], true)
				if pInvItem ~= nil then
					SceneObject(pInvItem):destroyObjectFromWorld()
					SceneObject(pInvItem):destroyObjectFromDatabase()
				end
			end
		end
	end
end

function seanTrenwellConvoHandler:giveDiskandJoinCampaign(pPlayer)
	if (pPlayer ~= nil) then
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
			self:removeEvidence(pPlayer)
			writeScreenPlayData(pPlayer, "BestineElection", "SeanCampaign", electionNum)
			deleteScreenPlayData(pPlayer, "BestineElection", "VictorCampaign")
			deleteScreenPlayData(pPlayer, "BestineElection", "VictorNegQuest")
			deleteScreenPlayData(pPlayer, "BestineElection", "SeanNegQuest")
			deleteScreenPlayData(pPlayer,"BestineElection", "questp_term_searched")
			deleteScreenPlayData(pPlayer,"BestineElection", "questp_desk_searched")
		end
	end
end


function seanTrenwellConvoHandler:checkForVoteReward(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "receivedSeanReward"))
	if (playerCampaign ~= nil) then
		return (playerCampaign == electionNum)
	end
	return false
end

function seanTrenwellConvoHandler:giveElectionReward(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			createLoot(pInventory, "bestine_election_sean_trenwell_rewards", 0, true)
		end
		writeScreenPlayData(pPlayer, "BestineElection", "receivedSeanReward", electionNum)
		deleteScreenPlayData(pPlayer, "BestineElection" , "VotedSean")
	end
end

function seanTrenwellConvoHandler:giveHistoryQuest(pPlayer)
	if (pPlayer ~= nil) then
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			CreatureObject(pPlayer):setScreenPlayState(4, "bestine_history_quest")
			local historyWaypointID = PlayerObject(pPlayerObj):addWaypoint("tatooine", "Historical Site", "", -758, -3907, WAYPOINT_COLOR_BLUE, true, true, 0,0)
			writeData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:historyWaypointID", historyWaypointID)
		end
	end
end

function seanTrenwellConvoHandler:removeHistoryQuest(pPlayer)
	if (pPlayer ~= nil) then
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			local wayID = readData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:historyWaypointID")
			PlayerObject(pPlayerObj):removeWaypoint(wayID, true)
			deleteData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:historyWaypointID")
			CreatureObject(pPlayer):removeScreenPlayState(2, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(4, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(8, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(16, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(32, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(64, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(128, "bestine_history_quest")
		end
	end
end

function seanTrenwellConvoHandler:giveContactQuest(pPlayer)
	if (pPlayer ~= nil) then
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			local contactWaypointID = PlayerObject(pPlayerObj):addWaypoint("tatooine", "Sean's Contact", "", -1448, -3765, WAYPOINT_COLOR_BLUE, true, true, 0,0)
			writeData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:contactWaypointID", contactWaypointID)
		end
	end
end


function seanTrenwellConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if self:gaveDiskToHutt(pPlayer) then
		return convoTemplate:getScreen("disk_to_hutt")
	elseif BestineElectionScreenPlay:noroomReturned(pPlayer, "Sean") then
		return convoTemplate:getScreen("returned_noroom")
	elseif BestineElectionScreenPlay:joinedCampaign(pPlayer, "Sean") then
		return convoTemplate:getScreen("ask_voted")
	elseif BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Sean") then
		return convoTemplate:getScreen("nquest_return")
	elseif BestineElectionScreenPlay:joinedCampaign(pPlayer, "Victor") then
		return convoTemplate:getScreen("rival_player")
	elseif BestineElectionScreenPlay:votedForWho(pPlayer, "Sean") then
		return convoTemplate:getScreen("voted_sean_this_election")
	elseif BestineElectionScreenPlay:votedForWho(pPlayer, "Victor") then
		return convoTemplate:getScreen("voted_victor_this_election")
	elseif getQuestStatus("bestine_election:electionWinner") == "Sean" then
		return convoTemplate:getScreen("sean_inOffice")
	elseif getQuestStatus("bestine_election:electionWinner") == "Victor" then
		if BestineElectionScreenPlay:votedForWho(pPlayer, "Victor") then
			return convoTemplate:getScreen("voted_victor_this_election")
		else
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
		local playerID = CreatureObject(conversingPlayer):getObjectID()
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			if screenID == "returned_noroom" then
				if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
					clonedConversation:addOption("@conversation/sean_trenwell:s_ff7aeed7","noroom_returned_noroom")-- Yes, that was me. (noroom)
				else
					clonedConversation:addOption("@conversation/sean_trenwell:s_ff7aeed7","join_campaign") -- Yes, that was me. (maderoom)
				end
				clonedConversation:addOption("@conversation/sean_trenwell:s_5ef87080","returned_noroom_nojoin")--I've thought about it and no longer want to join your campaign.
			elseif screenID == "ask_voted" then
				if BestineElectionScreenPlay:votedForWho(conversingPlayer, "Sean") then
					clonedConversation:addOption("@conversation/sean_trenwell:s_d1f385de","checkForVote_true") --It went well. I voted for you.
				else
					clonedConversation:addOption("@conversation/sean_trenwell:s_d1f385de","checkForVote_false") --It went well. I voted for you.
				end
				clonedConversation:addOption("@conversation/sean_trenwell:s_e7ffff2","get_going") --I think I'm going to get going.
				clonedConversation:addOption("@conversation/sean_trenwell:s_8b63bfe1","cant_find_evidence") --I can't find evidence.
			elseif screenID == "nquest_return" then
				if self:hasNegativeEvidence(conversingPlayer) then
					clonedConversation:addOption("@conversation/sean_trenwell:s_338ea1e3","nquest_found") --Yes, I did. Here you are.
				else
					clonedConversation:addOption("@conversation/sean_trenwell:s_da9a29e9","nquest_notfound") --No, not yet.
				end
			elseif screenID == "nquest_found" then
				if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
					clonedConversation:addOption("@conversation/sean_trenwell:s_641d98d5","joincampaign_noroom") --Yes, of course!
				else
					clonedConversation:addOption("@conversation/sean_trenwell:s_641d98d5","join_campaign") --Yes, of course!
				end
				clonedConversation:addOption("@conversation/sean_trenwell:s_fe8dd35a","nquest_nojoin")--No, I changed my mind.
			elseif screenID == "here_to_vote2" then
				if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
					clonedConversation:addOption("@conversation/sean_trenwell:s_ef067f71","no_inventory_space")--Alright. I want to join your campaign.
				else
					clonedConversation:addOption("@conversation/sean_trenwell:s_ef067f71","join_campaign")--Alright. I want to join your campaign.
					deleteData(playerID..":bestine_election:Sean_noroom")
				end
				clonedConversation:addOption("@conversation/sean_trenwell:s_5c46daeb","changed_my_mind")--I've changed my mind.
				clonedConversation:addOption("@conversation/sean_trenwell:s_dea56128","have_to_go")--I have to go.
			elseif screenID == "join_campaign" then
				self:giveDiskandJoinCampaign(conversingPlayer)
			elseif screenID == "no_inventory_space" then
				writeData(playerID..":bestine_election:Sean_noroom",electionNum)
			elseif screenID == "action_nquest" then
				writeScreenPlayData(conversingPlayer, "BestineElection", "SeanNegQuest", electionNum)
				deleteScreenPlayData(conversingPlayer, "BestineElection", "VictorCampaign")
				deleteScreenPlayData(conversingPlayer,"BestineElection", "questn_term_searched")
				deleteScreenPlayData(conversingPlayer,"BestineElection", "questn_desk_searched")
			end
		end

		if (BestineElectionScreenPlay:getCurrentPhase() == 2) then
			if screenID == "sean_inOffice" then
				if BestineElectionScreenPlay:noroomReturned(conversingPlayer, "history") then
					if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
						clonedConversation:addOption("@conversation/sean_trenwell:s_9fa98668","inOffice_giveHistoryReward_noroom_returned")--You said to return for a reward. For destroying that dis
					else
						clonedConversation:addOption("@conversation/sean_trenwell:s_9fa98668","inOffice_giveHistoryReward")--You said to return for a reward. For destroying that disk.
					end
				end

				if seanTrenwellConvoHandler:checkForVoteReward(conversingPlayer) then
					if self:checkForVoteReward(conversingPlayer) then
						clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_alreadyReceivedReward") --Now that you're in office, I've come to ask about the reward you promised.
					elseif BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
						clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward_noroom") --Now that you're in office, I've come to ask about the reward you promised.
					else
						clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward") --Now that you're in office, I've come to ask about the reward you promised.
					end
				end

				if CreatureObject(conversingPlayer):hasScreenPlayState(64, "bestine_history_quest") then
					clonedConversation:addOption("@conversation/sean_trenwell:s_a3734170","historyQuest_SpokeToContact")--I spoke to your contact about the disk from the crash site.
				end

				if CreatureObject(conversingPlayer):hasScreenPlayState(32, "bestine_history_quest") then
					clonedConversation:addOption("@conversation/sean_trenwell:s_49368633","historyQuest_HasDisk")--What was I supposed to do with this disk from the crash site?
				end

				if CreatureObject(conversingPlayer):hasScreenPlayState(16, "bestine_history_quest") then
					clonedConversation:addOption("@conversation/sean_trenwell:s_238ef4f6","historyQuest_SearchedCrashSite")--I've searched the crash site.
				end

				if self:checkForVoteReward(conversingPlayer) then
					clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_alreadyReceivedReward") --Now that you're in office, I've come to ask about the reward you promised.
				elseif BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
					clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward_noroom") --Now that you're in office, I've come to ask about the reward you promised.
				else
					clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward") --Now that you're in office, I've come to ask about the reward you promised.
				end

				if CreatureObject(conversingPlayer):hasScreenPlayState(8, "bestine_history_quest") then
					if getQuestStatus("bestine_election:electionWinner") == "Sean" then
						clonedConversation:addOption("@conversation/sean_trenwell:s_a068d8f2","historyQuest_SeanHistorian")--Who do I let screen anything I find at the crash site?
					end
				end
			end
			if screenID == "inOffice_giveReward" then
				seanTrenwellConvoHandler:giveElectionReward(conversingPlayer)
			end
			if screenID == "inOffice_accept_HQuest" then
				self:giveHistoryQuest(conversingPlayer)
			end

			if screenID == "historyQuest_CrashSite_quit" then
				self:removeHistoryQuest(conversingPlayer)
			end

			if CreatureObject(conversingPlayer):hasScreenPlayState(4, "bestine_history_quest") then
				clonedConversation:addOption("@conversation/sean_trenwell:s_35bc21ba","historyQuest_CrashSite")--What did you want me to do at the crash site?
			end
			--if CreatureObject(conversingPlayer):hasScreenPlayState(2, "bestine_history_quest") then
				clonedConversation:addOption("@conversation/sean_trenwell:s_6a0bba8c","inOffice_yourPlans")-- Do you have any special plans for while you're in office?
			--end
			if BestineElectionScreenPlay:votedForWho(conversingPlayer,"Sean") then
				clonedConversation:addOption("@conversation/sean_trenwell:s_811e4ed1","inOffice_playerVoted") ----I heard and greatly appreciate it! When the election is over, if I win I'd like to thank you for your support. Come back and speak to me if that happens.
			end
			clonedConversation:addOption("@conversation/sean_trenwell:s_81f9db80","inOffice_HowsWork")--Just thought I'd see what the local government was up to.
			if self:inOffice_newElection(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_3ab76f84","inOffice_newElection")--I hear you're up for re-election. How's the campaign going
			end
		end
		print(screenID)
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
