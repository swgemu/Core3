local ObjectManager = require("managers.object.object_manager")

victorVisalisConvoHandler = conv_handler:new {
	}

local negativeEvidence = {"object/tangible/loot/quest/sean_questn_gpapers.iff","object/tangible/loot/quest/sean_questn_tdisk.iff","object/tangible/loot/quest/sean_questn_alog.iff"}
local tuskenHead = "object/tangible/loot/quest/tusken_head.iff"

function victorVisalisConvoHandler:hasNegativeEvidence(pPlayer)
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

function victorVisalisConvoHandler:hasTuskenHead(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			return getContainerObjectByTemplate(pInventory, tuskenHead, true)
		end
	end
	return false
end

function victorVisalisConvoHandler:giveTuskenReward(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local ptuskenHead = getContainerObjectByTemplate(pInventory,tuskenHead, true)
			if (ptuskenHead ~= nil) then
				SceneObject(ptuskenHead):destroyObjectFromWorld()
				SceneObject(ptuskenHead):destroyObjectFromDatabase()
			end
			createLoot(pInventory, "bestine_election_tusken_quest", 0, true)
			self:removeTuskenQuest(pPlayer)

			local electionNum = BestineElectionScreenPlay:getElectionNumber()
			if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
				electionNum = electionNum - 1
			end
			CreatureObject(pPlayer):setScreenPlayState(2, "bestine_tusken_quest" .. electionNum)
		end
	end
end

function victorVisalisConvoHandler:tuskenWaypoint(pPlayer)
	if (pPlayer ~= nil) then

		local playerID = SceneObject(pPlayer):getObjectID()
		local waypointID = readData(playerID .. ":bestine_election:tuskenWaypointID")

		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			PlayerObject(pPlayerObj):removeWaypoint(waypointID, true)
			waypointID = PlayerObject(pPlayerObj):addWaypoint("tatooine", "Fort Tusken", "", -3960, 6233, WAYPOINT_COLOR_PURPLE, true, true, 0,0)
			writeData(playerID .. ":bestine_election:tuskenWaypointID", waypointID)
		end
	end
end

function victorVisalisConvoHandler:giveTuskenQuest(pPlayer)
	if (pPlayer ~= nil) then
		self:tuskenWaypoint(pPlayer)
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		CreatureObject(pPlayer):setScreenPlayState(1, "bestine_tusken_quest" .. electionNum)
	end
end

function victorVisalisConvoHandler:removeTuskenQuest(pPlayer)
	if (pPlayer ~= nil) then
		local playerID = SceneObject(pPlayer):getObjectID()
		local waypointID = readData(playerID.. ":bestine_election:tuskenWaypointID")

		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			PlayerObject(pPlayerObj):removeWaypoint(waypointID, true)
			deleteData(playerID .. ":bestine_election:tuskenWaypointID")
		end
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		CreatureObject(pPlayer):removeScreenPlayState(1, "bestine_tusken_quest" .. electionNum)
	end
end


function victorVisalisConvoHandler:giveElectionReward(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			createLoot(pInventory, "bestine_election_victor_visalis_rewards", 0, true)
		end
		writeScreenPlayData(pPlayer, "BestineElection", "receivedVictorReward", electionNum)
	end
end

function victorVisalisConvoHandler:giveDiskandJoinCampaign(pPlayer)
	if (pPlayer ~= nil) then

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_campaign_disk.iff", -1)
			if (pDisk == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item victor_campaign_disk.iff")
				return
			end
			if BestineElectionScreenPlay:isOnNegativeQuest(pPlayer,"victor") then
				for i = 1, #negativeEvidence do
					local pInvItem = getContainerObjectByTemplate(pInventory, negativeEvidence[i], true)
					if (pInvItem ~= nil) then
						SceneObject(pInvItem):destroyObjectFromWorld()
						SceneObject(pInvItem):destroyObjectFromDatabase()
					end
				end
			end
			local electionNum = BestineElectionScreenPlay:getElectionNumber()
			writeScreenPlayData(pPlayer, "BestineElection", "victorCampaign", electionNum)
			deleteScreenPlayData(pPlayer, "BestineElection", "victorNegQuest")
			deleteScreenPlayData(pPlayer, "BestineElection", "seanCampaign")
			deleteScreenPlayData(pPlayer, "BestineElection", "seanNegQuest")
			deleteScreenPlayData(pPlayer, "BestineElection", "questp_term_searched")
			deleteScreenPlayData(pPlayer, "BestineElection", "questp_desk_searched")
		end
	end
end

function victorVisalisConvoHandler:receivedElectionReward(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "receivedVictorReward"))
		if (playerCampaign ~= nil) then
			return (playerCampaign == electionNum)
		end
	end
	return false
end

function victorVisalisConvoHandler:onTuskenQuest(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		if (CreatureObject(pPlayer):hasScreenPlayState(1, "bestine_tusken_quest" .. electionNum)) then
			return true
		end
	end
	return false
end

function victorVisalisConvoHandler:completedTuskenQuest(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
			electionNum = electionNum - 1
		end
		if (CreatureObject(pPlayer):hasScreenPlayState(2, "bestine_tusken_quest" .. electionNum)) then
			return true
		end
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

function victorVisalisConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local electionWinner = getQuestStatus("bestine_election:electionWinner")
	local phase = tonumber(getQuestStatus("bestine_election:currentPhase"))

	if (screenID == "returned_noroom") then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_c82e9a2f","noroom_returned_noroom")--Yes, please.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_c82e9a2f","noroom_returned_joincampaign") -- Yes, please.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_ee26e33e","endconvo_verywell")--No thanks!
	elseif (screenID == "nquest_return") then
		if self:hasNegativeEvidence(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_6ac98e49","nquest_found") --I have it, yes.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_da9a29e9","nquest_notfound")--No, not yet.
		end
	elseif (screenID == "nquest_found") then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_9e0196ed","joincampaign_noroom") --Yes, I am sure.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_9e0196ed","nquest_joincampaign") --Yes, I am sure.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_5c46daeb","nquest_nojoin")--I've changed my mind.
	elseif (screenID == "here_to_vote3") then
		if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_5492e753","joincampaign_noroom") -- I wish to join your campaign.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_5492e753","joinCampaign_giveDisk") -- I wish to join your campaign.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_d041eb82","changed_mind") -- I don't want to join your campaign.
		clonedConversation:addOption("@conversation/victor_visalis:s_9201d81b","endconvo_verywell") -- I have to go. Bye!
	elseif (screenID == "ask_voted") then
		if BestineElectionScreenPlay:votedCurrentElection(pPlayer, "victor") then
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7","checkForVote_true") -- Yes and I voted for you.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7","checkForVote_false") -- Yes and I voted for you.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_700330a5","cant_find_evidence")--I can't find evidence.
		clonedConversation:addOption("@conversation/victor_visalis:s_8999ec9b","decided_no_vote")	--I decided not to vote for you.
		clonedConversation:addOption("@conversation/victor_visalis:s_6cf7afee","endconvo_verywell")--I have to go.
	elseif (screenID == "victor_inOffice") then
		if self:onTuskenQuest(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b","inOffice_onTuskenQuest") --How goes your work now that you're in office?
		elseif self:completedTuskenQuest(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b","tuskenquest_complete")--How goes your work now that you're in office?
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b","tuskenquest_intro")--How goes your work now that you're in office?
		end
		if self:hasTuskenHead(pPlayer) then
			if self:onTuskenQuest(pPlayer) then
				if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
					clonedConversation:addOption("@conversation/victor_visalis:s_6641e79e","election_reward_noroom") --I have destroyed the intended target.
				else
					clonedConversation:addOption("@conversation/victor_visalis:s_6641e79e","destroyed_target") --I have destroyed the intended target.
				end
			elseif self:completedTuskenQuest(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_6641e79e","tusken_reward_given") --I have destroyed the intended target.
			end
		elseif self:onTuskenQuest(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_42c394e0","retell_tusken_quest") --I'm lost. What do I need to do?
			clonedConversation:addOption("@conversation/victor_visalis:s_cbb4f307","still_looking") --I'm still looking for our target.
			clonedConversation:addOption("@conversation/victor_visalis:s_f70821a3","quit_tusken_quest") --I quit!
		end

		if self:checkForStones(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_380817dd","found_stones") --I found these weird stones.
		end

		if BestineElectionScreenPlay:votingrewardCheck(pPlayer,"victor") then
			if self:receivedElectionReward(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_82af0027","already_received_election_reward")--Hey wait! What about my reward for voting for you?
			elseif BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_82af0027","election_reward_noroom")--Hey wait! What about my reward for voting for you?
			else
				clonedConversation:addOption("@conversation/victor_visalis:s_82af0027","give_election_reward")--Hey wait! What about my reward for voting for you?
			end
		end
		if (phase == 1) then
			if BestineElectionScreenPlay:votedCurrentElection(pPlayer, "victor") then
				clonedConversation:addOption("@conversation/victor_visalis:s_de1eacb3","inOffice_votedvictor") --Now that another election has begun, are you planning to get re-elected?
			elseif BestineElectionScreenPlay:votedCurrentElection(pPlayer, "sean") then
				clonedConversation:addOption("@conversation/victor_visalis:s_de1eacb3","inOffice_votedsean") --Now that another election has begun, are you planning to get re-elected?
			else
				clonedConversation:addOption("@conversation/victor_visalis:s_de1eacb3","inOffice_newElection") --Now that another election has begun, are you planning to get re-elected?
			end
		end
	elseif (screenID == "inOffice_newElection") then
		if BestineElectionScreenPlay:votingrewardCheck(pPlayer,"victor") then
			if self:receivedElectionReward(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_435f07d4","already_received_election_reward")--Hey wait! What about my reward for voting for you in the last election?
			elseif BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_435f07d4","election_reward_noroom")--Hey wait! What about my reward for voting for you in the last election?
			else
				clonedConversation:addOption("@conversation/victor_visalis:s_435f07d4","give_election_reward")--Hey wait! What about my reward for voting for you in the last election?
			end
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_bae6b22d","proposed_changes")-- What are your proposed changes for Bestine?
		clonedConversation:addOption("@conversation/victor_visalis:s_d6a9a15d","here_to_vote") -- I'm here to vote for you.
		clonedConversation:addOption("@conversation/victor_visalis:s_1a50f0d3","about_tuskens")-- Tell me more about the Tuskens.
		clonedConversation:addOption("@conversation/victor_visalis:s_87b97dc","endconvo_verywell")-- I need to go. I'm sorry.
	elseif (screenID == "tuskenquest_complete") then
		if self:checkForStones(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_380817dd","tuskenquest_foundstones") --I found these weird stones.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_30e8118","endconvo_friendly") --Just checking up on things. Bye!
	elseif (screenID == "givedisk_joincampaign") or (screenID == "noroom_returned_joincampaign")  then
		self:giveDiskandJoinCampaign(pPlayer)
	elseif (screenID =="joincampaign_noroom") then
		writeData(CreatureObject(pPlayer):getObjectID()..":bestine_election:victor_noroom")
	elseif screenID == "action_nquest" then
		writeScreenPlayData(pPlayer, "BestineElection", "victorNegQuest", electionNum)
		deleteScreenPlayData(pPlayer, "BestineElection", "seanCampaign")
		deleteScreenPlayData(pPlayer,"BestineElection", "questn_term_searched")
		deleteScreenPlayData(pPlayer,"BestineElection", "questn_desk_searched")
	elseif (screenID == "tuskenquest_accept") then
		self:giveTuskenQuest(pPlayer)
	elseif (screenID == "retell_tusken_quest") or (screenID == "still_looking") then
		self:tuskenWaypoint(pPlayer)
	elseif (screenID == "quit_tusken_quest") then
		self:removeTuskenQuest(pPlayer)
	elseif screenID == "destroyed_target" then
		self:giveTuskenReward(pPlayer)
	elseif screenID == "give_election_reward" then
		self:giveElectionReward(pPlayer)
	end
	return pConvScreen
end

function victorVisalisConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return convoTemplate:getScreen("notInOffice_noElection")
	end

	local electionWinner = getQuestStatus("bestine_election:electionWinner")
	local phase = tonumber(getQuestStatus("bestine_election:currentPhase"))

	if (phase == 1) then
		if BestineElectionScreenPlay:noroomReturned(pPlayer, "victor") then
			return convoTemplate:getScreen("returned_noroom")
		end
		if BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "victor") then
			return convoTemplate:getScreen("nquest_return")
		end
		if BestineElectionScreenPlay:joinedCampaign(pPlayer, "sean") then
			return convoTemplate:getScreen("rival_player")
		end

		if (electionWinner == "victor") then
			if BestineElectionScreenPlay:joinedCampaign(pPlayer, "victor") then
				return convoTemplate:getScreen("ask_voted")
			else
				return convoTemplate:getScreen("victor_inOffice")
			end
		elseif (electionWinner == "sean") then
			if BestineElectionScreenPlay:joinedCampaign(pPlayer, "victor") then
				return convoTemplate:getScreen("ask_voted")
			elseif BestineElectionScreenPlay:votedCurrentElection(pPlayer, "victor") then
				return convoTemplate:getScreen("voted_victor_this_election")
			elseif BestineElectionScreenPlay:votedCurrentElection(pPlayer, "sean") then
				return convoTemplate:getScreen("voted_sean_this_election")
			end
		end
	elseif (phase == 2) then
		if (electionWinner == "sean") then
			return convoTemplate:getScreen("notInOffice_noElection")
		elseif (electionWinner == "victor") then
			return convoTemplate:getScreen("victor_inOffice")
		end
	end

	return convoTemplate:getScreen("convo_start")
end
