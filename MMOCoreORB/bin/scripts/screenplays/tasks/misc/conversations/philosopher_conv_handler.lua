local ObjectManager = require("managers.object.object_manager")

philosopherConvoHandler = conv_handler:new {}

function philosopherConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	clonedConversation:setDialogTextStringId("@static_npc/philosopher:philosopher_" .. getRandomNumber(50))

	return pConvScreen
end

function philosopherConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption, pNpc)
	return self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
end
