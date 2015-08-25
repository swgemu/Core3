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

	local pTheater = TheaterManagerScreenPlay:getTheaterBuilding(conversingPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerConvoHandler:runScreenHandlers(), unable to get theater building object.\n")
		return conversationScreen
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local showRunning = readData(theaterID .. ":theater_manager:show_running")

	if (screenID == "init_first_time" and TheaterManagerScreenPlay:getCurrentSeries(conversingPlayer) ~= 0) then
		TheaterManagerScreenPlay:setCurrentSeries(conversingPlayer, 0)
	elseif (screenID == "what_type_of_audition") then
		if (CreatureObject(conversingPlayer):hasSkill("social_entertainer_music_02")) then
			if (showRunning == 1) then
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "someone_on_stage")
			else
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "audition_starts_in_30_music")
			end
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "not_skilled_enough")
		end

		if (CreatureObject(conversingPlayer):hasSkill("social_entertainer_dance_02")) then
			if (showRunning == 1) then
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "someone_on_stage")
			else
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "audition_starts_in_30_dance")
			end
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "not_skilled_enough")
		end

		clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_414898b2", "come_back_ready")
	elseif (screenID == "init_passed_audition") then -- Passed audition
		TheaterManagerScreenPlay:doPayout(conversingPlayer, 500)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
	elseif (screenID == "make_audition_preperations") then -- Accepted audition, not started
		writeData(playerID .. ":theater_manager:acceptedAudition", 1)
	elseif (screenID == "audition_starts_in_30_music") then -- Started audition
		TheaterManagerScreenPlay:setCurrentSeries(conversingPlayer, 2)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		writeData(playerID .. ":theater_manager:acceptedAudition", 0)
		TheaterManagerScreenPlay:startAudition(conversingPlayer)
	elseif (screenID == "audition_starts_in_30_dance") then -- Started audition
		TheaterManagerScreenPlay:setCurrentSeries(conversingPlayer, 1)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		TheaterManagerScreenPlay:completeCurrentStep(conversingPlayer)
		writeData(playerID .. ":theater_manager:acceptedAudition", 0)
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

	if (TheaterManagerScreenPlay:isOnFailureTimer(pPlayer)) then
		if (currentStep == 2) then
			return convoTemplate:getScreen("init_failed_audition_timer")
		end
	elseif (readData(SceneObject(pPlayer):getObjectID() .. ":theater_manager:acceptedAudition") == 1) then -- Accepted audition, has not started yet
		return convoTemplate:getScreen("init_start_audition")
	elseif (currentStep == 0) then -- Has not started a series
		return convoTemplate:getScreen("init_first_time")
	elseif (currentStep == 3) then -- Completed audition
		return convoTemplate:getScreen("init_passed_audition")
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
