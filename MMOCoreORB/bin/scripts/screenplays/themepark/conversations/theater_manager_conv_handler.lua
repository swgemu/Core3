local ObjectManager = require("managers.object.object_manager")

TheaterManagerConvoHandler = { }

function TheaterManagerConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function TheaterManagerConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()
	local playerID = SceneObject(conversingPlayer):getObjectID()

	local currentStep = TheaterManagerScreenPlay:getCurrentStep(conversingPlayer)

	local pTheater = TheaterManagerScreenPlay:getTheaterBuilding(conversingPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerConvoHandler:runScreenHandlers(), unable to get theater building object.\n")
		return conversationScreen
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local showRunning = readData(theaterID .. ":theater_manager:show_running")

	if (screenID == "init_first_time" and TheaterManagerScreenPlay:getCurrentSeries(conversingPlayer) ~= 0) then
		-- Initial convo
		TheaterManagerScreenPlay:setCurrentSeries(conversingPlayer, 0)
	elseif (screenID == "what_type_of_audition") then
		-- Convo options for type of series
		if (CreatureObject(conversingPlayer):hasSkill("social_entertainer_music_02")) then
			if (showRunning ~= 0 and showRunning ~= nil) then
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "someone_on_stage")
			else
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "audition_starts_in_30_music")
			end
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "not_skilled_enough")
		end

		if (CreatureObject(conversingPlayer):hasSkill("social_entertainer_dance_02")) then
			if (showRunning ~= 0 and showRunning ~= nil) then
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "someone_on_stage")
			else
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "audition_starts_in_30_dance")
			end
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "not_skilled_enough")
		end

		clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_414898b2", "come_back_when_ready")
	elseif (screenID == "init_passed_audition") then
		-- Passed audition
		TheaterManagerScreenPlay:doPayout(conversingPlayer, 500)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
	elseif (screenID == "make_audition_preperations") then
		-- Accepted audition, not started
		writeData(playerID .. ":theater_manager:acceptedAudition", 1)
	elseif (screenID == "audition_starts_in_30_music") then
		-- Started audition
		TheaterManagerScreenPlay:setCurrentSeries(conversingPlayer, 2)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		writeData(playerID .. ":theater_manager:acceptedAudition", 0)
		TheaterManagerScreenPlay:startAudition(conversingPlayer)
	elseif (screenID == "audition_starts_in_30_dance") then
		-- Started audition
		TheaterManagerScreenPlay:setCurrentSeries(conversingPlayer, 1)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		writeData(playerID .. ":theater_manager:acceptedAudition", 0)
		TheaterManagerScreenPlay:startAudition(conversingPlayer)
	elseif (screenID == "go_entertain_ten") then
		-- Accepted promo one
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		TheaterManagerScreenPlay:startPromotion(conversingPlayer)
	elseif (screenID == "init_entertained_ten") then
		-- Completed promo one
		TheaterManagerScreenPlay:completePromotionPhase(conversingPlayer)
	elseif (screenID == "init_first_show" or screenID == "stomach_of_steel") then
		-- Convo for first show
		if (showRunning ~= 0 and showRunning ~= nil) then
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_1377703a", "someone_on_stage")
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_1377703a", "starts_in_two_min")
		end

		if (screenID == "init_first_show") then
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_4365b273", "stomach_of_steel")
		end

		clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_d730c5dd", "take_your_time")
	elseif (screenID == "starts_in_two_min") then
		-- Started first show
		if (currentStep ~= 7) then
			TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		end
		TheaterManagerScreenPlay:beginPerformance(conversingPlayer)
	elseif (screenID == "init_completed_first_show") then
		-- completed first show
		TheaterManagerScreenPlay:doPayout(conversingPlayer, 1000)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
	elseif (screenID == "go_entertain_twenty") then
		-- Accepted promo two
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		TheaterManagerScreenPlay:startPromotion(conversingPlayer)
	elseif (screenID == "init_entertained_twenty") then
		-- Completed promo two
		TheaterManagerScreenPlay:completePromotionPhase(conversingPlayer)
	elseif (screenID == "open_slot_coming_up") then
		-- Convo for second show
		if (showRunning ~= 0 and showRunning ~= nil) then
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_59a59142", "someone_on_stage")
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_59a59142", "starts_in_two_and_a_half")
		end

		clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_fb55e1c0", "nervous_come_back")
	elseif (screenID == "starts_in_two_and_a_half") then
		-- Started second show
		if (currentStep ~= 12) then
			TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		end
		TheaterManagerScreenPlay:beginPerformance(conversingPlayer)
	elseif (screenID == "init_completed_second_show") then
		-- completed second show
		TheaterManagerScreenPlay:doPayout(conversingPlayer, 1500)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
	elseif (screenID == "go_entertain_thirty") then
		-- Accepted promo three
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		TheaterManagerScreenPlay:startPromotion(conversingPlayer)
	elseif (screenID == "init_entertained_thirty") then
		-- Completed promo three
		TheaterManagerScreenPlay:completePromotionPhase(conversingPlayer)
	elseif (screenID == "set_up_if_ready") then
		-- Convo for third show
		if (showRunning ~= 0 and showRunning ~= nil) then
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_dd4bb16d", "someone_on_stage")
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_dd4bb16d", "starts_in_three")
		end

		clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_d730c5dd", "take_your_time")
	elseif (screenID == "starts_in_three") then
		-- Started third show
		if (currentStep ~= 17) then
			TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		end
		TheaterManagerScreenPlay:beginPerformance(conversingPlayer)
	elseif (screenID == "init_completed_third_show") then
		-- completed third show
		TheaterManagerScreenPlay:doPayout(conversingPlayer, 2000)
		TheaterManagerScreenPlay:teachSkills(conversingPlayer)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		TheaterManagerScreenPlay:completeCurrentSeries(conversingPlayer)
	elseif (screenID == "init_completed_one") then
		-- Convo for initial convo after completing one series
		if (TheaterManagerScreenPlay:isSeriesComplete(conversingPlayer, 1)) then
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_dda95847", "full_on_dance")
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_dda95847", "full_on_music")
		end
		clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_c5a66e82", "come_see_me")
	elseif (screenID == "prep_second_audition_dance") then
		writeData(playerID .. ":theater_manager:acceptedSecondAudition", 1)
		TheaterManagerScreenPlay:setCurrentSeries(conversingPlayer, 1)
	elseif (screenID == "prep_second_audition_music") then
		writeData(playerID .. ":theater_manager:acceptedSecondAudition", 1)
		TheaterManagerScreenPlay:setCurrentSeries(conversingPlayer, 2)
	elseif (screenID == "second_audition_starts_in_30") then
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		writeData(playerID .. ":theater_manager:acceptedSecondAudition", 0)
		TheaterManagerScreenPlay:startAudition(conversingPlayer)
	end

	return conversationScreen
