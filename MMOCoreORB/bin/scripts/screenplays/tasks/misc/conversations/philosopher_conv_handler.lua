local ObjectManager = require("managers.object.object_manager")

philosopherConvoHandler = Object:new { }

function philosopherConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	clonedConversation:setDialogTextStringId("@static_npc/philosopher:philosopher_" .. getRandomNumber(50))

	return conversationScreen
end

function philosopherConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("init")
end

function philosopherConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end
