local ObjectManager = require("managers.object.object_manager")

audienceMemberConvoHandler = conv_handler:new { }

function audienceMemberConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local npcID = SceneObject(pNpc):getObjectID()
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

	return pConvScreen
end

function audienceMemberConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption, pNpc)
	return self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
end