end


function TheaterManagerConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local pTheater = TheaterManagerScreenPlay:getTheaterBuilding(pPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerConvoHandler:getInitialScreen(), unable to get theater building object.\n")
		return convoTemplate:getScreen("init_event_in_progress")
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	local showRunning = readData(theaterID .. ":theater_manager:show_running")

	if (TheaterManagerScreenPlay.enabled == 0 or showRunning == 1) then
		return convoTemplate:getScreen("init_event_in_progress")
	elseif (not CreatureObject(pPlayer):hasSkill("social_entertainer_novice")) then
		return convoTemplate:getScreen("init_not_entertainer")
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local currentStep = TheaterManagerScreenPlay:getCurrentStep(pPlayer)

	if (readData(playerID .. ":theater_manager:acceptedAudition") == 1) then
		-- Accepted audition, has not started yet
		return convoTemplate:getScreen("init_start_audition")
	elseif (readData(playerID .. ":theater_manager:acceptedSecondAudition") == 1) then
		-- Accepted audition, has not started yet
		return convoTemplate:getScreen("init_start_second_audition")
	elseif (currentStep == 0) then
		-- Has not started a series
		if (not TheaterManagerScreenPlay:isSeriesComplete(pPlayer, 1) and not TheaterManagerScreenPlay:isSeriesComplete(pPlayer, 2)) then
			return convoTemplate:getScreen("init_first_time")
		elseif (TheaterManagerScreenPlay:isSeriesComplete(pPlayer, 1) and not TheaterManagerScreenPlay:isSeriesComplete(pPlayer, 2)) or
			(not TheaterManagerScreenPlay:isSeriesComplete(pPlayer, 1) and TheaterManagerScreenPlay:isSeriesComplete(pPlayer, 2)) then
			return convoTemplate:getScreen("init_completed_one")
		elseif (TheaterManagerScreenPlay:isSeriesComplete(pPlayer, 1) and TheaterManagerScreenPlay:isSeriesComplete(pPlayer, 2)) then
			return convoTemplate:getScreen("init_completed_both")
		end
	elseif (currentStep == 2) then
		if (TheaterManagerScreenPlay:isOnFailureTimer(pPlayer)) then
			return convoTemplate:getScreen("init_failed_audition_timer")
		else
			return convoTemplate:getScreen("init_start_audition")
		end
	elseif (currentStep == 3) then
		-- Completed audition
		return convoTemplate:getScreen("init_passed_audition")
	elseif (currentStep == 4) then
		-- Has not started first promo
		return convoTemplate:getScreen("init_first_advertising")
	elseif (currentStep == 5) then
		-- Started first promotion
		if (TheaterManagerScreenPlay:hasPromotedEnough(pPlayer)) then
			return convoTemplate:getScreen("init_entertained_ten")
		else
			return convoTemplate:getScreen("init_hasnt_entertained_ten")
		end
	elseif (currentStep == 6) then
		-- Completed first promotion
		return convoTemplate:getScreen("init_first_show")
	elseif (currentStep == 7) then
		-- Already started show at least once
		if (TheaterManagerScreenPlay:isOnFailureTimer(pPlayer)) then
			return convoTemplate:getScreen("init_failed_performance_timer")
		else
			return convoTemplate:getScreen("init_first_show")
		end
	elseif (currentStep == 8) then
		-- Completed first show
		return convoTemplate:getScreen("init_completed_first_show")
	elseif (currentStep == 9) then
		-- Has not started second promo
		return convoTemplate:getScreen("init_second_advertising")
	elseif (currentStep == 10) then
		-- Started second promotion
		if (TheaterManagerScreenPlay:hasPromotedEnough(pPlayer)) then
			return convoTemplate:getScreen("init_entertained_twenty")
		else
			return convoTemplate:getScreen("init_hasnt_entertained_twenty")
		end
	elseif (currentStep == 11) then
		-- Completed second promotion
		return convoTemplate:getScreen("init_second_show")
	elseif (currentStep == 12) then
		-- Already started show at least once
		if (TheaterManagerScreenPlay:isOnFailureTimer(pPlayer)) then
			return convoTemplate:getScreen("init_failed_performance_timer")
		else
			return convoTemplate:getScreen("init_second_show")
		end
	elseif (currentStep == 13) then
		-- Completed second show
		return convoTemplate:getScreen("init_completed_second_show")
	elseif (currentStep == 14) then
		-- Has not started third promo
		return convoTemplate:getScreen("init_third_advertising")
	elseif (currentStep == 15) then
		-- Started third promotion
		if (TheaterManagerScreenPlay:hasPromotedEnough(pPlayer)) then
			return convoTemplate:getScreen("init_entertained_thirty")
		else
			return convoTemplate:getScreen("init_hasnt_entertained_thirty")
		end
	elseif (currentStep == 16) then
		-- Completed third promotion
		return convoTemplate:getScreen("init_third_show")
	elseif (currentStep == 17) then
		-- Already started show at least once
		if (TheaterManagerScreenPlay:isOnFailureTimer(pPlayer)) then
			return convoTemplate:getScreen("init_failed_performance_timer")
		else
			return convoTemplate:getScreen("init_third_show")
		end
	elseif (currentStep == 18) then
		-- Completed third show
		return convoTemplate:getScreen("init_completed_third_show")
	end


	return convoTemplate:getScreen("init_event_in_progress") -- Temporary until future phases are added
end



function TheaterManagerConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
