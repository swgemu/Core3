local ObjectManager = require("managers.object.object_manager")

imperialCoordinatorConvoHandler = conv_handler:new {}

function imperialCoordinatorConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (TangibleObject(pPlayer):isRebel()) then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif (pGhost == nil or not PlayerObject(pGhost):hasBadge(EVENT_PROJECT_DEAD_EYE_1)) then -- Act 1 not complete
		return convoTemplate:getScreen("generic_response")
	end

	if (not PlayerObject(pGhost):hasBadge(EVENT_COA2_IMPERIAL)) then
		-- CoA2
		local state = tonumber(readScreenPlayData(pPlayer, "imperial_coa2", "state"))

		if (state == nil or state == Coa2Screenplay.M1_REFUSED) then
			return convoTemplate:getScreen("coa2_m1_begin")
		elseif (state == Coa2Screenplay.M1_ACTIVE) then
			return convoTemplate:getScreen("coa2_m1_active")
		elseif (state == Coa2Screenplay.M1_RETURN or state == Coa2Screenplay.M1_COMPLETE or state == Coa2Screenplay.M2_REFUSED) then
			return convoTemplate:getScreen("coa2_m2_begin")
		elseif (state == Coa2Screenplay.M2_ACTIVE) then
			return convoTemplate:getScreen("coa2_m2_active")
		elseif (state == Coa2Screenplay.M2_RETURN) then
			if (Coa2Screenplay:hasDisk(pPlayer, "slicer")) then
				return convoTemplate:getScreen("coa2_m3_begin")
			else
				return convoTemplate:getScreen("coa2_m2_active")
			end
		elseif (state == Coa2Screenplay.M2_COMPLETE) then
			return convoTemplate:getScreen("coa2_m3_begin")
		elseif (state == Coa2Screenplay.M3_4_ACTIVE) then
			return convoTemplate:getScreen("coa2_m3_active")
		elseif (state > Coa2Screenplay.M3_4_ACTIVE) then
			return convoTemplate:getScreen("coa2_m3_finish")
		end
	else
		-- CoA3
		local state = tonumber(readScreenPlayData(pPlayer, "imperial_coa3", "state"))
	end

	return convoTemplate:getScreen("generic_response")
end

function imperialCoordinatorConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local state = tonumber(readScreenPlayData(pPlayer, "imperial_coa2", "state"))

	if (screenID == "coa2_m1_begin_yes") then
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "imperial")
	elseif (screenID == "coa2_m1_active_abort") then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", Coa2Screenplay.M1_REFUSED)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif (screenID == "coa2_m1_active_restart") then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "imperial")
	elseif (screenID == "coa2_m2_begin" and state == Coa2Screenplay.M1_RETURN) then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", Coa2Screenplay.M1_COMPLETE)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif (screenID == "coa2_m2_begin_yes") then
		Coa2Screenplay:startMissionTwo(pPlayer, pNpc, "imperial")
	elseif (screenID == "coa2_m2_active_abort") then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", Coa2Screenplay.M2_REFUSED)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif (screenID == "coa2_m2_active_restart") then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionTwo(pPlayer, pNpc, "imperial")
	elseif (screenID == "coa2_m3_begin" and state == Coa2Screenplay.M2_RETURN) then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", Coa2Screenplay.M2_COMPLETE)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif (screenID == "coa2_m3_begin_yes") then
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "imperial")
	elseif (screenID == "coa2_m3_active_abort") then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", Coa2Screenplay.M2_COMPLETE)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif (screenID == "coa2_m3_active_restart") then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "imperial")
	end

	return pConvScreen
end
