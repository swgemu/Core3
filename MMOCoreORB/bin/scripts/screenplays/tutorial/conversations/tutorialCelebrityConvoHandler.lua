local ObjectManager = require("managers.object.object_manager")

tutorialCelebrityConvoHandler = Object:new { }

function tutorialCelebrityConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function tutorialCelebrityConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("intro" .. getRandomNumber(1,5))
end

function tutorialCelebrityConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end