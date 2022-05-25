local ObjectManager = require("managers.object.object_manager")

rebelCoordinatorConvoHandler = conv_handler:new {}

function rebelCoordinatorConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if TangibleObject(pPlayer):isImperial() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif pGhost == nil or (not PlayerObject(pGhost):hasBadge(EVENT_PROJECT_DEAD_EYE_1) and not CriesOfAlderaan.skipToThree) then
		return convoTemplate:getScreen("generic_response")
	end

	-- Has coa3 badge already
	if (PlayerObject(pGhost):hasBadge(EVENT_COA3_REBEL)) then
		return convoTemplate:getScreen("coa3_init_complete")
	elseif (PlayerObject(pGhost):hasBadge(EVENT_COA2_REBEL) or CriesOfAlderaan.skipToThree) then
		-- Has coa2 badge, handle coa3
		if (not CriesOfAlderaan.episodeThreeEnabled) then
			return convoTemplate:getScreen("generic_response")
		end

		local state = CriesOfAlderaan:getState(pPlayer, "coa3_rebel")
		printf("state: " .. state .. "\n")

		if state == 0 then
			return convoTemplate:getScreen("coa3_init")
		elseif (state == Coa3Screenplay.PRE_INFO_OFFICER) then
			return convoTemplate:getScreen("coa3_init_go_to_info")
		elseif (state == Coa3Screenplay.PRE_RETURN) then
			return convoTemplate:getScreen("coa3_init_completed_info")
		elseif (state >= Coa3Screenplay.M1_FIND_LOOKOUT and state <= Coa3Screenplay.M2_RETURNED_UNIT and Coa3Screenplay:hasDisk(pPlayer)) then
			return convoTemplate:getScreen("coa3_init_has_disk")
		elseif (state >= Coa3Screenplay.M1_FIND_LOOKOUT and state <= Coa3Screenplay.M2_RETURNED_UNIT and not Coa3Screenplay:hasDisk(pPlayer)) then
			return convoTemplate:getScreen("coa3_init_has_lookout")
		elseif (state >= Coa3Screenplay.M3_TACTICAL_OFFICER and state <= Coa3Screenplay.M3_WAREHOUSE_DESTROYED) then
			return convoTemplate:getScreen("coa3_init_go_to_tact")
		elseif (state == Coa3Screenplay.M3_COMPLETE) then
			return convoTemplate:getScreen("coa3_init_completed_tact")
		elseif (state >= Coa3Screenplay.M4_CELEBRITY) then
			return convoTemplate:getScreen("coa3_init_go_to_princess")
		end
	else
		-- Handle coa2
		if (not CriesOfAlderaan.episodeTwoEnabled) then
			return convoTemplate:getScreen("generic_response")
		end

		local state = CriesOfAlderaan:getState(pPlayer, "rebel_coa2")

		if state == 0 then
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
	elseif screenID == "coa3_come_out_on_top" then
		CriesOfAlderaan:setState(pPlayer, "coa3_rebel", Coa3Screenplay.PRE_INFO_OFFICER)
	elseif screenID == "coa3_pose_as_them" or screenID == "coa3_uploaded_lookout_location" then
		CriesOfAlderaan:setState(pPlayer, self:getStateKey("rebel"), Coa3Screenplay.M1_FIND_LOOKOUT)
		Coa3Screenplay:startLookoutMission(pPlayer, pNpc, "rebel")
	end

	return pConvScreen
end
