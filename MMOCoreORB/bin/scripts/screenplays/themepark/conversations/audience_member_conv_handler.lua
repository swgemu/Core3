local ObjectManager = require("managers.object.object_manager")

audienceMemberConvoHandler = Object:new { }

function audienceMemberConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local npcID = SceneObject(conversingNPC):getObjectID()
	local phrase = readStringData(npcID .. ":theater_manager:convoResponse")
	local phraseTO = readStringData(npcID .. ":theater_manager:convoResponseTO")

	if (phrase == "") then
		clonedConversation:setDialogTextStringId("@quest/crowd_pleaser/audience:neutral_" .. getRandomNumber(40))
	else
		clonedConversation:setDialogTextStringId("@quest/crowd_pleaser/audience:" .. phrase)
	end

	if (phraseTO ~= "") then
		clonedConversation:setDialogTextTO(tostring(phraseTO))
	end

	return conversationScreen
end

function audienceMemberConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("init")
end

function audienceMemberConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end
