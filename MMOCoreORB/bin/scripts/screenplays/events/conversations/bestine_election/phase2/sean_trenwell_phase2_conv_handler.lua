local ObjectManager = require("managers.object.object_manager")

seanTrenwellPhase2ConvoHandler = conv_handler:new {	}

--			ScreenPlayState(1, "bestine_history_quest") hasHistoryQuest
--			ScreenPlayState(2, "bestine_history_quest") talked to historian and can search
--			ScreenPlayState(4, "bestine_history_quest") found something
--			ScreenPlayState(8, "bestine_history_quest") let historian screen the find
--			ScreenPlayState(16, "bestine_history_quest") spoke to sean and received contact quest
--			ScreenPlayState(32, "bestine_history_quest") spoke to contact & destroyed the disk

function seanTrenwellPhase2ConvoHandler:gaveDiskToHutt(pPlayer)
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



function seanTrenwellPhase2ConvoHandler:canDoHistoryQuest(pPlayer)
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

function seanTrenwellPhase2ConvoHandler:giveHistoryQuest(pPlayer)
	if (pPlayer ~= nil) then
		local playerID = SceneObject(pPlayer):getObjectID()
		deleteScreenPlayData(pPlayer, "BestineElection", "completedHistoryQuest")
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			CreatureObject(pPlayer):setScreenPlayState(1, "bestine_history_quest")
			local historyWaypointID = PlayerObject(pPlayerObj):addWaypoint("tatooine", "Historical Site", "", -758, -3907, WAYPOINT_COLOR_BLUE, true, true, 0,0)
			writeData(playerID .. ":bestine_election:historyWaypointID", historyWaypointID)
		end
	end
end

function seanTrenwellPhase2ConvoHandler:giveContactQuest(pPlayer)
	if (pPlayer ~= nil) then
		local playerID = SceneObject(pPlayer):getObjectID()
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			local contactWaypointID = PlayerObject(pPlayerObj):addWaypoint("tatooine", "Sean's Contact", "", -1448, -3765, WAYPOINT_COLOR_BLUE, true, true, 0,0)
			writeData(playerID.. ":bestine_election:contactWaypointID", contactWaypointID)
		end
	end
end


function seanTrenwellPhase2ConvoHandler:removeHistoryQuest(pPlayer)
	if (pPlayer ~= nil) then
		local playerID = SceneObject(pPlayer):getObjectID()
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			local wayID = readData(playerID .. ":bestine_election:historyWaypointID")
			PlayerObject(pPlayerObj):removeWaypoint(wayID, true)
			deleteData(playerID .. ":bestine_election:historyWaypointID")
			CreatureObject(pPlayer):removeScreenPlayState(1, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(2, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(4, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(8, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(16, "bestine_history_quest")
			CreatureObject(pPlayer):removeScreenPlayState(32, "bestine_history_quest")
		end
	end
end

function seanTrenwellPhase2ConvoHandler:checkRewardGiven(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum =  BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "receivedSeanReward"))
		if (playerCampaign ~= nil) then
			if (playerCampaign == electionNum) then
				return true
			end
		end
	end
	return false
end

function seanTrenwellPhase2ConvoHandler:giveVoteReward(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			createLoot(pInventory, "bestine_election_sean_trenwell_rewards", 0, true)
		end
		writeScreenPlayData(pPlayer, "BestineElection", "receivedSeanReward", electionNum)
	end
end

function seanTrenwellPhase2ConvoHandler:giveHistoryReward(pPlayer)
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


function seanTrenwellPhase2ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()

	local clonedConversation = LuaConversationScreen(pConvScreen)

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()

	local electionWinner = getQuestStatus("bestine_election:electionWinner")

	if (screenID == "sean_inOffice") then
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

		if BestineElectionScreenPlay:votingrewardCheck(pPlayer,"sean") then
			if self:checkRewardGiven(pPlayer) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_alreadyReceivedReward") --Now that you're in office, I've come to ask about the reward you promised.
			elseif BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward_noroom") --Now that you're in office, I've come to ask about the reward you promised.
			else
				clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120","inOffice_giveReward") --Now that you're in office, I've come to ask about the reward you promised.
			end
		end
		clonedConversation:addOption("@conversation/sean_trenwell:s_81f9db80","inOffice_HowsWork")--Just thought I'd see what the local government was up to.
	elseif (screenID == "inOffice_giveReward") then
		self:giveVoteReward(pPlayer)
	elseif (screenID == "inOffice_accept_HQuest") then
		self:giveHistoryQuest(pPlayer)
	elseif (screenID == "historyQuest_CrashSite") then
	elseif (screenID == "historyQuest_CrashSite_quit") then
		self:removeHistoryQuest(pPlayer)
	elseif (screenID == "historyQuest_SeansContact") then
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

function seanTrenwellPhase2ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if self:gaveDiskToHutt(pPlayer) then
		return convoTemplate:getScreen("disk_to_hutt")
	end

	local electionWinner = getQuestStatus("bestine_election:electionWinner")
	if (electionWinner == "sean") then
		return convoTemplate:getScreen("sean_inOffice")
	else
		return convoTemplate:getScreen("notInOffice_noElection")
	end
end
