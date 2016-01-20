local ObjectManager = require("managers.object.object_manager")

tourAryonConvoHandler = Object:new {
	themePark = nil
}

function tourAryonConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function tourAryonConvoHandler:canVote(pPlayer)
	return (not BestineElectionScreenPlay:hasAlreadyVoted(pPlayer)) and (BestineElectionScreenPlay:canVoteForSean(pPlayer) or BestineElectionScreenPlay:canVoteForVictor(pPlayer))
end

function tourAryonConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (BestineElectionScreenPlay:isElectionEnabled() == false) then
		return convoTemplate:getScreen("default_condition")
	end

	local currentPhase = BestineElectionScreenPlay:getCurrentPhase()

	if (currentPhase == 1) then
		return convoTemplate:getScreen("election_started")
	elseif (currentPhase == 2) then
		return convoTemplate:getScreen("election_ended")
	end
	return convoTemplate:getScreen("default_condition")
end

function tourAryonConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local conversationTemplate = LuaConversationTemplate(ConversationTemplate)
	local screen = LuaConversationScreen(conversationScreen)
	local conversationScreen = screen:cloneScreen()
	local screenID = screen:getScreenID()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")
	local playerID = CreatureObject(conversingPlayer):getObjectID()

	if (screenID == "hello_no_election") then
	elseif (screenID == "election_started") then
		if self:canVote(conversingPlayer) then
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
		if self:canVote(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_65a4282", "ready_to_vote") --I'd like to vote, yes.			
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_fb124268", "quick_exit") --	No, I really need to go.

	elseif (screenID == "have_evidence") then
		if self:canVote(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "ready_to_vote")
		end
			clonedConversation:addOption("@conversation/tour_aryon:s_ccae64dd", "not_quite_ready") --On second thought, I think I'm not quite ready.  
	elseif (screenID == "more_information3") then
			if self:canVote(conversingPlayer) then
				clonedConversation:addOption("@conversation/tour_aryon:s_47117f94", "ready_to_vote") --Okay. I'd like to vote.
			else clonedConversation:addOption("@conversation/tour_aryon:s_eea34749", "thank_you") --Okay. thank you!
			end
				clonedConversation:addOption("@conversation/tour_aryon:s_3829680a", "quick_exit") --I'm... uh, gonna go. Bye!
	elseif (screenID == "no_evidence") then
		if self:canVote(conversingPlayer) then		
			clonedConversation:addOption("@conversation/tour_aryon:s_90ec63e0", "ready_to_vote") --Yes, I do.		
		end
		clonedConversation:addOption("@conversation/tour_aryon:s_1f2450ea", "get_to_it") --No, I need to go get it.
	elseif (screenID == "like_to_vote_more") then
			if self:canVote(conversingPlayer) then
				clonedConversation:addOption("@conversation/tour_aryon:s_47117f94", "ready_to_vote") --Okay. I'd like to vote.
			end
			clonedConversation:addOption("@conversation/tour_aryon:s_23b3506c", "get_to_it") --I need more information, please.
			clonedConversation:addOption("@conversation/tour_aryon:s_a44272b4", "what_evidence") --what evidence?
			clonedConversation:addOption("@conversation/tour_aryon:s_3829680a", "quick_exit") --I'm... uh, gonna go. Bye!
	elseif (screenID == "ready_to_vote") then
		if BestineElectionScreenPlay:canVoteForVictor(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "vote_for_victor") --I am ready to vote. (victor branch)
		elseif BestineElectionScreenPlay:canVoteForSean(conversingPlayer) then
			clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "vote_for_sean") -- I am ready to vote. (sean branch)
		else clonedConversation:addOption("@conversation/tour_aryon:s_1a74caee", "no_evidence") -- I am ready to vote. (no_evidence)
		end
			clonedConversation:addOption("@conversation/tour_aryon:s_ccae64dd", "not_quite_ready") --On second thought, I think I'm not quite ready.  
	elseif (screenID == "elect_victor") then
	elseif (screenID == "winning_candidate") then
	elseif (screenID == "election_ended") then
		local timeLeftInSecs = BestineElectionScreenPlay:getPhaseTimeLeft(conversingPlayer)
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

function tourAryonConvoHandler:handle_vote()

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
