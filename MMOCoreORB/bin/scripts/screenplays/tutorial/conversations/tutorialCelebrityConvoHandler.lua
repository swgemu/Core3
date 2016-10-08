local ObjectManager = require("managers.object.object_manager")

tutorialCelebrityConvoHandler = conv_handler:new {}

function tutorialCelebrityConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	return convoTemplate:getScreen("intro" .. getRandomNumber(1,5))
end

function tutorialCelebrityConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption, pNpc)
	return self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
end
