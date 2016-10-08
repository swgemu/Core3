local ObjectManager = require("managers.object.object_manager")

rebelCommanderConvoHandler = conv_handler:new {}

function rebelCommanderConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local state = tonumber(readScreenPlayData(pPlayer, "rebel_coa2", "state"))

	if TangibleObject(pPlayer):isImperial() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif state == nil or state < 9 then
		return convoTemplate:getScreen("m4_finish_incomplete")
	elseif state == 9 then
		return convoTemplate:getScreen("m4_finish")
	elseif state == 10 then
		if TangibleObject(pPlayer):isNeutral() then
			return convoTemplate:getScreen("m5_begin_undeclared")
		else
			return convoTemplate:getScreen("m5_begin")
		end
	elseif state == 11 then
		if TangibleObject(pPlayer):isNeutral() then
			return convoTemplate:getScreen("m5_begin_undeclared")
		else
			return convoTemplate:getScreen("m5_refused")
		end
	elseif state == 12 then
		return convoTemplate:getScreen("m5_active")
	elseif state > 12 then
		return convoTemplate:getScreen("m5_finish")
	end

	return convoTemplate:getScreen("m4_finish_incomplete")
end

function rebelCommanderConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "m4_finish" then
		Coa2Screenplay:finishMissionFour(pPlayer, "rebel")
	elseif screenID == "m5_begin_no" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", 11)
	elseif screenID == "m5_begin_yes" or screenID == "m5_refused_yes" then
		Coa2Screenplay:startMissionFive(pPlayer, pNpc, "rebel")
	elseif screenID == "m5_active_abort" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", 11)
		Coa2Screenplay:cleanupMission(pPlayer, "rebel")
	elseif screenID == "m5_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer, "rebel")
		Coa2Screenplay:startMissionFive(pPlayer, pNpc, "rebel")
	end

	return pConvScreen
end
