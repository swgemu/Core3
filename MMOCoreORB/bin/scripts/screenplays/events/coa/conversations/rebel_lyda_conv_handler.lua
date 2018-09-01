local ObjectManager = require("managers.object.object_manager")

rebelLydaConvoHandler = conv_handler:new {}

function rebelLydaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local npcID = SceneObject(pNpc):getObjectID()
	local playersNpcID = readData(SceneObject(pPlayer):getObjectID() .. ":coaTargetID")

	if playersNpcID == npcID then
		local state = tonumber(readScreenPlayData(pPlayer, "rebel_coa2", "state"))

		if state == Coa2Screenplay.M2_RETURN then
			return convoTemplate:getScreen("m2_lydasaved_done")
		else
			return convoTemplate:getScreen("m2_lydasaved")
		end
	else
		return convoTemplate:getScreen("m1_sympathizer_invalid")
	end
end

function rebelLydaConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "m2_lydasaved_done" then
		local state = tonumber(readScreenPlayData(pPlayer, "rebel_coa2", "state"))

		if state == Coa2Screenplay.M2_ACTIVE then
			Coa2Screenplay:progressMissionTwo(pPlayer, "rebel")
		end
	end

	return pConvScreen
end
