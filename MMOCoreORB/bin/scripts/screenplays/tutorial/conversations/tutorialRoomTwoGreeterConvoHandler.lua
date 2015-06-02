local ObjectManager = require("managers.object.object_manager")

tutorialRoomTwoGreeterConvoHandler = Object:new { }

function tutorialRoomTwoGreeterConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(conversingPlayer):getObjectID()

	if (screenID == "intro" and readData(playerID .. ":tutorial:hasDoneRoomTwoConvo") ~= 1) then
		CreatureObject(conversingPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_12")
		CreatureObject(conversingPlayer):playMusicMessage("sound/tut_12_conversation.snd")
		writeData(playerID .. ":tutorial:isHandlingGreeterConvo", 1)
	elseif (screenID == "all_the_same" and readData(playerID .. ":tutorial:hasDoneRoomTwoConvo") ~= 1) then
		CreatureObject(conversingPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_13")
		CreatureObject(conversingPlayer):playMusicMessage("sound/tut_13_justtype.snd")
	elseif (screenID == "in_the_drum" or screenID == "they_were_dissidents") then
		CreatureObject(conversingNPC):doAnimation("point_left")
		writeData(playerID .. ":tutorial:hasDoneRoomTwoConvo", 1)
		createEvent(1000, "TutorialScreenPlay", "handleRoomTwo", conversingPlayer)
	end

	return conversationScreen
end

function tutorialRoomTwoGreeterConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("intro")
end

function tutorialRoomTwoGreeterConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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