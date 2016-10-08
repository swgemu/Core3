local ObjectManager = require("managers.object.object_manager")

lifeDayRadrrlConvoHandler = conv_handler:new {}

function lifeDayRadrrlConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local playerID = SceneObject(pPlayer):getObjectID()
	if readScreenPlayData(pPlayer, readStringSharedMemory("lifeDayScreenplayName"), "complete") == "1" or readData(playerID .. ":lifeDayRadrrl") == 1 then
		return convoTemplate:getScreen("hello_again")
	elseif readData(playerID .. ":lifeDayState") == 2 then
		return convoTemplate:getScreen("rememberance")
	else
		return convoTemplate:getScreen("elder_first")
	end
end

function lifeDayRadrrlConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local playerID = SceneObject(pPlayer):getObjectID()
	if screenID == "always_remember" or screenID == "participate" then
		writeData(playerID .. ":lifeDayRadrrl", 1)
		if readData(playerID .. ":lifeDayAnarra") == 1 and readData(playerID .. ":lifeDayTebeurra") == 1 then
			writeData(playerID .. ":lifeDayState", 3)
		end
	end
	return pConvScreen
end
