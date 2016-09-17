local ObjectManager = require("managers.object.object_manager")

deathWatchLutinNightstalkerConvoHandler = {  }

function deathWatchLutinNightstalkerConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function deathWatchLutinNightstalkerConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("intro")
	end

	if (PlayerObject(pGhost):isOnLeave() or not CreatureObject(pPlayer):isRebel()) then
		return convoTemplate:getScreen("wrong_faction")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(4, "death_watch_bunker_rebel_sidequest")) then
		return convoTemplate:getScreen("quest_already_completed")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")) then
		return convoTemplate:getScreen("return_intro")
	else
		return convoTemplate:getScreen("intro")
	end

end

function deathWatchLutinNightstalkerConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	local pGhost = CreatureObject(conversingPlayer):getPlayerObject()

	if (pGhost == nil) then
		return conversationScreen
	end

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "excellent_travel_to_bunker") then
		CreatureObject(conversingPlayer):setScreenPlayState(1, "death_watch_bunker_rebel_sidequest")
	elseif (screenID == "return_intro") then
		if (CreatureObject(conversingPlayer):hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")) then
			clonedConversation:addOption("@conversation/death_watch_rebel_herald:s_9b06da0", "excellent_reward")
		end
		clonedConversation:addOption("@conversation/death_watch_rebel_herald:s_dc839e59", "please_be_quick")
		clonedConversation:addOption("@conversation/death_watch_rebel_herald:s_6f2c6f44", "more_information")
		clonedConversation:addOption("@conversation/death_watch_rebel_herald:s_f70821a3", "this_distresses_me")
	elseif (screenID == "this_distresses_me") then
		CreatureObject(conversingPlayer):removeScreenPlayState(1, "death_watch_bunker_rebel_sidequest")
		CreatureObject(conversingPlayer):removeScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
	elseif (screenID == "excellent_reward") then
		PlayerObject(pGhost):increaseFactionStanding("rebel", 30)
		CreatureObject(conversingPlayer):setScreenPlayState(4, "death_watch_bunker_rebel_sidequest")
	end

	return conversationScreen
end
