local ObjectManager = require("managers.object.object_manager")

rebelCoordinatorConvoHandler = conv_handler:new {}

function rebelCoordinatorConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local state = tonumber(readScreenPlayData(pPlayer, "rebel_coa2", "state"))

	if TangibleObject(pPlayer):isImperial() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif pGhost == nil or not PlayerObject(pGhost):hasBadge(EVENT_PROJECT_DEAD_EYE_1) then
		return convoTemplate:getScreen("act1_not_complete")
	elseif state == nil then
		return convoTemplate:getScreen("m1_begin")
	elseif state == 1 then
		return convoTemplate:getScreen("m1_refused")
	elseif state == 2 then
		return convoTemplate:getScreen("m1_active")
	elseif state == 3 then
		if Coa2Screenplay:hasDisk(pPlayer, "decoded") then
			return convoTemplate:getScreen("m1_finish_decoded")
		elseif Coa2Screenplay:hasDisk(pPlayer, "encoded") then
			return convoTemplate:getScreen("m1_finish_encoded")
		else
			return convoTemplate:getScreen("m1_active")
		end
	elseif state == 4 then
		if Coa2Screenplay:hasDisk(pPlayer, "decoded") then
			return convoTemplate:getScreen("m2_begin")
		else
			return convoTemplate:getScreen("m2_begin_encoded")
		end
	elseif state == 5 then
		return convoTemplate:getScreen("m2_refused")
	elseif state == 6 then
		return convoTemplate:getScreen("m2_active")
	elseif state == 7 then
		return convoTemplate:getScreen("m2_finish")
	elseif state == 8 then
		return convoTemplate:getScreen("m3_begin")
	elseif state == 9 then
		return convoTemplate:getScreen("m3_active")
	elseif state > 9 then
		return convoTemplate:getScreen("m3_finish")
	end

	return convoTemplate:getScreen("m1_begin")
end

function rebelCoordinatorConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "m1_begin_no" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", 1)
	elseif screenID == "m1_begin_yes" or screenID == "m1_refused_yes" then
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "rebel")
	elseif screenID == "m1_active_abort" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", 1)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m1_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "rebel")
	elseif screenID == "m1_finish_encoded" then
		Coa2Screenplay:finishMissionOne(pPlayer, "rebel")
	elseif screenID == "m1_finish_decoded" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", 4)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m2_begin_no" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", 5)
	elseif screenID == "m2_begin_yes" or screenID == "m2_refused_yes" then
		Coa2Screenplay:startMissionTwo(pPlayer, pNpc, "rebel")
	elseif screenID == "m2_active_abort" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", 5)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m2_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionTwo(pPlayer, pNpc, "rebel")
	elseif screenID == "m2_finish" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", 8)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m2_finish_yes" then
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "rebel")
	elseif screenID == "m3_begin_yes" then
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "rebel")
	elseif screenID == "m3_active_abort" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", 8)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m3_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "rebel")
	end

	return pConvScreen
end
