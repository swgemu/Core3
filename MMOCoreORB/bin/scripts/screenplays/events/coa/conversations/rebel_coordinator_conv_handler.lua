local ObjectManager = require("managers.object.object_manager")

rebelCoordinatorConvoHandler = conv_handler:new {}

function rebelCoordinatorConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if TangibleObject(pPlayer):isImperial() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif pGhost == nil or not PlayerObject(pGhost):hasBadge(EVENT_PROJECT_DEAD_EYE_1) then
		return convoTemplate:getScreen("generic_response")
	end

	if (not PlayerObject(pGhost):hasBadge(EVENT_COA2_REBEL)) then
		-- CoA2
		local state = tonumber(readScreenPlayData(pPlayer, "rebel_coa2", "state"))
		
		if state == nil then
			return convoTemplate:getScreen("coa2_m1_begin")
		elseif state == Coa2Screenplay.M1_REFUSED then
			return convoTemplate:getScreen("coa2_m1_refused")
		elseif state == Coa2Screenplay.M1_ACTIVE then
			return convoTemplate:getScreen("coa2_m1_active")
		elseif state == Coa2Screenplay.M1_RETURN then
			if Coa2Screenplay:hasDisk(pPlayer, "decoded") then
				return convoTemplate:getScreen("coa2_m1_finish_decoded")
			elseif Coa2Screenplay:hasDisk(pPlayer, "encoded") then
				return convoTemplate:getScreen("coa2_m1_finish_encoded")
			else
				return convoTemplate:getScreen("coa2_m1_active")
			end
		elseif state == Coa2Screenplay.M1_COMPLETE then
			if Coa2Screenplay:hasDisk(pPlayer, "decoded") then
				return convoTemplate:getScreen("coa2_m2_begin")
			else
				return convoTemplate:getScreen("coa2_m2_begin_encoded")
			end
		elseif state == Coa2Screenplay.M2_REFUSED then
			return convoTemplate:getScreen("coa2_m2_refused")
		elseif state == Coa2Screenplay.M2_ACTIVE then
			return convoTemplate:getScreen("coa2_m2_active")
		elseif state == Coa2Screenplay.M2_RETURN then
			return convoTemplate:getScreen("coa2_m2_finish")
		elseif state == Coa2Screenplay.M2_COMPLETE then
			return convoTemplate:getScreen("coa2_m3_begin")
		elseif state == Coa2Screenplay.M3_4_ACTIVE then
			return convoTemplate:getScreen("coa2_m3_active")
		elseif state > Coa2Screenplay.M3_4_ACTIVE then
			return convoTemplate:getScreen("coa2_m3_finish")
		end
	end

	return convoTemplate:getScreen("generic_response")
end

function rebelCoordinatorConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "coa2_m1_begin_no" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", Coa2Screenplay.M1_REFUSED)
	elseif screenID == "coa2_m1_begin_yes" or screenID == "coa2_m1_refused_yes" then
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "rebel")
	elseif screenID == "coa2_m1_active_abort" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", Coa2Screenplay.M1_REFUSED)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "coa2_m1_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "rebel")
	elseif screenID == "coa2_m1_finish_encoded" then
		Coa2Screenplay:finishMissionOne(pPlayer, "rebel")
	elseif screenID == "coa2_m1_finish_decoded" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", Coa2Screenplay.M1_COMPLETE)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "coa2_m2_begin_no" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", Coa2Screenplay.M2_REFUSED)
	elseif screenID == "coa2_m2_begin_yes" or screenID == "coa2_m2_refused_yes" then
		Coa2Screenplay:startMissionTwo(pPlayer, pNpc, "rebel")
	elseif screenID == "coa2_m2_active_abort" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", Coa2Screenplay.M2_REFUSED)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "coa2_m2_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionTwo(pPlayer, pNpc, "rebel")
	elseif screenID == "coa2_m2_finish" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", Coa2Screenplay.M2_COMPLETE)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "coa2_m2_finish_yes" then
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "rebel")
	elseif screenID == "coa2_m3_begin_yes" then
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "rebel")
	elseif screenID == "coa2_m3_active_abort" then
		writeScreenPlayData(pPlayer, "rebel_coa2", "state", Coa2Screenplay.M2_COMPLETE)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "coa2_m3_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "rebel")
	end

	return pConvScreen
end
