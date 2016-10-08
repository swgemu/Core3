local ObjectManager = require("managers.object.object_manager")

lifeDayTebeurraConvoHandler = conv_handler:new {}

function lifeDayTebeurraConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local playerID = SceneObject(pPlayer):getObjectID()
	if readScreenPlayData(pPlayer, readStringSharedMemory("lifeDayScreenplayName"), "complete") == "1" or readData(playerID .. ":lifeDayTebeurra") == 1 then
		return convoTemplate:getScreen("hear_again")
	elseif readData(playerID .. ":lifeDayState") == 2 then
		return convoTemplate:getScreen("life_day_began")
	else
		return convoTemplate:getScreen("elder_first")
	end
end

function lifeDayTebeurraConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local playerID = SceneObject(pPlayer):getObjectID()
	if screenID == "let_others" then
		writeData(playerID .. ":lifeDayTebeurra", 1)
		if readData(playerID .. ":lifeDayAnarra") == 1 and readData(playerID .. ":lifeDayRadrrl") == 1 then
			writeData(playerID .. ":lifeDayState", 3)
		end
	end
	return pConvScreen
end
