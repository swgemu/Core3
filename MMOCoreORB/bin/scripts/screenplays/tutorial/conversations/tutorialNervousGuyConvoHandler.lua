local ObjectManager = require("managers.object.object_manager")

tutorialNervousGuyConvoHandler = conv_handler:new {}

function tutorialNervousGuyConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	return convoTemplate:getScreen("intro" .. getRandomNumber(1,5))
end

function tutorialNervousGuyConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption, pNpc)
	return self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
end
