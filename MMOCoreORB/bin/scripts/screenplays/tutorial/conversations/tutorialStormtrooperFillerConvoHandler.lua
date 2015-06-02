local ObjectManager = require("managers.object.object_manager")

tutorialStormtrooperFillerConvoHandler = Object:new { }

function tutorialStormtrooperFillerConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "moveAlong") then
		CreatureObject(conversingNPC):doAnimation("wave_on_directing")
	end

	return conversationScreen
end

function tutorialStormtrooperFillerConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("moveAlong")
end

function tutorialStormtrooperFillerConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end