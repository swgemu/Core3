local ObjectManager = require("managers.object.object_manager")

lifeDayRadrrlConvoHandler = Object:new {}

function lifeDayRadrrlConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, ghost)
		if readScreenPlayData(pPlayer, "lifeDay", "complete") == "1" or readData(player:getObjectID() .. ":lifeDayRadrrl") == 1 then
			return convoTemplate:getScreen("hello_again")
		elseif readData(player:getObjectID() .. ":lifeDayState") == 2 then
			return convoTemplate:getScreen("rememberance")
		else
			return convoTemplate:getScreen("elder_first")
		end
	end)
end

function lifeDayRadrrlConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local screen = LuaConversationScreen(conversationScreen)
		local screenID = screen:getScreenID()
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)

		if screenID == "always_remember" or screenID == "participate" then
			writeData(player:getObjectID() .. ":lifeDayRadrrl", 1)
			if readData(player:getObjectID() .. ":lifeDayAnarra") == 1 and readData(player:getObjectID() .. ":lifeDayTebeurra") == 1 then
				writeData(player:getObjectID() .. ":lifeDayState", 3)
			end
		end
		return conversationScreen
	end)
end

function lifeDayRadrrlConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()

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
