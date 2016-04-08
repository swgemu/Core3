local ObjectManager = require("managers.object.object_manager")

victorVisalisConvoHandler = conv_handler:new {
}

local negativeEvidence = {"object/tangible/loot/quest/sean_questn_gpapers.iff","object/tangible/loot/quest/sean_questn_tdisk.iff","object/tangible/loot/quest/sean_questn_alog.iff"}


function victorVisalisConvoHandler:hasNegativeEvidence(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return false
	end

	for i = 1, #negativeEvidence do
		local pInvItem = getContainerObjectByTemplate(pInventory, negativeEvidence[i], true)
		if pInvItem ~= nil then
			return true
		end
	end
	return false
end

function victorVisalisConvoHandler:removeEvidence(pPlayer)
	if (pPlayer == nil) then
		return
	end

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


function victorVisalisConvoHandler:inOffice_newElection(pPlayer)
	if (pPlayer == nil) then
		return false
	end
if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		if (not BestineElectionScreenPlay:votedFor(pPlayer,"Victor")) or (not BestineElectionScreenPlay:votedFor(pPlayer,"Sean")) then
			return true
		end
	

		local currentElection = BestineElectionScreenPlay:getElectionNumber()
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "VotedVictor"))
		if (playerCampaign == nil) then
			local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "VotedSean"))
		end
		return (playerCampaign ~= currentElection)
	end
	return false
end


function victorVisalisConvoHandler:votedVictorCurrentElection(pPlayer)
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then

		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "VotedVictor"))
		if (playerCampaign ~= nil) then
			if (playerCampaign == electionNum) then
			return true
			end
		end
	end
	return false;
end

function victorVisalisConvoHandler:inCampaign(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	if self:votedVictorCurrentElection(pPlayer) then
		return false
	end

	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "VictorCampaign"))
		if ( playerCampaign >= electionNum) then
			if (not BestineElectionScreenPlay:noroomReturned(pPlayer, "Victor")) then
				return true
			end
		end
	end
	return false
end

