local ObjectManager = require("managers.object.object_manager")

tutorialTrainingRoomOfficerConvoHandler = conv_handler:new {}

function tutorialTrainingRoomOfficerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "go_train_1" or screenID == "go_train_2") then
		CreatureObject(pNpc):doAnimation("point_right")
		writeData(SceneObject(pPlayer):getObjectID() .. ":tutorial:spokeToTrainingRoomOfficer", 1)
	end

	return pConvScreen
end
