local ObjectManager = require("managers.object.object_manager")

seanTrenwellConvoHandler = conv_handler:new {
	}

--			ScreenPlayState(1, "bestine_history_quest") hasHistoryQuest
--			ScreenPlayState(2, "bestine_history_quest") talked to historian and can search
--			ScreenPlayState(4, "bestine_history_quest") found something
--			ScreenPlayState(8, "bestine_history_quest") let historian screen the find
--			ScreenPlayState(16, "bestine_history_quest") spoke to sean and received contact quest
--			ScreenPlayState(32, "bestine_history_quest") spoke to contact & destroyed the disk

local negativeEvidence = {"object/tangible/loot/quest/victor_questn_hlist.iff","object/tangible/loot/quest/victor_questn_dseal.iff","object/tangible/loot/quest/victor_questn_journal.iff"}

function seanTrenwellConvoHandler:gaveDiskToHutt(pPlayer)
	if (pPlayer ~= nil) then
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "gaveDisktoHutt"))
		if (playerCampaign ~= nil) then
			if playerCampaign > 0 then
				return true
			end
		end
	end
	return false
end

function seanTrenwellConvoHandler:hasNegativeEvidence(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			for i = 1, #negativeEvidence do
				local pInvItem = getContainerObjectByTemplate(pInventory, negativeEvidence[i], true)
				if (pInvItem ~= nil) then
					return true
				end
			end
		end
	end
	return false
end

function seanTrenwellConvoHandler:canDoHistoryQuest(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	if not CreatureObject(pPlayer):hasScreenPlayState(1, "bestine_history_quest") then
		if not CreatureObject(pPlayer):hasScreenPlayState(2, "bestine_history_quest") then
			if not CreatureObject(pPlayer):hasScreenPlayState(4, "bestine_history_quest") then
				if not CreatureObject(pPlayer):hasScreenPlayState(8, "bestine_history_quest") then
					if not CreatureObject(pPlayer):hasScreenPlayState(16, "bestine_history_quest") then
						if not CreatureObject(pPlayer):hasScreenPlayState(32, "bestine_history_quest") then
							if not BestineElectionScreenPlay:noroomReturned(pPlayer, "history") then
								local playerQuest = tonumber(readScreenPlayData(pPlayer, "BestineElection", "completedHistoryQuest"))
								if (playerQuest == nil) then
									return true
								else
									local currentElection = BestineElectionScreenPlay:getElectionNumber()
									if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
										currentElection = currentElection - 1
									end
									if (playerQuest < currentElection) then
										return true
									end
								end
							end
						end
					end
				end
			end
		end
	end
	return false
end

function seanTrenwellConvoHandler:giveHistoryQuest(pPlayer)
	if (pPlayer ~= nil) then
		deleteScreenPlayData(pPlayer, "BestineElection", "completedHistoryQuest")
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			CreatureObject(pPlayer):setScreenPlayState(1, "bestine_history_quest")
			local historyWaypointID = PlayerObject(pPlayerObj):addWaypoint("tatooine", "Historical Site", "", -758, -3907, WAYPOINT_COLOR_BLUE, true, true, 0,0)
			writeData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:historyWaypointID", historyWaypointID)
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


function seanTrenwellConvoHandler:removeHistoryQuest(pPlayer)
	if (pPlayer ~= nil) then
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			local wayID = readData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:historyWaypointID")
			PlayerObject(pPlayerObj):removeWaypoint(wayID, true)
			deleteData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:historyWaypointID")
			CreatureObject(pPlayer):removeScreenPlayState(1, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(2, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(4, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(8, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(16, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(32, "bestine_history_quest")
		end
	end
end

function seanTrenwellConvoHandler:checkForVoteReward(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum =  BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "votedsean"))
		if (playerCampaign ~= nil) then
			if (playerCampaign <= electionNum) then
				return true
			end
		end
	end
	return false
end

function seanTrenwellConvoHandler:checkRewardGiven(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum =  BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "receivedSeanReward"))
		if (playerCampaign ~= nil) then
			if (playerCampaign <= electionNum) then
				return true
			end
		end
	end
	return false
end

function seanTrenwellConvoHandler:giveVoteReward(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			createLoot(pInventory, "bestine_election_sean_trenwell_rewards", 0, true)
		end
		writeScreenPlayData(pPlayer, "BestineElection", "receivedSeanReward", electionNum)
		deleteScreenPlayData(pPlayer, "BestineElection" , "votedsean")
	end
end

function seanTrenwellConvoHandler:giveHistoryReward(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local reward = giveItem(pInventory, "object/tangible/painting/bestine_history_quest_painting.iff",-1)
			if (reward == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item bestine_history_quest_painting.iff")
				return
			end
		end
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		writeScreenPlayData(pPlayer, "BestineElection", "completedHistoryQuest", electionNum)
		deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:history_noroom")
		CreatureObject(pPlayer):removeScreenPlayState(32, "bestine_history_quest")
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
			if BestineElectionScreenPlay:isOnNegativeQuest(pPlayer,"sean") then
				for i = 1, #negativeEvidence do
					local pInvItem = getContainerObjectByTemplate(pInventory, negativeEvidence[i], true)
					if pInvItem ~= nil then
						SceneObject(pInvItem):destroyObjectFromWorld()
						SceneObject(pInvItem):destroyObjectFromDatabase()
					end
				end
			end
			writeScreenPlayData(pPlayer, "BestineElection", "seanCampaign", electionNum)
			deleteScreenPlayData(pPlayer, "BestineElection", "seanNegQuest")
			deleteScreenPlayData(pPlayer, "BestineElection", "victorCampaign")
			deleteScreenPlayData(pPlayer, "BestineElection", "victorNegQuest")
			deleteScreenPlayData(pPlayer, "BestineElection", "questp_term_searched")
			deleteScreenPlayData(pPlayer, "BestineElection", "questp_desk_searched")
			self:removeHistoryQuest(pPlayer)
		end
	end
end

function seanTrenwellConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()

	local clonedConversation = LuaConversationScreen(pConvScreen)

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()

	local electionWinner = getQuestStatus("bestine_election:electionWinner")
	local phase = tonumber(getQuestStatus("bestine_election:currentPhase"))

	if (screenID == "returned_noroom") then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_ff7aeed7","noroom_returned_noroom")-- Yes, that was me. (noroom)
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_ff7aeed7","join_campaign") -- Yes, that was me. (maderoom)
		end
		clonedConversation:addOption("@conversation/sean_trenwell:s_5ef87080","returned_noroom_nojoin")--I've thought about it and no longer want to join your campaign.
	elseif (screenID == "nquest_return") then
		if self:hasNegativeEvidence(pPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_338ea1e3","nquest_found") --Yes, I did. Here you are.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_da9a29e9","nquest_notfound") --No, not yet.
		end
	elseif (screenID == "nquest_found") then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_641d98d5","joincampaign_noroom") --Yes, of course!
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_641d98d5","join_campaign") --Yes, of course!
		end
		clonedConversation:addOption("@conversation/sean_trenwell:s_fe8dd35a","nquest_nojoin")--No, I changed my mind.
	elseif (screenID == "here_to_vote_continue") then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_ef067f71","joincampaign_noroom")--Alright. I want to join your campaign.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_ef067f71","join_campaign")--Alright. I want to join your campaign.
			deleteData(playerID..":bestine_election:sean_noroom")
		end
		clonedConversation:addOption("@conversation/sean_trenwell:s_5c46daeb","joincampaign_changedmind")--I've changed my mind.
		clonedConversation:addOption("@conversation/sean_trenwell:s_dea56128","have_to_go")--I have to go.
	elseif (screenID == "ask_voted") then
		if BestineElectionScreenPlay:votedFor(pPlayer, "sean") then
			clonedConversation:addOption("@conversation/sean_trenwell:s_d1f385de","checkForVote_true") --It went well. I voted for you.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_d1f385de","checkForVote_false") --It went well. I voted for you.
		end
		clonedConversation:addOption("@conversation/sean_trenwell:s_e7ffff2","get_going") --I think I'm going to get going.
		clonedConversation:addOption("@conversation/sean_trenwell:s_8b63bfe1","cant_find_evidence") --I can't find evidence.
	elseif (screenID == "action_nquest") then
		writeScreenPlayData(pPlayer, "BestineElection", "seanNegQuest", electionNum)
		deleteScreenPlayData(pPlayer, "BestineElection", "victorCampaign")
		deleteScreenPlayData(pPlayer,"BestineElection", "questn_term_searched")
		deleteScreenPlayData(pPlayer,"BestineElection", "questn_desk_searched")
	elseif (screenID == "sean_inOffice") then
		if BestineElectionScreenPlay:noroomReturned(pPlayer, "history") then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_9fa98668","inOffice_giveHistoryReward_noroom_returned")--You said to return for a reward. For destroying that dis
			else
				clonedConversation:addOption("@conversation/sean_trenwell:s_9fa98668","inOffice_giveHistoryReward")--You said to return for a reward. For destroying that disk.
			end
		end
		if self:canDoHistoryQuest(pPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_6a0bba8c","inOffice_yourPlans")-- Do you have any special plans for while you're in office?
		elseif CreatureObject(pPlayer):hasScreenPlayState(1, "bestine_history_quest") then
			clonedConversation:addOption("@conversation/sean_trenwell:s_35bc21ba","historyQuest_CrashSite")--What did you want me to do at the crash site?
		elseif CreatureObject(pPlayer):hasScreenPlayState(2, "bestine_history_quest") or CreatureObject(pPlayer):hasScreenPlayState(4, "bestine_history_quest") then
			clonedConversation:addOption("@conversation/sean_trenwell:s_a068d8f2","historyQuest_SeanHistorian")--Who do I let screen anything I find at the crash site?
		elseif CreatureObject(pPlayer):hasScreenPlayState(8, "bestine_history_quest") then
			clonedConversation:addOption("@conversation/sean_trenwell:s_238ef4f6","historyQuest_SearchedCrashSite")--I've searched the crash site.
		elseif CreatureObject(pPlayer):hasScreenPlayState(16, "bestine_history_quest") then
			clonedConversation:addOption("@conversation/sean_trenwell:s_49368633","historyQuest_HasDisk")--What was I supposed to do with this disk from the crash site?
		elseif CreatureObject(pPlayer):hasScreenPlayState(32, "bestine_history_quest") then
			clonedConversation:addOption("@conversation/sean_trenwell:s_a3734170","historyQuest_SpokeToContact")--I spoke to your contact about the disk from the crash site.
		end

		if (phase == 1) then
			if BestineElectionScreenPlay:votedFor(pPlayer,"sean") then
				clonedConversation:addOption("@conversation/sean_trenwell:s_811e4ed1","inOffice_playerVoted") --I voted for you in this election.
			elseif  (not BestineElectionScreenPlay:hasVoted(pPlayer)) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_3ab76f84","inOffice_newElection")--I hear you're up for re-election. How's the campaign going
			end
		end

		if self:checkForVoteReward(pPlayer) then
			if self:checkRewardGiven(pPlayer) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_alreadyReceivedReward") --Now that you're in office, I've come to ask about the reward you promised.
			elseif BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward_noroom") --Now that you're in office, I've come to ask about the reward you promised.
			else
				clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward") --Now that you're in office, I've come to ask about the reward you promised.
			end
		end
		clonedConversation:addOption("@conversation/sean_trenwell:s_81f9db80","inOffice_HowsWork")--Just thought I'd see what the local government was up to.
	elseif (screenID == "join_campaign") then
		self:giveDiskandJoinCampaign(pPlayer)
	elseif (screenID == "joincampaign_noroom") then
		writeData(playerID..":bestine_election:sean_noroom",electionNum)
	elseif (screenID == "inOffice_giveReward") then
		self:giveVoteReward(pPlayer)
	elseif (screenID == "inOffice_accept_HQuest") then
		self:giveHistoryQuest(pPlayer)
	elseif (screenID == "historyQuest_CrashSite") then
	elseif (screenID == "historyQuest_CrashSite_quit") then
		self:removeHistoryQuest(pPlayer)
	elseif (screenID == "HistoryQuest_SeansContact") then
		CreatureObject(pPlayer):removeScreenPlayState(8, "bestine_history_quest")
		CreatureObject(pPlayer):setScreenPlayState(16, "bestine_history_quest")
		self:giveContactQuest(pPlayer)
	elseif (screenID == "historyQuest_SpokeToContact") then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_a907268e","historyQuest_DestroyedDisk_noroom")	--Yes, the disk has been taken care of.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_a907268e","historyQuest_DestroyedDisk")	--Yes, the disk has been taken care of.
		end
	elseif (screenID == "historyQuest_DestroyedDisk_noroom") then
		writeData(playerID..":bestine_election:history_noroom",electionNum)
		CreatureObject(pPlayer):removeScreenPlayState(32, "bestine_history_quest")
	elseif (screenID == "historyQuest_DestroyedDisk") then
		self:giveHistoryReward(pPlayer)
	elseif (screenID == "historyQuest_SearchedCrashSite") then
	end
	return pConvScreen
end

function seanTrenwellConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if self:gaveDiskToHutt(pPlayer) then
		return convoTemplate:getScreen("disk_to_hutt")
	end

	local electionWinner = getQuestStatus("bestine_election:electionWinner")
	local phase = tonumber(getQuestStatus("bestine_election:currentPhase"))
	if (phase == 1) then
		if BestineElectionScreenPlay:noroomReturned(pPlayer,"sean") then
			return convoTemplate:getScreen("returned_noroom")
		end
		if BestineElectionScreenPlay:isOnNegativeQuest(pPlayer,"sean") then
			return convoTemplate:getScreen("nquest_return")
		end
		if BestineElectionScreenPlay:joinedCampaign(pPlayer, "victor") then
			return convoTemplate:getScreen("rival_player")
		end
		if BestineElectionScreenPlay:votedFor(pPlayer, "victor") then
			return convoTemplate:getScreen("voted_victor_this_election")
		end

		if (electionWinner == "sean") then
			if BestineElectionScreenPlay:joinedCampaign(pPlayer, "sean") then
				return convoTemplate:getScreen("ask_voted")
			else
				return convoTemplate:getScreen("sean_inOffice")
			end
		elseif (electionWinner == "victor") then
			if BestineElectionScreenPlay:joinedCampaign(pPlayer, "sean") then
				return convoTemplate:getScreen("ask_voted")
			elseif BestineElectionScreenPlay:votedFor(pPlayer, "sean") then
				return convoTemplate:getScreen("voted_sean_this_election")
			else
				return convoTemplate:getScreen("convo_start")
			end
		end
	elseif (phase == 2) then
		if (electionWinner == "victor") then
			return convoTemplate:getScreen("notInOffice_noElection")
		elseif (electionWinner == "sean") then
			return convoTemplate:getScreen("sean_inOffice")
		end
	end
	return convoTemplate:getScreen("convo_start")
end
