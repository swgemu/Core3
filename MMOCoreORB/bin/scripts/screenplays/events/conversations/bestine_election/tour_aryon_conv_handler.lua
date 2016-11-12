local ObjectManager = require("managers.object.object_manager")

tourAryonConvoHandler = conv_handler:new {
}

function tourAryonConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()

	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "election_started") then
		if (BestineElectionScreenPlay:canVote(pPlayer, "sean") or BestineElectionScreenPlay:canVote(pPlayer, "victor")) then
			clonedConversation:addOption("@conversation/tour_aryon:s_fad1aba", "have_evidence") -- I have some evidence I'd like to show you. It's for the election.
		end
		if BestineElectionScreenPlay:hasVoted(pPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_ca478f48", "already_voted") -- Yes, I'd like to get involved.
		else
			clonedConversation:addOption("@conversation/tour_aryon:s_ca478f48", "get_involved") -- Yes, I'd like to get involved.
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_3001dad0", "enjoy_your_time") -- No, not really. Just wandering through Bestine.
	elseif (screenID == "get_involved") then
		clonedConversation:addOption("@conversation/tour_aryon:s_bb225c00", "more_information") -- I need more information.
		if (BestineElectionScreenPlay:canVote(pPlayer, "sean") or BestineElectionScreenPlay:canVote(pPlayer, "victor")) then
			clonedConversation:addOption("@conversation/tour_aryon:s_65a4282", "like_to_vote") -- I'd like to vote, yes.
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_fb124268", "completely_understand") -- No, I really need to go.
	elseif (screenID == "have_evidence") then
		if BestineElectionScreenPlay:canVote(pPlayer, "victor") then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "ready_to_vote_victor") -- I am ready to vote.
		elseif BestineElectionScreenPlay:canVote(pPlayer, "sean") then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "ready_to_vote_sean") -- I am ready to vote.
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_23b3506c", "more_information_please") -- I need more information, please.
		clonedConversation:addOption("@conversation/tour_aryon:s_ccae64dd", "voting_not_ready") -- On second thought, I think I'm not quite ready.
	elseif (screenID == "more_information3") then
		if (BestineElectionScreenPlay:canVote(pPlayer, "sean") or BestineElectionScreenPlay:canVote(pPlayer, "victor")) then
			clonedConversation:addOption("@conversation/tour_aryon:s_47117f94", "have_evidence") -- Okay. I'd like to vote.
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_eea34749", "more_information_exit") -- Okay. Thank you!
		clonedConversation:addOption("@conversation/tour_aryon:s_3829680a", "completely_understand") -- I'm... uh, gonna go. Bye!
	elseif (screenID == "like_to_vote") then
		clonedConversation:addOption("@conversation/tour_aryon:s_23b3506c", "more_information_please") -- I need more information, please.
		clonedConversation:addOption("@conversation/tour_aryon:s_3001dad0", "what_evidence") -- What evidence?
		if BestineElectionScreenPlay:canVote(pPlayer, "victor") then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "ready_to_vote_victor") -- I am ready to vote.
		elseif BestineElectionScreenPlay:canVote(pPlayer, "sean") then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "ready_to_vote_sean") -- I am ready to vote.
		end
	elseif (screenID == "what_evidence") then
		if (BestineElectionScreenPlay:canVote(pPlayer, "sean") or BestineElectionScreenPlay:canVote(pPlayer, "victor")) then
			clonedConversation:addOption("@conversation/tour_aryon:s_90ec63e0", "ready_to_vote") -- Yes, I do.
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_1f2450ea", "go_get_it") -- No, I need to go get it.
	elseif (screenID == "ready_to_vote") then
		if BestineElectionScreenPlay:canVote(pPlayer, "victor") then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "ready_to_vote_victor") -- I am ready to vote.
		elseif BestineElectionScreenPlay:canVote(pPlayer, "sean") then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "ready_to_vote_sean") -- I am ready to vote.
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_ccae64dd", "voting_not_ready") -- On second thought, I think I'm not quite ready.
	elseif (screenID == "thanks_for_vote_victor") then
		BestineElectionScreenPlay:castVote(pPlayer, "victor")
	elseif (screenID == "thanks_for_vote_sean") then
		BestineElectionScreenPlay:castVote(pPlayer, "sean")
	elseif (screenID == "election_ended") then
		local winner = getQuestStatus("bestine_election:electionWinner")
		if (winner == "sean") then
			clonedConversation:addOption("@conversation/tour_aryon:s_5d2e1112", "sean_won") -- Who was the winning candidate?
		elseif (winner == "victor") then
			clonedConversation:addOption("@conversation/tour_aryon:s_5d2e1112", "victor_won") -- Who was the winning candidate?
		else
			clonedConversation:addOption("@conversation/tour_aryon:s_5d2e1112", "not_sure_who") -- Who was the winning candidate?
		end

		-- When does the next election begin?
		local timeLeftInSecs = BestineElectionScreenPlay:getPhaseTimeLeft()
		if (timeLeftInSecs < 3600) then -- Less than an hour
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "within_the_hour") -- The next election starts within the hour.
		elseif (timeLeftInSecs < 14400) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_a_few_hours") -- The next election starts in just a few hours.
		elseif (timeLeftInSecs < 86400) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_less_than_a_day") -- In less than a day the next election will begin.
		elseif (timeLeftInSecs < 172800) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_more_than_a_day") -- The election won't begin for more than a day.
		elseif (timeLeftInSecs < 345600) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "just_a_few_days") -- It's just a few days until the next election begins.
		elseif (timeLeftInSecs < 604800) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_less_than_a_week") -- The next election will start in less than a week.
		elseif (timeLeftInSecs < 1209600) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_more_than_a_week") -- The next election won't start for well over a week.
		else
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_more_than_two_weeks") -- It will be more than two weeks before the next election begins.
		end
	end

	return pConvScreen
end

function tourAryonConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return convoTemplate:getScreen("hello_no_election")
	end

	local phase = BestineElectionScreenPlay:getCurrentPhase()
	if (phase == 1) then
		return convoTemplate:getScreen("election_started")
	elseif (phase == 2) then
		return convoTemplate:getScreen("election_ended")
	end

	return convoTemplate:getScreen("hello_no_election")
end
