local ObjectManager = require("managers.object.object_manager")

victorVisalisConvoHandler = conv_handler:new {}

function victorVisalisConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum)

	if (curPhase == BestineElection.ELECTION_PHASE) then
		electionWinner = BestineElection:getElectionWinner(electionNum - 1)
	end

	if (curPhase == BestineElection.ELECTION_PHASE and BestineElection:hadInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_MAIN_QUEST)) then
		return convoTemplate:getScreen("init_had_no_room_to_join_campaign")
	elseif (BestineElection:getPlayerVote(pPlayer) == BestineElection.NONE and BestineElection:hasJoinedCampaign(pPlayer, BestineElection.VICTOR)) then
		return convoTemplate:getScreen("init_joined_campaign")
	elseif (BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_QUEST) == BestineElection.VICTOR_RIVAL_QUEST_ACCEPTED) then
		return convoTemplate:getScreen("init_on_rival_quest")
	elseif (BestineElection:getPlayerVote(pPlayer) == BestineElection.NONE and BestineElection:hasJoinedCampaign(pPlayer, BestineElection.SEAN)) then
		return convoTemplate:getScreen("init_joined_sean")
	elseif (electionWinner == BestineElection.VICTOR) then
		return convoTemplate:getScreen("init_victor_in_office")
	elseif (BestineElection:getPlayerVote(pPlayer) == BestineElection.SEAN) then
		return convoTemplate:getScreen("init_not_in_office_election_voted_sean")
	elseif (BestineElection:getPlayerVote(pPlayer) == BestineElection.VICTOR) then
		return convoTemplate:getScreen("init_not_in_office_election_voted_victor")
	elseif (curPhase == BestineElection.OFFICE_PHASE and electionWinner ~= BestineElection.VICTOR) then
		return convoTemplate:getScreen("init_not_in_office_no_election")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end

function victorVisalisConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local currentPhase = BestineElection:getCurrentPhase()
	local electionNum = BestineElection:getElectionNumber()

	if (screenID == "init_had_no_room_to_join_campaign") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_visalis:s_c82e9a2f", "still_no_room_to_join_campaign") -- Yes, please.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_c82e9a2f", "youll_need_evidence") -- Yes, please.
		end

		clonedConversation:addOption("@conversation/victor_visalis:s_ee26e33e", "very_well") -- No thanks!
	elseif (screenID == "youll_need_evidence") then
		BestineElection:clearInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_MAIN_QUEST)
		BestineElection:joinCampaign(pPlayer, BestineElection.VICTOR)
	elseif (screenID == "init_joined_campaign") then
		if (BestineElection:getPlayerVote(pPlayer) == BestineElection.VICTOR) then
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7", "bestine_will_be_safe") -- Yes and I voted for you.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_798f58f7", "bit_suspicious") -- Yes and I voted for you.
		end

		clonedConversation:addOption("@conversation/victor_visalis:s_700330a5", "speak_with_secretary") -- I can't find any evidence.
		clonedConversation:addOption("@conversation/victor_visalis:s_8999ec9b", "thats_a_pity") -- I decided not to vote for you.
		clonedConversation:addOption("@conversation/victor_visalis:s_dea56128", "very_well") -- I have to go.
	elseif (screenID == "init_on_rival_quest") then
		if (BestineElection:hasCandidateEvidence(pPlayer, BestineElection.VICTOR, true)) then
			clonedConversation:addOption("@conversation/victor_visalis:s_6ac98e49", "proven_your_worth") -- I have it, yes.
		end

		clonedConversation:addOption("@conversation/victor_visalis:s_da9a29e9", "stop_wasting_my_time") -- No, not yet.
	elseif (screenID == "proven_your_worth") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_visalis:s_9e0196ed", "rival_complete_inv_full") -- Yes, I am sure.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_9e0196ed", "rival_complete_join_campaign") -- Yes, I am sure.
		end

		clonedConversation:addOption("@conversation/victor_visalis:s_5c46daeb", "be_sure_to_return") -- No, I changed my mind.
	elseif (screenID == "rival_complete_join_campaign") then
		BestineElection:removeCandidateEvidence(pPlayer, BestineElection.SEAN)
		BestineElection:setQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_QUEST, BestineElection.VICTOR_RIVAL_QUEST_COMPLETED)
		BestineElection:joinCampaign(pPlayer, BestineElection.VICTOR)
	elseif (screenID == "rival_complete_inv_full") then
		BestineElection:removeCandidateEvidence(pPlayer, BestineElection.SEAN)
		BestineElection:setQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_QUEST, BestineElection.VICTOR_RIVAL_QUEST_COMPLETED)
		BestineElection:setInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_MAIN_QUEST)
	elseif (screenID == "prove_yourself") then
		BestineElection:setQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_QUEST, BestineElection.VICTOR_RIVAL_QUEST_ACCEPTED)
	elseif (screenID == "init_victor_in_office") then
		if (BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_TUSKEN_QUEST) == BestineElection.VICTOR_TUSKEN_QUEST_ACCEPTED) then
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b", "awaiting_word") -- How goes your work now that you're in office?
		elseif (BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_TUSKEN_QUEST) == BestineElection.VICTOR_TUSKEN_QUEST_COMPLETED) then
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b", "bestine_is_safer_place") -- How goes your work now that you're in office?
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b", "strike_at_heart") -- How goes your work now that you're in office?
		end

		if (BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_TUSKEN_QUEST) == BestineElection.VICTOR_TUSKEN_QUEST_ACCEPTED and BestineElection:hasItemInInventory(pPlayer, "object/tangible/loot/quest/tusken_head.iff")) then
			clonedConversation:addOption("@conversation/victor_visalis:s_6641e79e", "sand_people_will_leave") -- I have destroyed the intended target.
		end

		if (BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_TUSKEN_QUEST) == BestineElection.VICTOR_TUSKEN_QUEST_ACCEPTED) then
			clonedConversation:addOption("@conversation/victor_visalis:s_42c394e0", "sand_people_fortress") -- I'm lost. What do I need to do?
			clonedConversation:addOption("@conversation/victor_visalis:s_cbb4f307", "target_in_fortress") -- I'm still looking for our target.
			clonedConversation:addOption("@conversation/victor_visalis:s_f70821a3", "released_from_mission") -- I quit!
		end

		if (BestineElection:hasItemInInventory(pPlayer, "object/tangible/loot/quest/carved_stone.iff") or BestineElection:hasItemInInventory(pPlayer, "object/tangible/loot/quest/smooth_stone.iff")) then
			clonedConversation:addOption("@conversation/victor_visalis:s_380817dd", "never_seen_before") -- I found these weird stones.
		end

		if (currentPhase == BestineElection.ELECTION_PHASE) then
			local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

			if (electionWinner == BestineElection.VICTOR) then
				if (BestineElection:getPlayerVote(pPlayer) == BestineElection.SEAN) then
					clonedConversation:addOption("@conversation/victor_visalis:s_de1eacb3", "in_office_voted_sean_current_election") -- I hear you're up for re-election. How's the campaign going?
				elseif (BestineElection:getPlayerVote(pPlayer) == BestineElection.VICTOR) then
					clonedConversation:addOption("@conversation/victor_visalis:s_de1eacb3", "in_office_voted_current_election") -- I hear you're up for re-election. How's the campaign going?
				else
					clonedConversation:addOption("@conversation/victor_visalis:s_de1eacb3", "in_office_hasnt_voted") -- I hear you're up for re-election. How's the campaign going?
				end
			end
		else
			if (BestineElection:getPlayerVote(pPlayer, electionNum) == BestineElection.VICTOR) then
				-- OFFICE_PHASE
				if (not BestineElection:hasReceivedElectionReward(pPlayer)) then
					if (BestineElection:hasFullInventory(pPlayer)) then
						clonedConversation:addOption("@conversation/victor_visalis:s_82af0027", "main_reward_inv_full") -- Hey wait! What about my reward for voting for you?
					else
						clonedConversation:addOption("@conversation/victor_visalis:s_82af0027", "main_reward_give") -- Hey wait! What about my reward for voting for you?
					end
				else
					clonedConversation:addOption("@conversation/victor_visalis:s_82af0027", "main_reward_already_claimed") -- Hey wait! What about my reward for voting for you?
				end
			end
		end
	elseif (screenID == "time_running_out") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_visalis:s_5492e753", "need_more_room") -- I wish to join your campaign.
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_5492e753", "wise_to_agree") -- I wish to join your campaign.
		end

		clonedConversation:addOption("@conversation/victor_visalis:s_d041eb82", "more_about_museums") -- I don't want to join your campaign.
		clonedConversation:addOption("@conversation/victor_visalis:s_9201d81b", "very_well") -- I have to go. Bye!
	elseif (screenID == "wise_to_agree") then
		BestineElection:joinCampaign(pPlayer, BestineElection.VICTOR)
	elseif (screenID == "need_more_room") then
		BestineElection:setInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_MAIN_QUEST)
	elseif (screenID == "main_reward_give") then
		BestineElection:giveCampaignReward(pPlayer, BestineElection.VICTOR)
	elseif (screenID == "released_from_mission") then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			local curID = readData(SceneObject(pPlayer):getObjectID() .. ":bestineElection:tuskenWaypointID")
			PlayerObject(pGhost):removeWaypoint(curID, true)
		end

		BestineElection:setQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_TUSKEN_QUEST, BestineElection.NONE)
	elseif (screenID == "target_in_fortress" or screenID == "sand_people_fortress") then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			local curID = readData(SceneObject(pPlayer):getObjectID() .. ":bestineElection:tuskenWaypointID")
			PlayerObject(pGhost):removeWaypoint(curID, true)

			local wayID = PlayerObject(pGhost):addWaypoint("tatooine", "Fort Tusken", "", -3960, 6233, WAYPOINTBLUE, true, true, 0,0)
			writeData(SceneObject(pPlayer):getObjectID() .. ":bestineElection:tuskenWaypointID", wayID)
		end
	elseif (screenID == "sand_people_will_leave") then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pHead = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/tusken_head.iff", true)

			if (pHead ~= nil) then
				SceneObject(pHead):destroyObjectFromWorld()
				SceneObject(pHead):destroyObjectFromDatabase()
			end

			local pReward = giveItem(pInventory, "object/weapon/ranged/rifle/rifle_victor_tusken.iff", -1)
		end

		BestineElection:setQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_TUSKEN_QUEST, BestineElection.VICTOR_TUSKEN_QUEST_COMPLETED)
	elseif (screenID == "leave_with_haste") then
		BestineElection:setQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_TUSKEN_QUEST, BestineElection.VICTOR_TUSKEN_QUEST_ACCEPTED)
		dropObserver(KILLEDCREATURE, "BestineElection", "notifyKilledCreature", pPlayer)
		createObserver(KILLEDCREATURE, "BestineElection", "notifyKilledCreature", pPlayer)

		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			local wayID = PlayerObject(pGhost):addWaypoint("tatooine", "Fort Tusken", "", -3960, 6233, WAYPOINTBLUE, true, true, 0,0)
			writeData(SceneObject(pPlayer):getObjectID() .. ":bestineElection:tuskenWaypointID", wayID)
		end
	end

	return pConvScreen
end
