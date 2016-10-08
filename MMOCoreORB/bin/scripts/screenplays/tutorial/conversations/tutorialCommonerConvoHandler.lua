local ObjectManager = require("managers.object.object_manager")

tutorialCommonerConvoHandler = conv_handler:new {}

function tutorialCommonerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local commonerNum = readData(SceneObject(pNpc):getObjectID() .. ":tutorial:commonerNum")

	return convoTemplate:getScreen("initCommoner" .. commonerNum)
end

function tutorialCommonerConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption, pNpc)
	return self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
end
