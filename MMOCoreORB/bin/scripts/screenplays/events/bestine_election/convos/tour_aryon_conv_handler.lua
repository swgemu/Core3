local ObjectManager = require("managers.object.object_manager")

tourAryonConvoHandler = conv_handler:new {}

function tourAryonConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()

	if (curPhase == BestineElection.ELECTION_PHASE) then
		return convoTemplate:getScreen("init_election_phase")
	else
		return convoTemplate:getScreen("init_not_election_phase")
	end
end

function tourAryonConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum)

	if (screenID == "init_not_election_phase") then
		if (electionWinner == BestineElection.SEAN) then
			clonedConversation:addOption("@conversation/tour_aryon:s_5d2e1112", "sean_won") -- Who was the winning candidate?
		elseif (electionWinner == BestineElection.VICTOR) then
			clonedConversation:addOption("@conversation/tour_aryon:s_5d2e1112", "victor_won") -- Who was the winning candidate?
		else
			clonedConversation:addOption("@conversation/tour_aryon:s_5d2e1112", "no_one_won") -- Who was the winning candidate?
		end

		local timeLeftInSecs = BestineElection:getPhaseTimeLeft()

		if (timeLeftInSecs < 3600) then
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
	elseif (screenID == "init_election_phase") then
		if (not BestineElection:hasPlayerVoted(pPlayer) and (BestineElection:canVoteForCandidate(pPlayer, BestineElection.SEAN) or BestineElection:canVoteForCandidate(pPlayer, BestineElection.VICTOR))) then
			clonedConversation:addOption("@conversation/tour_aryon:s_fad1aba", "proper_evidence") -- I have some evidence I'd like to show you. It's for the election.
		end

		if (BestineElection:hasPlayerVoted(pPlayer)) then
			clonedConversation:addOption("@conversation/tour_aryon:s_ca478f48", "get_involved_already_voted") -- Yes, I'd like to get involved.
		else
			clonedConversation:addOption("@conversation/tour_aryon:s_ca478f48", "get_involved_hasnt_voted") -- Yes, I'd like to get involved.
		end

		clonedConversation:addOption("@conversation/tour_aryon:s_3001dad0", "enjoy_your_time") -- No, not really. Just wandering through Bestine.
	elseif (screenID == "proper_evidence") then
		if not BestineElection:hasPlayerVoted(pPlayer) then
			if BestineElection:canVoteForCandidate(pPlayer, BestineElection.VICTOR) then
				clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "has_victor_evidence") -- I am ready to vote.
			elseif BestineElection:canVoteForCandidate(pPlayer, BestineElection.SEAN) then
				clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "has_sean_evidence") -- I am ready to vote.
			end
		end

		clonedConversation:addOption("@conversation/tour_aryon:s_ccae64dd", "be_sure_to_return") -- On second thought, I think I'm not quite ready.
	elseif (screenID == "get_involved_hasnt_voted") then
		if (not BestineElection:hasPlayerVoted(pPlayer) and (BestineElection:canVoteForCandidate(pPlayer, BestineElection.SEAN) or BestineElection:canVoteForCandidate(pPlayer, BestineElection.VICTOR))) then
			clonedConversation:addOption("@conversation/tour_aryon:s_65a4282", "glad_youre_taking_part") -- I'd like to vote, yes.
		end

		clonedConversation:addOption("@conversation/tour_aryon:s_fb124268", "completely_understand") -- No, I really need to go.
	elseif (screenID == "only_positive_things") then
		if (not BestineElection:hasPlayerVoted(pPlayer) and (BestineElection:canVoteForCandidate(pPlayer, BestineElection.SEAN) or BestineElection:canVoteForCandidate(pPlayer, BestineElection.VICTOR))) then
			clonedConversation:addOption("@conversation/tour_aryon:s_e547fd1e", "glad_youre_taking_part") -- Okay. I'd like to vote.
		end

		clonedConversation:addOption("@conversation/tour_aryon:s_3829680a", "completely_understand") -- I'm... uh, gonna go. Bye!
	elseif (screenID == "glad_youre_taking_part") then
		if not BestineElection:hasPlayerVoted(pPlayer) then
			if BestineElection:canVoteForCandidate(pPlayer, BestineElection.VICTOR) then
				clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "has_victor_evidence") -- I am ready to vote.
			elseif BestineElection:canVoteForCandidate(pPlayer, BestineElection.VICTOR) then
				clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "has_sean_evidence") -- I am ready to vote.
			end
		end

		clonedConversation:addOption("@conversation/tour_aryon:s_23b3506c", "two_eligible_candidates") -- I need more information, please.
		clonedConversation:addOption("@conversation/tour_aryon:s_a44272b4", "without_proper_evidence") -- What evidence?
	elseif (screenID == "without_proper_evidence") then
		if (not BestineElection:hasPlayerVoted(pPlayer) and (BestineElection:canVoteForCandidate(pPlayer, BestineElection.SEAN) or BestineElection:canVoteForCandidate(pPlayer, BestineElection.VICTOR))) then
			clonedConversation:addOption("@conversation/tour_aryon:s_90ec63e0", "are_you_ready") -- Yes, I do.
		else
			clonedConversation:addOption("@conversation/tour_aryon:s_1f2450ea", "glad_youre_taking_part") -- No, I need to go get it.
		end
	elseif (screenID == "are_you_ready") then
		if (BestineElection:canVoteForCandidate(pPlayer, BestineElection.VICTOR)) then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "has_victor_evidence") -- I am ready to vote.
		elseif (BestineElection:canVoteForCandidate(pPlayer, BestineElection.SEAN)) then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "has_sean_evidence") -- I am ready to vote.
		else
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "has_no_evidence") -- I am ready to vote.
		end
	elseif (screenID == "vote_for_sean") then
		if (BestineElection:canVoteForCandidate(pPlayer, BestineElection.SEAN) and BestineElection:removeCandidateEvidence(pPlayer, BestineElection.SEAN)) then
			BestineElection:addPlayerVote(pPlayer, BestineElection.SEAN)
		end
	elseif (screenID == "vote_for_victor") then
		if (BestineElection:canVoteForCandidate(pPlayer, BestineElection.VICTOR) and BestineElection:removeCandidateEvidence(pPlayer, BestineElection.VICTOR)) then
			BestineElection:addPlayerVote(pPlayer, BestineElection.VICTOR)
		end
	end

	return pConvScreen
end
