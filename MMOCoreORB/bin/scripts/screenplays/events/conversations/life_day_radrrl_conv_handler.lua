local ObjectManager = require("managers.object.object_manager")

lifeDayRadrrlConvoHandler = Object:new {}

function lifeDayRadrrlConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local playerID = SceneObject(pPlayer):getObjectID()
	if readScreenPlayData(pPlayer, "lifeDay", "complete") == "1" or readData(playerID .. ":lifeDayRadrrl") == 1 then
		return convoTemplate:getScreen("hello_again")
	elseif readData(playerID .. ":lifeDayState") == 2 then
		return convoTemplate:getScreen("rememberance")
	else
		return convoTemplate:getScreen("elder_first")
	end
end

function lifeDayRadrrlConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local playerID = SceneObject(conversingPlayer):getObjectID()
	if screenID == "always_remember" or screenID == "participate" then
		writeData(playerID .. ":lifeDayRadrrl", 1)
		if readData(playerID .. ":lifeDayAnarra") == 1 and readData(playerID .. ":lifeDayTebeurra") == 1 then
			writeData(playerID .. ":lifeDayState", 3)
		end
	end
	return conversationScreen
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
