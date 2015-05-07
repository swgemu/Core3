local ObjectManager = require("managers.object.object_manager")

tutorialNervousGuyConvoHandler = Object:new { }

function tutorialNervousGuyConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function tutorialNervousGuyConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("intro" .. getRandomNumber(1,5))
end

function tutorialNervousGuyConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end