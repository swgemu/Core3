local ObjectManager = require("managers.object.object_manager")

imperialCoordinatorConvoHandler = conv_handler:new {}

function imperialCoordinatorConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (TangibleObject(pPlayer):isRebel()) then
		return convoTemplate:getScreen("begin_wrong_faction")
	end

	-- Has coa3 badge already
	if (PlayerObject(pGhost):hasBadge(EVENT_COA3_IMPERIAL)) then
		return convoTemplate:getScreen("coa3_init_complete")

	-- CoA3 Conversations: Has CoA2 badge or skipToThree is true
	elseif (PlayerObject(pGhost):hasBadge(EVENT_COA2_IMPERIAL) or CriesOfAlderaan.skipToThree) then
		if (not CriesOfAlderaan.episodeThreeEnabled) then
			return convoTemplate:getScreen("generic_response")
		end

		local state3 = CriesOfAlderaan:getState(pPlayer, "coa3_imperial")

		if state3 == 0 then
			return convoTemplate:getScreen("coa3_init")
		elseif (state3 == Coa3Screenplay.PRE_INFO_OFFICER) then
			return convoTemplate:getScreen("coa3_init_go_to_info")
		elseif (state3 == Coa3Screenplay.PRE_RETURN) then
			return convoTemplate:getScreen("coa3_init_completed_info")
		elseif (state3 >= Coa3Screenplay.M1_FIND_LOOKOUT and state3 <= Coa3Screenplay.M2_RETURNED_UNIT and Coa3Screenplay:hasDisk(pPlayer)) then
			CriesOfAlderaan:setState(pPlayer, "coa3_imperial", Coa3Screenplay.M3_TACTICAL_OFFICER)

			return convoTemplate:getScreen("coa3_init_has_disk")
		elseif (state3 >= Coa3Screenplay.M1_FIND_LOOKOUT and state3 <= Coa3Screenplay.M2_RETURNED_UNIT and not Coa3Screenplay:hasDisk(pPlayer)) then
			return convoTemplate:getScreen("coa3_init_has_lookout")
		elseif (state3 >= Coa3Screenplay.M3_TACTICAL_OFFICER and state3 <= Coa3Screenplay.M3_WAREHOUSE_DESTROYED) then
			return convoTemplate:getScreen("coa3_init_go_to_tact")
		elseif (state3 == Coa3Screenplay.M3_COMPLETE) then
			return convoTemplate:getScreen("coa3_init_completed_tact")
		elseif (state3 >= Coa3Screenplay.M4_COMMANDER and not PlayerObject(pGhost):hasBadge(EVENT_COA3_IMPERIAL)) then
			return convoTemplate:getScreen("coa3_init_go_to_veers")
		end
	-- CoA2
	elseif (PlayerObject(pGhost):hasBadge(EVENT_PROJECT_DEAD_EYE_1) and CriesOfAlderaan.episodeTwoEnabled) then
		local state2 = CriesOfAlderaan:getState(pPlayer, "imperial_coa2")

		if (state2 == 0 or state2 == Coa2Screenplay.M1_REFUSED) then
			return convoTemplate:getScreen("coa2_m1_begin")
		elseif (state2 == Coa2Screenplay.M1_ACTIVE) then
			return convoTemplate:getScreen("coa2_m1_active")
		elseif (state2 == Coa2Screenplay.M1_RETURN or state2 == Coa2Screenplay.M1_COMPLETE or state2 == Coa2Screenplay.M2_REFUSED) then
			return convoTemplate:getScreen("coa2_m2_begin")
		elseif (state2 == Coa2Screenplay.M2_ACTIVE) then
			return convoTemplate:getScreen("coa2_m2_active")
		elseif (state2 == Coa2Screenplay.M2_RETURN) then
			if (Coa2Screenplay:hasDisk(pPlayer, "slicer")) then
				return convoTemplate:getScreen("coa2_m3_begin")
			else
				return convoTemplate:getScreen("coa2_m2_active")
			end
		elseif (state2 == Coa2Screenplay.M2_COMPLETE) then
			return convoTemplate:getScreen("coa2_m3_begin")
		elseif (state2 == Coa2Screenplay.M3_4_ACTIVE) then
			return convoTemplate:getScreen("coa2_m3_active")
		elseif (state2 > Coa2Screenplay.M3_4_ACTIVE) then
			return convoTemplate:getScreen("coa2_m3_finish")
		end
	end

	return convoTemplate:getScreen("generic_response")
end

function imperialCoordinatorConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local coa2State = tonumber(readScreenPlayData(pPlayer, "imperial_coa2", "state"))

	local faction = CreatureObject(pNpc):getFaction()
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "coa2_m1_begin_yes") then
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "imperial")
	elseif (screenID == "coa2_m1_active_abort") then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", Coa2Screenplay.M1_REFUSED)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif (screenID == "coa2_m1_active_restart") then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "imperial")
	elseif (screenID == "coa2_m2_begin" and coa2State == Coa2Screenplay.M1_RETURN) then
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
	elseif (screenID == "coa2_m3_begin" and coa2State == Coa2Screenplay.M2_RETURN) then
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


	-- CoA3
	elseif (screenID == ("coa3_get_filled_in")) then
		CriesOfAlderaan:setState(pPlayer, "coa3_imperial", Coa3Screenplay.PRE_INFO_OFFICER)
	elseif (screenID == ("coa3_pose_as_them") or screenID == ("coa3_uploaded_lookout_location")) then
		CriesOfAlderaan:setState(pPlayer, "coa3_imperial", Coa3Screenplay.M1_FIND_LOOKOUT)
		Coa3Screenplay:setupMission(pPlayer, pNpc, "imperial", Coa3Screenplay.LOOKOUT_MISSION)
	elseif (screenID == ("coa3_ran_into_trouble")) then
		Coa3Screenplay:cleanUpCaravan(pPlayer)
		Coa3Screenplay:abortMission(pPlayer, Coa3Screenplay.LOOKOUT_MISSION, 0)

		deleteData(playerID .. ":CoA3:lookoutConvoFlow:")
		deleteData(playerID .. ":CoA3:lookoutTracker:")
		CriesOfAlderaan:setState(pPlayer, "coa3_imperial", Coa3Screenplay.M1_FIND_LOOKOUT)

		Coa3Screenplay:setupMission(pPlayer, pNpc, "imperial", Coa3Screenplay.LOOKOUT_MISSION)
	elseif (screenID == ("coa3_come_back_later")) then
		Coa3Screenplay:abortMission(pPlayer, Coa3Screenplay.LOOKOUT_MISSION, 0)
	elseif (screenID == ("coa3_big_impression") or screenID == ("coa3_thought_was_correct")) then
		CriesOfAlderaan:setState(pPlayer, "coa3_imperial", Coa3Screenplay.M4_COMMANDER)

		Coa3Screenplay:setupCommanderMission(pPlayer, "imperial")
	end

	return pConvScreen
end
