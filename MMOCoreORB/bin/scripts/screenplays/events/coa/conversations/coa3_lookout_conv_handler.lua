local ObjectManager = require("managers.object.object_manager")

coa3LookoutConvoHandler = conv_handler:new {}

function coa3LookoutConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil or PlayerObject(pGhost):getFactionStanding("jabba") < 0) then
		return convoTemplate:getScreen("init_no_mission")
	end

	local faction = Coa3Screenplay:getFactionString(pPlayer)
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)
	local playerID = SceneObject(pPlayer):getObjectID()

	local tracker = readData(playerID .. ":CoA3:lookoutTracker:")
	local convoFlow = readData(playerID .. ":CoA3:lookoutConvoFlow:")

	if (state == Coa3Screenplay.M1_FIND_LOOKOUT) then
		writeData(playerID .. ":CoA3:lookoutTracker:", 1)

		return convoTemplate:getScreen("init_first_round")
	elseif (tracker == 2) then
		return convoTemplate:getScreen("init_second_round")
	elseif (tracker == 3) then
		return convoTemplate:getScreen("init_third_round")
	elseif ((convoFlow >= 2 and tracker == 4) or state == 5) then
		CriesOfAlderaan:setState(pPlayer, "coa3_" .. faction, Coa3Screenplay.M1_TRIAL_COMPLETED)
		deleteData(playerID .. ":CoA3:lookoutConvoFlow:")
		deleteData(playerID .. ":CoA3:lookoutTracker:")

		return convoTemplate:getScreen("init_passed_trial")
	elseif (convoFlow < 2 and tracker == 4) then
		deleteData(playerID .. ":CoA3:lookoutConvoFlow:")
		deleteData(playerID .. ":CoA3:lookoutTracker:")

		CriesOfAlderaan:setState(pPlayer, "coa3_" .. faction, Coa3Screenplay.M1_FIND_LOOKOUT)

		return convoTemplate:getScreen("init_failed_trial")
	elseif (state == Coa3Screenplay.M1_REFUSED) then
		return convoTemplate:getScreen("init_passed_prior_refuse")
	elseif (state == Coa3Screenplay.M2_FIND_CARAVAN_LEADER) then
		return convoTemplate:getScreen("init_already_accepted")
	end

	return convoTemplate:getScreen("init_no_mission")
end

function coa3LookoutConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local faction = Coa3Screenplay:getFactionString(pPlayer)
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)
	local playerID = SceneObject(pPlayer):getObjectID()

	local tracker = readData(playerID .. ":CoA3:lookoutTracker:")
	local convoFlow = readData(playerID .. ":CoA3:lookoutConvoFlow:")

	if (state == Coa3Screenplay.M1_FIND_LOOKOUT and (screenID == "response_valerian" or screenID == "reponse_alkhara" or screenID == "response_jabba")) then
		CriesOfAlderaan:setState(pPlayer, "coa3_" .. faction, Coa3Screenplay.M1_SPOKE_TO_LOOKOUT)
		writeData(playerID .. ":CoA3:lookoutTracker:", 2)

		if (screenID == ("response_valerian") or screenID == ("response_alkhara")) then
			writeData(playerID .. ":CoA3:lookoutConvoFlow:", (convoFlow - 1))
		end
	end

	if (state == Coa3Screenplay.M1_SPOKE_TO_LOOKOUT) then
		if (tracker == 2) then
			writeData(playerID .. ":CoA3:lookoutTracker:", 3)

			if (screenID == ("who_said_anything") or screenID == ("better_not_to_ask")) then
				writeData(playerID .. ":CoA3:lookoutConvoFlow:", (convoFlow - 1))
			elseif (screenID == ("i_like_gamblin") or screenID == ("less_risky") or screenID == ("good_philosophy")) then
				writeData(playerID .. ":CoA3:lookoutConvoFlow:", (convoFlow + 1))
			end
		end

		if (tracker == 3) then
			writeData(playerID .. ":CoA3:lookoutTracker:", 4)

			if (screenID == ("response_oh") or screenID == "watch_your_step") then
				writeData(playerID .. ":CoA3:lookoutConvoFlow:", (convoFlow - 1))
			elseif (screenID == ("something_in_common")) then
				writeData(playerID .. ":CoA3:lookoutConvoFlow:", (convoFlow + 1))
			end
		end

		-- tracker == 3
		if (screenID == ("rule_changin")) then
			writeData(playerID .. ":CoA3:lookoutConvoFlow:", (convoFlow + 1))
		end

		-- Failed Trial, attack player
		if (screenID == ("gotta_kill_ya")) then
			deleteData(playerID .. ":CoA3:lookoutConvoFlow:")
			deleteData(playerID .. ":CoA3:lookoutTracker:")

			CriesOfAlderaan:setState(pPlayer, "coa3_" .. faction, Coa3Screenplay.M1_FIND_LOOKOUT)

			AiAgent(pNpc):setDefender(pPlayer)
		end
	end

	-- Mission Accept
	if (screenID == ("take_repair_kit") or screenID == ("important_shipment")) then
		CriesOfAlderaan:setState(pPlayer, "coa3_" .. faction, Coa3Screenplay.M2_FIND_CARAVAN_LEADER)

		Coa3Screenplay:giveRepairKit(pPlayer)
		Coa3Screenplay:setupCaravan(pPlayer)
	elseif (screenID == ("help_us_out") or screenID == ("cant_leave_camp")) then
		CriesOfAlderaan:setState(pPlayer, "coa3_" .. faction, Coa3Screenplay.M1_REFUSED)
	elseif (screenID == ("always_getting_lost")) then
		Coa3Screenplay:cleanUpCaravan(pPlayer)
		Coa3Screenplay:setupCaravan(pPlayer)
	end

	return pConvScreen
end