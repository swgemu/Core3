BiogenicRandomConvoHandler = conv_handler:new {}

function BiogenicRandomConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	clonedScreen:setDialogTextStringId("@conversation/biogenic_random:phrase_" .. getRandomNumber(0, 20))

	return pConvScreen
end
