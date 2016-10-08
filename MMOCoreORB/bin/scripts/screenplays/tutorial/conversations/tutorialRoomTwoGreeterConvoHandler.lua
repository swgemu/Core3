local ObjectManager = require("managers.object.object_manager")

tutorialRoomTwoGreeterConvoHandler = conv_handler:new {}

function tutorialRoomTwoGreeterConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "intro" and readData(playerID .. ":tutorial:hasDoneRoomTwoConvo") ~= 1) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_12")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_12_conversation.snd")
		writeData(playerID .. ":tutorial:isHandlingGreeterConvo", 1)
	elseif (screenID == "all_the_same" and readData(playerID .. ":tutorial:hasDoneRoomTwoConvo") ~= 1) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_13")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_13_justtype.snd")
	elseif (screenID == "in_the_drum" or screenID == "they_were_dissidents") then
		CreatureObject(pNpc):doAnimation("point_left")
		writeData(playerID .. ":tutorial:hasDoneRoomTwoConvo", 1)
		createEvent(1000, "TutorialScreenPlay", "handleRoomTwo", pPlayer, "")
	end

	return pConvScreen
end
