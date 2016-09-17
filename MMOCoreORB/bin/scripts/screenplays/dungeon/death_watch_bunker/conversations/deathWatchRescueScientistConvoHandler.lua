local ObjectManager = require("managers.object.object_manager")

deathWatchRescueScientistConvoHandler = {  }

function deathWatchRescueScientistConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function deathWatchRescueScientistConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function deathWatchRescueScientistConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("thanks3")
	end

	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if (CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")) then
		return convoTemplate:getScreen("return_thanks")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")) then
		CreatureObject(pPlayer):setScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
		CreatureObject(pPlayer):sendSystemMessageWithDI("@theme_park/messages:theme_park_credits_pp", "487")
		CreatureObject(pPlayer):addCashCredits(487, true)
		return convoTemplate:getScreen("thanks1")
	elseif (PlayerObject(pGhost):isOnLeave() or not CreatureObject(pPlayer):isRebel()) then
		return convoTemplate:getScreen("thanks2")
	else
		return convoTemplate:getScreen("thanks3")
	end
end

function deathWatchRescueScientistConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end
