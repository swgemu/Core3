warrenWorkerConvoHandler = conv_handler:new {}

function warrenWorkerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	return convoTemplate:getScreen("init_" .. getRandomNumber(1,4))
end
