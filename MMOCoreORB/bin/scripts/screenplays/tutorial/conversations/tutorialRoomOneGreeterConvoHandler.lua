local ObjectManager = require("managers.object.object_manager")

tutorialRoomOneGreeterConvoHandler = conv_handler:new {}

function tutorialRoomOneGreeterConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	return convoTemplate:getScreen("greeter1_bark" .. getRandomNumber(1,3))
end

function tutorialRoomOneGreeterConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption, pNpc)
	return self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
end