function victorVisalisConvoHandler:giveDiskandJoinCampaign(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_campaign_disk.iff", -1)
			if (pDisk == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item sean_campaign_disk.iff")
				return
			end
			if BestineElectionScreenPlay:isOnNegativeQuest(pPlayer,"Victor") then
				self:removeEvidence(pPlayer)
			end
			writeScreenPlayData(pPlayer, "BestineElection", "VictorCampaign", electionNum)
			deleteScreenPlayData(pPlayer, "BestineElection", "SeanCampaign")
			deleteScreenPlayData(pPlayer, "BestineElection", "VictorNegQuest")
			deleteScreenPlayData(pPlayer, "BestineElection", "SeanNegQuest")
			deleteScreenPlayData(pPlayer, "BestineElection", "questp_term_searched")
			deleteScreenPlayData(pPlayer, "BestineElection", "questp_desk_searched")
			CreatureObject(pPlayer):removeScreenPlayState(1, "bestine_tusken_quest")
		end
	end
end

function victorVisalisConvoHandler:giveElectionReward(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local electionNum = BestineElectionScreenPlay:getElectionNumber()

	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		electionNum = electionNum - 1
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		createLoot(pInventory, "bestine_election_victor_visalis_rewards", 0, true)
	end
	writeScreenPlayData(pPlayer, "BestineElection", "receivedVictorReward", electionNum)
	deleteScreenPlayData(pPlayer, "BestineElection", "VotedVictor")
end

function victorVisalisConvoHandler:giveTuskenReward(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		electionNum = electionNum - 1
	end
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		createLoot(pInventory, "bestine_election_tusken_quest", 0, true)
		writeScreenPlayData(pPlayer, "BestineElection", "receivedTuskenReward", electionNum)

		local waypointID = readData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:tuskenWaypointID")
		deleteData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:tuskenWaypointID")
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			PlayerObject(pPlayerObj):removeWaypoint(waypointID, true)
		end
		CreatureObject(pPlayer):removeScreenPlayState(1, "bestine_tusken_quest")
	end
end

function victorVisalisConvoHandler:receivedElectionReward(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		electionNum = electionNum - 1
	end
	local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "receivedVictorReward"))
	if (playerCampaign ~= nil) then
		return (playerCampaign == electionNum)
	end
	return false
end

function victorVisalisConvoHandler:checkForStones(pPlayer)
	if (pPlayer == nil) then
		return false
	end
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		return (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true) or getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/smooth_stone.iff", true))
	end
	return false
end

function victorVisalisConvoHandler:hasTuskenHead(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			return (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/tusken_head.iff", true)) and (CreatureObject(pPlayer):hasScreenPlayState(1, "victorTuskenQuest"))
		end
	end
	return false
end

function victorVisalisConvoHandler:checkForTuskenReward(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		electionNum = electionNum - 1
	end
	local electionPlayerRewarded = tonumber(readScreenPlayData(pPlayer, "BestineElection", "receivedTuskenReward"))
	if (electionPlayerRewarded ~= nil) then
		return (electionPlayerRewarded <= electionNum)
	end
	return false
end

function victorVisalisConvoHandler:giveTuskenQuest(pPlayer)
	if (pPlayer == nil) then
		return false
	end
	local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
	if (pPlayerObj ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local tuskenWaypointID = PlayerObject(pPlayerObj):addWaypoint("tatooine", "Fort Tusken", "", -3960, 6233, WAYPOINT_COLOR_PURPLE, true, true, 0,0)
		writeData(CreatureObject(pPlayer):getObjectID() .. ":bestine_election:tuskenWaypointID", tuskenWaypointID)
		CreatureObject(pPlayer):setScreenPlayState(1, "bestine_tusken_quest")
	end
end


function victorVisalisConvoHandler:removeTuskenQuest(pPlayer)
	if (pPlayer == nil) then
		return false
	end
	local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
	if (pPlayerObj ~= nil) then
		local wayID = readData(CreatureObject(pPlayer):getObjectID() .. ":bestine:tuskenWaypointID")
		PlayerObject(pPlayerObj):removeWaypoint(wayID, true)
		deleteData(CreatureObject(pPlayer):getObjectId() .. ":bestine_election:tuskenWaypointID")
		CreatureObject(pPlayer):removeScreenPlayState(1, "bestine_tusken_quest")
	end
end



function victorVisalisConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()

	if (screenID == "returned_noroom") then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_c82e9a2f","returned_noroom_still")--Yes, please.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_c82e9a2f","returned_maderoom") -- Yes, please.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_ee26e33e","no_thanks")--No thanks!
	elseif (screenID == "victor_inOffice") then
		if self:hasTuskenHead(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_6641e79e","destroyed_target") --I have destroyed the intended target.
		elseif CreatureObject(pPlayer):hasScreenPlayState(1, "bestine_tusken_quest") then
			clonedConversation:addOption("@conversation/victor_visalis:s_42c394e0","retell_tusken_quest") --I'm lost. What do I need to do?
			clonedConversation:addOption("@conversation/victor_visalis:s_cbb4f307","still_looking") --I'm still looking for our target.
			clonedConversation:addOption("@conversation/victor_visalis:s_f70821a3","quit_tusken_quest") --I quit!
		elseif self:checkForStones(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_380817dd","found_stones") --I found these weird stones.
		end

		if (not self:checkForTuskenReward(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b","tusken_quest_complete")
		elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "bestine_tusken_quest")) then
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b","inoffice_ontuskenquest") --How goes your work now that you're in office?
		else clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b","start_tusken_quest")
		end

		if BestineElectionScreenPlay:votedFor(pPlayer, "Victor") then
			if self:receivedElectionReward(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_82af0027","already_received_election_reward")--Hey wait! What about my reward for voting for you?
			elseif BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_82af0027","election_reward_noroom")--Hey wait! What about my reward for voting for you?
			else
				clonedConversation:addOption("@conversation/victor_visalis:s_82af0027","give_election_reward")--Hey wait! What about my reward for voting for you?
			end
		end

		if (self:inOffice_newElection(pPlayer)) then
			if self:votedVictorCurrentElection(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_de1eacb3","new_election_votedvictor") --Now that another election has begun, are you planning to get re-elected?
			elseif seanTrenwellConvoHandler:votedSeanCurrentElection(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_de1eacb3","new_election_votedsean") --Now that another election has begun, are you planning to get re-elected?
			else
				clonedConversation:addOption("@conversation/victor_visalis:s_de1eacb3","new_election_default") --Now that another election has begun, are you planning to get re-elected?
			end
		end
	elseif (screenID == "new_election_default") then
		if BestineElectionScreenPlay:votedFor(pPlayer, "Victor") then
			clonedConversation:addOption("@conversation/victor_visalis:s_435f07d4","give_election_reward")--Hey wait! What about my reward for voting for you in the last election?
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_bae6b22d","proposed_changes")--What are your proposed changes for Bestine?
		clonedConversation:addOption("@conversation/victor_visalis:s_d6a9a15d","here_to_vote")--I'm here to vote for you.
		clonedConversation:addOption("@conversation/victor_visalis:s_1a50f0d3","about_tuskens")--Tell me more about the Tuskens.
		clonedConversation:addOption("@conversation/victor_visalis:s_87b97dc","need_to_go")--I need to go. I'm sorry.
	elseif (screenID == "tusken_quest_complete") then
		if not self:checkForStones(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_30e8118","goodbye_friend")--Just checking up on things. Bye!
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_380817dd","found_stones") --I found these weird stones.
		end
	elseif screenID == "here_to_vote3" then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_5492e753","joincampaign_noroom") -- I wish to join your campaign.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_5492e753","givedisk_joincampaign") -- I wish to join your campaign.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_d041eb82","changed_mind") -- I don't want to join your campaign.
		clonedConversation:addOption("@conversation/victor_visalis:s_9201d81b","need_to_go") -- I have to go. Bye!
	elseif screenID == "destroyed_target" then
		victorVisalisConvoHandler:giveTuskenReward(pPlayer)
	end
	if screenID == "action_nquest" then
		writeScreenPlayData(pPlayer, "BestineElection", "VictorNegQuest", electionNum)
		deleteScreenPlayData(pPlayer, "BestineElection", "SeanCampaign")
		deleteScreenPlayData(pPlayer,"BestineElection", "questn_term_searched")
		deleteScreenPlayData(pPlayer,"BestineElection", "questn_desk_searched")
	elseif (screenID == "returned_noroom_still") or (screenID == "joincampaign_noroom") then
		writeData(playerID..":bestine_election:victorNoRoom")
	elseif screenID == "campaign_returned" then
		if BestineElectionScreenPlay:votedFor(pPlayer, "Victor") then
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7","checkForVote_true") -- Yes and I voted for you.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7","checkForVote_false") -- Yes and I voted for you.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_6cf7afee","need_to_go")--I should go.
		clonedConversation:addOption("@conversation/victor_visalis:s_700330a5","cant_find_evidence")--I can't find evidence.
	elseif screenID == "nquest_return" then
		if self:hasNegativeEvidence(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_6ac98e49","nquest_found") --I have it, yes.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_da9a29e9","nquest_notfound")--No, not yet.
		end
	elseif screenID == "nquest_found" then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_9e0196ed","joincampaign_noroom") --Yes, I am sure.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_9e0196ed","nquest_joincampaign") --Yes, I am sure.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_5c46daeb","nquest_changed_mind")--I've changed my mind.
	elseif (screenID == "givedisk_joincampaign") or (screenID == "nquest_joincampaign") or (screenID == "returned_maderoom")  then
		self:giveDiskandJoinCampaign(pPlayer)
	elseif (screenID == "new_election_votedvictor") then
		self:giveElectionReward(pPlayer)
	elseif (screenID == "accept_tusken_quest") or (screenID == "retell_tusken_quest") or (screenID == "still_looking") then
		self:giveTuskenQuest(pPlayer)
	elseif (screenID == "quit_tusken_quest") then
		self:removeTuskenQuest(pPlayer)
	elseif screenID == "destroyed_target" then
		self:giveTuskenReward(pPlayer)
	elseif screenID == "give_election_reward" then
		self:giveElectionReward(pPlayer)
	end
	return pConvScreen
end

function victorVisalisConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)

	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = CreatureObject(pPlayer):getObjectID()

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return convoTemplate:getScreen("noOffice_noElection")
	elseif BestineElectionScreenPlay:noroomReturned(pPlayer, "Victor") then
		return convoTemplate:getScreen("returned_noroom")
	elseif BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Victor") then
		return convoTemplate:getScreen("nquest_return")
	elseif BestineElectionScreenPlay:joinedCampaign(pPlayer, "Sean") then
		return convoTemplate:getScreen("rival_player")
	elseif getQuestStatus("bestine_election:electionWinner") == "Victor" then
		if BestineElectionScreenPlay:votedFor(pPlayer,"Sean") then
			return convoTemplate:getScreen("voted_sean_this_election")
		else
			return convoTemplate:getScreen("victor_inOffice")
		end
	elseif (getQuestStatus("bestine_election:electionWinner") == "Sean" and BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return convoTemplate:getScreen("noOffice_noElection")
	end
	return convoTemplate:getScreen("convo_start")
end
