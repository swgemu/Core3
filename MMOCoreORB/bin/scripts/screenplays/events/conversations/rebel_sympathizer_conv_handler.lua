local ObjectManager = require("managers.object.object_manager")

rebelSympathizerConvoHandler = conv_handler:new {}

function rebelSympathizerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local npcID = SceneObject(pNpc):getObjectID()
	local playersNpcID = readData(SceneObject(pPlayer):getObjectID() .. ":coaTargetID")

	if npcID == playersNpcID then
		local state = tonumber(readScreenPlayData(pPlayer, "rebel_coa2", "state"))

		if state == 3 then
			return convoTemplate:getScreen("m1_sympathizer_complete")
		else
			return convoTemplate:getScreen("m1_sympathizer_greeting")
		end
	else
		return convoTemplate:getScreen("m1_sympathizer_invalid")
	end
end

function rebelSympathizerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "m1_sympathizer_greeting" then
		Coa2Screenplay:progressMissionOne(pPlayer, "rebel")
	end

	return pConvScreen
end
