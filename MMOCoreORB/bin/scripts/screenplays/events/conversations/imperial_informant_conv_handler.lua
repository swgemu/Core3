local ObjectManager = require("managers.object.object_manager")

imperialInformantConvoHandler = conv_handler:new {}

function imperialInformantConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local npcID = SceneObject(pNpc):getObjectID()
	local playersNpcID = readData(SceneObject(pPlayer):getObjectID() .. ":coaTargetID")

	if npcID == playersNpcID then
		return convoTemplate:getScreen("m1_informant")
	else
		return convoTemplate:getScreen("m1_informant_invalid")
	end
end

function imperialInformantConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "m1_informant_report" then
		Coa2Screenplay:progressMissionOne(pPlayer, "imperial")
	end

	return pConvScreen
end
