local ObjectManager = require("managers.object.object_manager")

tourAryonConvoHandler = Object:new {
	themePark = nil
}

function tourAryonConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function tourAryonConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return convoTemplate:getScreen("hello_no_election")
	end
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		return convoTemplate:getScreen("election_started")
	end
	if (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return convoTemplate:getScreen("election_ended")
	end
	return convoTemplate:getScreen("hello_no_election")
end

function tourAryonConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local conversationTemplate = LuaConversationTemplate(ConversationTemplate)
	local screen = LuaConversationScreen(conversationScreen)

	local conversationScreen = screen:cloneScreen()
	local screenID = screen:getScreenID()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "election_started") then
		if BestineElectionScreenPlay:canVote(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_fad1aba","have_evidence")--I have some evidence I'd like to show you. It's for the election.
		end
		if BestineElectionScreenPlay:hasAlreadyVoted(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_ca478f48", "already_voted") --Yes, I'd like to get involved.
		else
			clonedConversation:addOption("@conversation/tour_aryon:s_ca478f48", "get_involved") --Yes, I'd like to get involved.
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_3001dad0", "thanks_for_visiting") --No, not really. Just wandering through Bestine.
	elseif (screenID == "get_involved") then
		clonedConversation:addOption("@conversation/tour_aryon:s_bb225c00", "more_information") --I need more information.
		if BestineElectionScreenPlay:canVote(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_65a4282", "ready_to_vote") --I'd like to vote, yes.
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_fb124268", "quick_exit") --	No, I really need to go.

	elseif (screenID == "have_evidence") then
		if BestineElectionScreenPlay:canVote(conversingPlayer) then
			if BestineElectionScreenPlay:canVoteForVictor(conversingPlayer) then
				clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "can_vote_for_victor")
			end
			if BestineElectionScreenPlay:canVoteForSean(conversingPlayer) then
				clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "can_vote_for_sean")
			end
		end
			clonedConversation:addOption("@conversation/tour_aryon:s_ccae64dd", "not_quite_ready") --On second thought, I think I'm not quite ready.
	elseif (screenID == "more_information3") then
			if BestineElectionScreenPlay:canVote(conversingPlayer) then
				clonedConversation:addOption("@conversation/tour_aryon:s_47117f94", "ready_to_vote") --Okay. I'd like to vote.
			else clonedConversation:addOption("@conversation/tour_aryon:s_eea34749", "thank_you") --Okay. thank you!
			end
				clonedConversation:addOption("@conversation/tour_aryon:s_3829680a", "quick_exit") --I'm... uh, gonna go. Bye!
	elseif (screenID == "no_evidence") then
		if BestineElectionScreenPlay:canVote(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_90ec63e0", "ready_to_vote") --Yes, I do.
		end
			clonedConversation:addOption("@conversation/tour_aryon:s_1f2450ea", "go_get_it") --No, I need to go get it.
	elseif (screenID == "like_to_vote_more") then
			if BestineElectionScreenPlay:canVote(conversingPlayer) then
				clonedConversation:addOption("@conversation/tour_aryon:s_47117f94", "ready_to_vote") --Okay. I'd like to vote.
			end
			clonedConversation:addOption("@conversation/tour_aryon:s_23b3506c", "go_get_it") --I need more information, please.
			clonedConversation:addOption("@conversation/tour_aryon:s_a44272b4", "what_evidence") --what evidence?
			clonedConversation:addOption("@conversation/tour_aryon:s_3829680a", "quick_exit") --I'm... uh, gonna go. Bye!
	elseif (screenID == "ready_to_vote") then
		if BestineElectionScreenPlay:canVoteForVictor(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "can_vote_for_victor") --I am ready to vote. (victor branch)
		elseif BestineElectionScreenPlay:canVoteForSean(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "can_vote_for_sean") -- I am ready to vote. (sean branch)
		else clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "no_evidence") -- I am ready to vote. (no_evidence)
		end
			clonedConversation:addOption("@conversation/tour_aryon:s_ccae64dd", "not_quite_ready") --On second thought, I think I'm not quite ready.
	elseif (screenID == "can_vote_for_victor") then
			clonedConversation:addOption("@conversation/tour_aryon:s_b51737ff", "elect_victor") --Yes, I wish to vote for him.
			clonedConversation:addOption("@conversation/tour_aryon:s_91852029", "changed_my_mind") --I've changed my mind and would like to think about this a bit more.
	elseif (screenID == "can_vote_for_sean") then
			clonedConversation:addOption("@conversation/tour_aryon:s_b51737ff", "elect_sean") --Yes, I wish to vote for him.
			clonedConversation:addOption("@conversation/tour_aryon:s_91852029", "changed_my_mind") --I've changed my mind and would like to think about this a bit more.
	elseif (screenID == "elect_victor") then
		BestineElectionScreenPlay:voteForVictor(conversingPlayer)
		BestineElectionScreenPlay:removeVictorEvidence(conversingPlayer)
	elseif (screenID == "elect_sean") then
		BestineElectionScreenPlay:voteForSean(conversingPlayer)
		BestineElectionScreenPlay:removeSeanEvidence(conversingPlayer)
	elseif (screenID == "election_ended") then
		local winner = getQuestStatus("bestine_election:electionWinner")
		if winner == "Sean" then
			clonedConversation:addOption("@conversation/tour_aryon:s_5d2e1112", "sean_won")
			elseif winner == "Victor" then
				clonedConversation:addOption("@conversation/tour_aryon:s_5d2e1112", "victor_won")
			else clonedConversation:addOption("@conversation/tour_aryon:s_5d2e1112", "not_sure_who")
		end
		local timeLeftInSecs = BestineElectionScreenPlay:getPhaseTimeLeft()
		timeLeftInSecs = 172900
		if (timeLeftInSecs <= 3600) then -- Less than an hour s_68d96c4a
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "within_the_hour") --The next election starts within the hour.
		elseif (timeLeftInSecs >=3600 and timeLeftInSecs <= 14400) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_a_few_hours") --The next election starts in just a few hours.
		elseif (timeLeftInSecs >= 14400 and timeLeftInSecs < 86400) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_less_than_a_day") --In less than a day the next election will begin.
		elseif (timeLeftInSecs >= 86400 and timeLeftInSecs < 172800) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_more_than_a_day") --The election won't begin for more than a day.
		elseif (timeLeftInSecs >= 172800 and timeLeftInSecs < 345600) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "just_a_few_days") --It's just a few days until the next election begins.
		elseif (timeLeftInSecs >= 345600 and timeLeftInSecs < 604800) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_less_than_a_week") --The next election will start in less than a week.
		elseif (timeLeftInSecs >= 604800 and timeLeftInSecs < 120960) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_more_than_a_week") --The next election won't start for well over a week.
		elseif (timeLeftInSecs >= 1209600) then
			clonedConversation:addOption("@conversation/tour_aryon:s_68d96c4a", "in_more_than_two_weeks") --It will be more than two weeks before the next election begins.
		end
	end
	return conversationScreen
end

function tourAryonConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
