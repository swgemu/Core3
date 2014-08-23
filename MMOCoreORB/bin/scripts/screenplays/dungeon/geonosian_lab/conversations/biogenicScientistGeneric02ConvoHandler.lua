local ObjectManager = require("managers.object.object_manager")

BiogenicScientistGeneric02ConvoHandler = Object:new {
	}

function BiogenicScientistGeneric02ConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	return ObjectManager.withCreatureObject(pConversingPlayer, function(player)
		local screen = LuaConversationScreen(pConversationScreen)
		local screenID = screen:getScreenID()
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)

		return pConversationScreen
	end)
end

function BiogenicScientistGeneric02ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		return convoTemplate:getScreen("init_talk")
	end)
end

function BiogenicScientistGeneric02ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local player = LuaCreatureObject(pPlayer)
	local pConversationSession = player:getConversationSession()

	local pLastConversationScreen = nil

	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)

		return conversationTemplate:getScreen(optionLink)
	end

	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end