local ObjectManager = require("managers.object.object_manager")

tutorialCommonerConvoHandler = Object:new { }

function tutorialCommonerConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function tutorialCommonerConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local commonerNum = readData(SceneObject(pNpc):getObjectID() .. ":tutorial:commonerNum")

	return convoTemplate:getScreen("initCommoner" .. commonerNum)
end

function tutorialCommonerConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end