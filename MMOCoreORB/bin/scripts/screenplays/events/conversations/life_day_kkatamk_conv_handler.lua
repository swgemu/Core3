local ObjectManager = require("managers.object.object_manager")

lifeDayKkatamkConvoHandler = conv_handler:new {}

function lifeDayKkatamkConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if readScreenPlayData(pPlayer, readStringSharedMemory("lifeDayScreenplayName"), "complete") == "1" then
		return convoTemplate:getScreen("return_complete")
	elseif readData(CreatureObject(pPlayer):getObjectID() .. ":lifeDayState") == 1 then
		return convoTemplate:getScreen("return_incomplete")
	elseif CreatureObject(pPlayer):getSpecies() == 4 then
		return convoTemplate:getScreen("greetings_wookiee")
	else
		return convoTemplate:getScreen("greetings")
	end
end

function lifeDayKkatamkConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "waypoint" or screenID == "waypoint_wookiee" or screenID == "new_waypoint" then
		lifeDayScreenplay:giveWaypoint(pPlayer)
	end
	return pConvScreen
end
