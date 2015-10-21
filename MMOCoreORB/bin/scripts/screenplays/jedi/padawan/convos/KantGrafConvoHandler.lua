local ObjectManager = require("managers.object.object_manager")

trialsKantGrafConvoHandler = Object:new {}

function trialsKantGrafConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function trialsKantGrafConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local state = CreatureObject(pPlayer):getScreenPlayState("JediPadawanTrialArchitechScreenPlay")
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (state == 2) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("not_interested")
	end
end

function trialsKantGrafConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "intro") then
	end

	return pConversationScreen
end
