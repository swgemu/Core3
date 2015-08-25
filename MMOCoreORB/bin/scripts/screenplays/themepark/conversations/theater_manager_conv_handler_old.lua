local ObjectManager = require("managers.object.object_manager")

TheaterManagerConvoHandler = Object:new {
	themePark = nil
}
--[[
screenplays:
theater_manager: 1 - completed dance series, 2 - completed musician series
(set signifies complete) theater_manager_dance: 1 - audition, 2 - promo 1, 4 - show 1, 8 - promo 2, 16 - show 2, 32 - promo 3, 64 - show 3
(set signifies complete) theater_manager_musician: 1 - audition, 2 - promo 1, 4 - show 1, 8 - promo 2, 16 - show 2, 32 - promo 3, 64 - show 3

]]--

function TheaterManagerConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function TheaterManagerConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()
	local playerID = SceneObject(conversingPlayer):getObjectID()

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	local showRunning = readData("theater_manager:show_running")
	if (screenID == "musician_or_dancer") then
		if (CreatureObject(conversingPlayer):hasSkill("social_entertainer_music_02")) then
			if (showRunning == 1) then
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "show_running")
			else
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "audition_in_30_music")
			end
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "not_skilled_enough")
		end

		if (CreatureObject(conversingPlayer):hasSkill("social_entertainer_dance_02")) then
			if (showRunning == 1) then
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "show_running")
			else
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "audition_in_30_dance")
			end
		else
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "not_skilled_enough")
		end
		clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_414898b2", "come_back_ready")
	elseif (screenID == "audition_successful") then
		TheaterManagerScreenPlay:doPayout(conversingPlayer, 500)
		deleteData(playerID .. ":auditionSuccessful")
	elseif (screenID == "prepare_audition") then
		writeData(playerID .. ":preparingForAudition", 1)
	elseif (screenID == "audition_in_30_dance") then
		deleteData(playerID .. ":preparingForAudition")
		writeData(playerID .. ":auditionType", 1)
		TheaterManagerScreenPlay:spawnAudition(conversingPlayer)
	elseif (screenID == "audition_in_30_music") then
		deleteData(playerID .. ":preparingForAudition")
		writeData(playerID .. ":auditionType", 2)
		TheaterManagerScreenPlay:spawnAudition(conversingPlayer)
	elseif (screenID == "entertain_10_then_return") then
		TheaterManagerScreenPlay:startPromotion(conversingPlayer)
	end

	return conversationScreen
end


function TheaterManagerConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (THEATER_MANAGER_ENABLED == 0) then
		return convoTemplate:getScreen("too_busy")
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local showRunning = readData("theater_manager:show_running")
	local showPerformer = readData("theater_manager:show_performer")
	local phase = readData(playerID .. ":auditionPhase")

	local series = TheaterManagerScreenPlay:getCurrentSeries(pPlayer)
	local currentStep = TheaterManagerScreenPlay:getCurrentStep(pPlayer, series)

	if (not CreatureObject(pPlayer):hasSkill("social_entertainer_novice")) then
		return convoTemplate:getScreen("init_notentertainer")
	elseif (showRunning == 1 and showPerformer == playerID) then
		if (TheaterManagerScreenPlay:getCurrentStep(pPlayer, "dance") == 1 or TheaterManagerScreenPlay:getCurrentStep(pPlayer, "music") == 1) then
			return convoTemplate:getScreen("audition_in_30")
		elseif (TheaterManagerScreenPlay:getCurrentStep(pPlayer, "dance") == 3 or TheaterManagerScreenPlay:getCurrentStep(pPlayer, "music") == 3) then
			return convoTemplate:getScreen("show_in_two_mins")
		elseif (TheaterManagerScreenPlay:getCurrentStep(pPlayer, "dance") == 5 or TheaterManagerScreenPlay:getCurrentStep(pPlayer, "music") == 5) then
			return convoTemplate:getScreen("show_in_two_and_half_mins")
		elseif (TheaterManagerScreenPlay:getCurrentStep(pPlayer, "dance") == 7 or TheaterManagerScreenPlay:getCurrentStep(pPlayer, "music") == 7) then
			return convoTemplate:getScreen("show_in_three_mins")
		end
	elseif (readData(playerID .. ":auditionSuccessful") == 1) then
		return convoTemplate:getScreen("audition_successful")
	elseif (readData(playerID .. ":preparingForAudition") == 1) then
		deleteData(playerID .. ":preparingForAudition")
		return convoTemplate:getScreen("here_for_audition")
	elseif (TheaterManagerScreenPlay:getCurrentStep(pPlayer, "dance") == 8 and TheaterManagerScreenPlay:getCurrentStep(pPlayer, "music") == 8) then
		return convoTemplate:getScreen("done_both_performances")
	end

	if (currentStep == 2 or currentStep == 4 or currentStep == 6) then
		if (TheaterManagerScreenPlay:hasPromotedEnough(pPlayer) == true) then
			TheaterManagerScreenPlay:completePromotionPhase(pPlayer)
			if (currentStep == 2) then
				return convoTemplate:getScreen("completed_first_promotion")
			end
		elseif(TheaterManagerScreenPlay:getCurrentPromotions(pPlayer) ~= nil) then
			if (currentStep == 2) then
				return convoTemplate:getScreen("finish_first_promotion")
			end
		else
			if (currentStep == 2) then
				return convoTemplate:getScreen("first_promotion_init")
			end
		end
	end

	if (series == "none") then
		return convoTemplate:getScreen("init_entertainer")
	end

	return convoTemplate:getScreen("too_busy") -- Temporary until future phases are added
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