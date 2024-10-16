local SpaceHelpers = require("utils.space_helpers")

imperialBrokerConvoHandler = conv_handler:new {}

function imperialBrokerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	return convoTemplate:getScreen("nothing_i_can")
end

function imperialBrokerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local stringFile = "@conversation/imperial_broker"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	return pConvScreen
end

