local ObjectManager = require("managers.object.object_manager")

lifeDayAnarraConvoHandler = conv_handler:new {}

function lifeDayAnarraConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local playerID = SceneObject(pPlayer):getObjectID()
	if readScreenPlayData(pPlayer, readStringSharedMemory("lifeDayScreenplayName"), "complete") == "1" or readData(playerID .. ":lifeDayAnarra") == 1 then
		return convoTemplate:getScreen("tell_again")
	elseif readData(playerID .. ":lifeDayState") == 2 then
		return convoTemplate:getScreen("renewel")
	else
		return convoTemplate:getScreen("elder_first")
	end
end

function lifeDayAnarraConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local playerID = SceneObject(pPlayer):getObjectID()

	if screenID == "appreciate_freedom" then
		if TangibleObject(pPlayer):isImperial() == true then
			clonedConversation:addOption("@conversation/lifeday04c:s_b8b7ef2b", "work_for_empire") -- Yes. Go on.
		else
			clonedConversation:addOption("@conversation/lifeday04c:s_b8b7ef2b", "share_our_tale") -- Yes. Go on.
		end
	elseif screenID == "hope_you_will" or screenID == "thank_you" then
		writeData(playerID .. ":lifeDayAnarra", 1)
		if readData(playerID .. ":lifeDayRadrrl") == 1 and readData(playerID .. ":lifeDayTebeurra") == 1 then
			writeData(playerID .. ":lifeDayState", 3)
		end
	end
	return pConvScreen
end
