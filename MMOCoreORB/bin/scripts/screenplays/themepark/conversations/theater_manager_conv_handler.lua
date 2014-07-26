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

	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player,playerObject)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		local showRunning = readData("theater_manager:show_running")
		if (screenID == "musician_or_dancer") then
			if (player:hasSkill("social_entertainer_music_02")) then
				if (showRunning == 1) then
					clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "show_running")
				else
					clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "audition_in_30_music")
				end
			else
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "not_skilled_enough")
			end
			if (player:hasSkill("social_entertainer_dance_02")) then
				if (showRunning == 1) then
					clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "show_running")
				else
					clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_9172f29c", "audition_in_30_dance")
				end
			else
				clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_183e8ee4", "not_skilled_enough")
			end
			clonedConversation:addOption("@conversation/quest_crowd_pleaser_manager:s_414898b2", "come_back_ready")
		elseif (screenID == "prepare_audition") then
			writeData(player:getObjectID() .. ":preparingForAudition", 1)
		elseif (screenID == "audition_in_30_dance") then
			deleteData(player:getObjectID() .. ":preparingForAudition")
			writeData(player:getObjectID() .. ":auditionType", 1)
			TheaterManagerScreenPlay:spawnAudition(conversingPlayer)
		elseif (screenID == "audition_in_30_music") then
			deleteData(player:getObjectID() .. ":preparingForAudition")
			writeData(player:getObjectID() .. ":auditionType", 2)
			TheaterManagerScreenPlay:spawnAudition(conversingPlayer)
		end
		return conversationScreen
	end)
end


function TheaterManagerConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local showRunning = readData("theater_manager:show_running")
		local phase = readData(player:getObjectID() .. ":auditionPhase")
		if (showRunning == 1 and phase ~= nil) then
			return convoTemplate:getScreen("audition_in_30")
		elseif (readData(player:getObjectID() .. ":auditionSuccessful") == 1) then
			deleteData(player:getObjectID() .. ":auditionSuccessful") -- Temporary until next phases are added to allow player to repeatedly try
			return convoTemplate:getScreen("audition_successful")
		elseif (not player:hasSkill("social_entertainer_novice")) then
			return convoTemplate:getScreen("init_notentertainer")
		elseif (player:hasScreenPlayState(1, "theater_manager") == 1 and player:hasScreenPlayState(2, "theater_manager") == 1 and player:hasScreenPlayState(4, "theater_manager") == 1) then
			--Has completed both dancer and musician performances
			return convoTemplate:getScreen("done_both_performances")
		elseif (readData(player:getObjectID() .. ":preparingForAudition") == 1 and (player:hasScreenPlayState(2, "theater_manager") ~= 1 or player:hasScreenPlayState(4, "theater_manager") ~= 1)) then
			--Has done initial talk about audition
			deleteData(player:getObjectID() .. ":preparingForAudition")
			return convoTemplate:getScreen("here_for_audition")
		else
			return convoTemplate:getScreen("init_entertainer")
		end
	end)
end

function TheaterManagerConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local pConversationSession = player:getConversationSession()
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
	end)
end