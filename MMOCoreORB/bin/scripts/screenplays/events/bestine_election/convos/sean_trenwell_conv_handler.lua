local ObjectManager = require("managers.object.object_manager")

seanTrenwellConvoHandler = conv_handler:new {}

function seanTrenwellConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum)

	if (curPhase == BestineElection.ELECTION_PHASE) then
		electionWinner = BestineElection:getElectionWinner(electionNum - 1)
	end

	if (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_GAVE_TO_HUTT) then
		return convoTemplate:getScreen("init_gave_intel_to_hutt")
	elseif (curPhase == BestineElection.ELECTION_PHASE and BestineElection:hadInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_MAIN_QUEST)) then
		return convoTemplate:getScreen("init_had_full_inventory")
	elseif (BestineElection:getPlayerVote(pPlayer) == BestineElection.NONE and BestineElection:hasJoinedCampaign(pPlayer, BestineElection.SEAN)) then
		return convoTemplate:getScreen("init_joined_campaign")
	elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_QUEST) == BestineElection.SEAN_RIVAL_QUEST_ACCEPTED) then
		return convoTemplate:getScreen("init_on_dirt_quest")
	elseif (BestineElection:getPlayerVote(pPlayer) == BestineElection.NONE and BestineElection:hasJoinedCampaign(pPlayer, BestineElection.VICTOR)) then
		return convoTemplate:getScreen("init_joined_victor")
	elseif (electionWinner == BestineElection.SEAN) then
		return convoTemplate:getScreen("init_sean_in_office")
	elseif (BestineElection:getPlayerVote(pPlayer) == BestineElection.SEAN) then
		return convoTemplate:getScreen("init_voted_for_sean")
	elseif (BestineElection:getPlayerVote(pPlayer) == BestineElection.VICTOR) then
		return convoTemplate:getScreen("init_voted_for_victor")
	elseif (curPhase == BestineElection.OFFICE_PHASE and electionWinner ~= BestineElection.SEAN) then
		return convoTemplate:getScreen("init_not_in_office_no_election")
	else
		return convoTemplate:getScreen("init_not_in_office_current_election")
	end
end

function seanTrenwellConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()

	if (screenID == "init_sean_in_office") then
		if (BestineElection:hadInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST)) then
			if (BestineElection:hasFullInventory(pPlayer)) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_338ea1e3", "history_quest_inv_still_full") -- You said to return for a reward. For destroying that disk.
			else
				clonedConversation:addOption("@conversation/sean_trenwell:s_338ea1e3", "history_quest_was_full_reward") -- You said to return for a reward. For destroying that disk.
			end
		end

		if (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_DISK_DESTROYED) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_a3734170", "disk_dealt_with") -- I spoke to your contact about the disk from the crash site.
		elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_SENT_TO_CONTACT) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_49368633", "take_it_to_contact") -- What was I supposed to do with this disk from the crash site?
		elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_DISK_SCREENED and BestineElection:hasItemInInventory(pPlayer, "object/tangible/loot/quest/sean_history_disk.iff")) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_238ef4f6", "did_you_find_anything") -- I've searched the crash site.
		elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_FOUND_DISK) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_a068d8f2", "seek_historian") -- Who do I let screen anything I find at the crash site?
		elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_ACCEPTED) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_35bc21ba", "find_anything_of_value") -- What did you want me to do at the crash site?
		elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.NONE) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_6a0bba8c", "indeed_i_do") -- Do you have any special plans for while you're in office?
		end

		local currentPhase = BestineElection:getCurrentPhase()

		if (currentPhase == BestineElection.ELECTION_PHASE) then
			if (BestineElection:getPlayerVote(pPlayer) == BestineElection.SEAN) then
				clonedConversation:addOption("@conversation/sean_trenwell:s_811e4ed1", "greatly_appreciate_it") -- I voted for you in this election.
			else

				local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

				if (electionWinner == BestineElection.SEAN) then
					clonedConversation:addOption("@conversation/sean_trenwell:s_3ab76f84", "efforts_going_well") -- I hear you're up for re-election. How's the campaign going?
				end
			end
		else
			if (BestineElection:getPlayerVote(pPlayer, electionNum) == BestineElection.SEAN) then
				-- OFFICE_PHASE
				if (not BestineElection:hasReceivedElectionReward(pPlayer)) then
					if (BestineElection:hasFullInventory(pPlayer)) then
						clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120", "main_reward_inv_full") -- Now that you're in office, I've come to ask about the reward you promised.
					else
						clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120", "give_main_reward") -- Now that you're in office, I've come to ask about the reward you promised.
					end
				else
					clonedConversation:addOption("@conversation/sean_trenwell:s_7eabd120", "main_reward_already_given") -- Now that you're in office, I've come to ask about the reward you promised.
				end
			end
		end

		clonedConversation:addOption("@conversation/sean_trenwell:s_81f9db80", "taking_an_interest") -- Just thought I'd see what the local government was up to.
	elseif (screenID == "main_reward_inv_full") then
		BestineElection:setInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_MAIN_REWARD)
	elseif (screenID == "negative_tidbit") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_ef067f71", "disk_inv_full") -- Alright. I want to join your campaign.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_ef067f71", "sensible_type") -- Alright. I want to join your campaign.
		end

		clonedConversation:addOption("@conversation/sean_trenwell:s_5c46daeb", "always_use_vote") -- I've changed my mind.
		clonedConversation:addOption("@conversation/sean_trenwell:s_dea56128", "come_back_soon") -- I have to go.
	elseif (screenID == "disk_inv_full") then
		BestineElection:setInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_MAIN_QUEST)
	elseif (screenID == "sensible_type") then
		BestineElection:clearInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_MAIN_QUEST)
		BestineElection:joinCampaign(pPlayer, BestineElection.SEAN)
	elseif (screenID == "init_had_full_inventory") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_ff7aeed7", "disk_inv_full") -- Yes, that was me.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_ff7aeed7", "sensible_type") -- Yes, that was me.
		end

		clonedConversation:addOption("@conversation/sean_trenwell:s_ef067f71", "these_things_happen") -- I've thought about it and no longer want to join your campaign.
	elseif (screenID == "these_things_happen") then
		BestineElection:clearInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_MAIN_QUEST)
	elseif (screenID == "disk_dealt_with") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_a907268e", "history_quest_inv_full") -- Yes, the disk has been taken care of.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_a907268e", "history_quest_reward") -- Yes, the disk has been taken care of.
		end
	elseif (screenID == "history_quest_inv_full")	then
		BestineElection:setInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST)
	elseif (screenID == "history_quest_reward") then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pReward = giveItem(pInventory, "object/tangible/painting/bestine_history_quest_painting.iff", -1)
		end

		BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST, BestineElection.SEAN_HISTORY_QUEST_RECEIVED_REWARD)
	elseif (screenID == "init_on_dirt_quest") then
		if (BestineElection:hasCandidateEvidence(pPlayer, BestineElection.SEAN, true)) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_338ea1e3", "so_daft") -- Yes, I did. Here you are.
		end

		clonedConversation:addOption("@conversation/sean_trenwell:s_da9a29e9", "return_when_you_do") -- No, not yet.
	elseif (screenID == "so_daft") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_641d98d5", "disk_inv_full_rival") -- Yes, of course!
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_641d98d5", "sensible_type_rival") -- Yes, of course!
		end

		clonedConversation:addOption("@conversation/sean_trenwell:s_fe8dd35a", "error_of_ways") -- No, I changed my mind.
	elseif (screenID == "sensible_type_rival") then
		BestineElection:removeCandidateEvidence(pPlayer, BestineElection.VICTOR)
		BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_QUEST, BestineElection.SEAN_RIVAL_QUEST_COMPLETED)
		BestineElection:joinCampaign(pPlayer, BestineElection.SEAN)
	elseif (screenID == "disk_inv_full_rival") then
		BestineElection:removeCandidateEvidence(pPlayer, BestineElection.VICTOR)
		BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_QUEST, BestineElection.SEAN_RIVAL_QUEST_COMPLETED)
		BestineElection:setInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_MAIN_QUEST)
	elseif (screenID == "punch_in_location") then
		BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST, BestineElection.SEAN_HISTORY_QUEST_ACCEPTED)

		local pGhost = CreatureObject(pPlayer):getPlayerObject()
		local playerID = SceneObject(pPlayer):getObjectID()

		if (pGhost ~= nil) then
			local curID = readData(playerID .. ":bestineElection:historyWaypointID")
			PlayerObject(pGhost):removeWaypoint(curID, true)

			local historyWaypointID = PlayerObject(pGhost):addWaypoint("tatooine", "Historical Site", "", -758, -3907, WAYPOINTBLUE, true, true, 0,0)
			writeData(playerID .. ":bestineElection:historyWaypointID", historyWaypointID)
		end
	elseif (screenID == "seek_out_contact") then
		BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST, BestineElection.SEAN_HISTORY_QUEST_SENT_TO_CONTACT)

		local pGhost = CreatureObject(pPlayer):getPlayerObject()
		local playerID = SceneObject(pPlayer):getObjectID()

		if (pGhost ~= nil) then
			local curID = readData(playerID .. ":bestineElection:contactWaypointID")
			PlayerObject(pGhost):removeWaypoint(curID, true)

			local contactWaypointID = PlayerObject(pGhost):addWaypoint("tatooine", "Sean's Contact", "", -1448, -3765, WAYPOINTBLUE, true, true, 0,0)
			writeData(playerID .. ":bestineElection:contactWaypointID", contactWaypointID)
		end
	elseif (screenID == "disappointed_but_understand") then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()
		local playerID = SceneObject(pPlayer):getObjectID()

		if (pGhost ~= nil) then
			local curID = readData(playerID .. ":bestineElection:contactWaypointID")
			PlayerObject(pGhost):removeWaypoint(curID, true)

			curID = readData(playerID .. ":bestineElection:historyWaypointID")
			PlayerObject(pGhost):removeWaypoint(curID, true)
		end

		BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST, BestineElection.NONE)
	elseif (screenID == "speak_with_secretary") then
		BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_QUEST, BestineElection.SEAN_RIVAL_QUEST_ACCEPTED)
	elseif (screenID == "init_joined_campaign") then
		if (BestineElection:getPlayerVote(pPlayer) == BestineElection.SEAN) then
			clonedConversation:addOption("@conversation/sean_trenwell:s_d1f385de", "appreciate_support") -- It went well. I voted for you.
		else
			clonedConversation:addOption("@conversation/sean_trenwell:s_d1f385de", "thanks_i_think") -- It went well. I voted for you.
		end

		clonedConversation:addOption("@conversation/sean_trenwell:s_e7ffff2", "oh_so_soon") -- I think I'm going to get going.
		clonedConversation:addOption("@conversation/sean_trenwell:s_8b63bfe1", "speak_to_secretary") -- I can't find evidence.
	elseif (screenID == "give_main_reward") then
		BestineElection:giveCampaignReward(pPlayer, BestineElection.SEAN)
	end

	return pConvScreen
end
