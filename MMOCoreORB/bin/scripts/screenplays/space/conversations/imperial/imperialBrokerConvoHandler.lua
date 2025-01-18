local SpaceHelpers = require("utils.space_helpers")

imperialBrokerConvoHandler = conv_handler:new {}

function imperialBrokerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerFactionStatus = CreatureObject(pPlayer):getFactionStatus()
	local playerID = CreatureObject(pPlayer):getObjectID()
	local playerGender = CreatureObject(pPlayer):getGender()

	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("no_jtl")
	end

	-- Player is a Imperial pilot and is not on leave
	if (SpaceHelpers:isImperialPilot(pPlayer) and faction == FACTIONIMPERIAL and playerFactionStatus > ONLEAVE) then
		CreatureObject(pNpc):doAnimation("salute2")

		return convoTemplate:getScreen("hello_imperial_pilot")

	-- Player is rebel
	elseif (faction == FACTIONREBEL) then
		if (readData(playerID .. ":ImperialBroker:rebel:") == 1) then
			CreatureObject(pNpc):doAnimation("wave_on_dismissing")

			return convoTemplate:getScreen("get_lost_")
		else
			return convoTemplate:getScreen("rebel_player")
		end
	-- Player is a pilot
	elseif (SpaceHelpers:isPilot(pPlayer)) then
		return convoTemplate:getScreen("no_business")

	-- Already conversed
	elseif (readData(playerID .. ":ImperialBroker:") == 1) then
		CreatureObject(pNpc):doAnimation("shrug_hands")

		-- Male
		if (playerGender == 0) then
			return convoTemplate:getScreen("something_else_male")
		-- Female
		else
			return convoTemplate:getScreen("something_else_female")
		end
	elseif (faction == FACTIONIMPERIAL and playerFactionStatus > ONLEAVE) then
		CreatureObject(pNpc):doAnimation("salute1")
		CreatureObject(pPlayer):doAnimation("salute1")

		-- Male imperial
		if (playerGender == 0) then
			return convoTemplate:getScreen("greet_male_imp")
		-- Female imperial
		else
			return convoTemplate:getScreen("greet_female_imp")
		end

	-- Neutral Female
	elseif (faction == FACTIONNEUTRAL and playerGender == 1) then
		CreatureObject(pNpc):doAnimation("point_away")

		return convoTemplate:getScreen("neutral_female")
	-- Neutral Wookiee
	elseif (CreatureObject(pPlayer):getSpecies() == SPECIES_WOOKIEE) then
		CreatureObject(pNpc):doAnimation("belly_laugh")

		return convoTemplate:getScreen("neutral_wookiee")
	end

	return convoTemplate:getScreen("greet_neutral")
end

function imperialBrokerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local stringFile = "@conversation/imperial_broker"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerFactionStatus = CreatureObject(pPlayer):getFactionStatus()
	local playerGender = CreatureObject(pPlayer):getGender()

	-- Pilot Recruiting
	if (screenID == "recruiting_male" or screenID == "recruiting_female") then
		CreatureObject(pNpc):doAnimation("nod_head_once")
	elseif (screenID == "never_mind") then
		CreatureObject(pNpc):doAnimation("salute2")
	elseif (screenID == "no_just_checking_male" or screenID == "no_just_checking_female") then
		CreatureObject(pNpc):doAnimation("salute1")
	elseif (screenID == "yes_recruiting_male") then
		CreatureObject(pNpc):doAnimation("point_to_self")
	elseif (screenID == "yes_recruiting_female") then
		CreatureObject(pNpc):doAnimation("explain")

	elseif (screenID == "greet_neutral") then
		CreatureObject(pNpc):doAnimation("shrug_hands")
	elseif (screenID == "no_never_mind") then
		CreatureObject(pNpc):doAnimation("salute2")
	elseif (screenID == "recruiting_neutral") then
		CreatureObject(pNpc):doAnimation("nod_head_once")
	elseif (screenID == "no_just_checking") then
		CreatureObject(pNpc):doAnimation("salute1")
	elseif (screenID == "yes_neutral_recruit") then
		CreatureObject(pNpc):doAnimation("explain")

	-- Black Epsilon
	elseif (screenID == "more_black_epsilon_male" or screenID == "more_black_epsilon_female") then
		CreatureObject(pNpc):doAnimation("explain")

		SpaceHelpers:addBlackEpsilonSquadWaypoint(pPlayer)
		imperialBrokerConvoHandler:setBrokerStatus(pPlayer)
	elseif (screenID == "more_black_epsilon_neutral") then
		CreatureObject(pNpc):doAnimation("wave_finger_warning")

		SpaceHelpers:addBlackEpsilonSquadWaypoint(pPlayer)
		imperialBrokerConvoHandler:setBrokerStatus(pPlayer)

	-- Storm Squadron
	elseif (screenID == "storm_squadron") then
		CreatureObject(pNpc):doAnimation("pose_proudly")

		-- Storm Squadron Male Responses
		if (playerGender == 0) then
			clonedConversation:addOption("@conversation/imperial_broker:s_70f18874", "not_interested_storm_male") -- I'm not interested in that.
			clonedConversation:addOption("@conversation/imperial_broker:s_df2917b1", "storm_more_male") -- Tell me more

		-- Storm Squadron Female Responses
		else
			clonedConversation:addOption("@conversation/imperial_broker:s_70f18874", "not_interested_storm_female") -- I'm not interested in that.
			clonedConversation:addOption("@conversation/imperial_broker:s_df2917b1", "storm_more_female") -- Tell me more
		end
	elseif (screenID == "storm_squadron") then
		CreatureObject(pNpc):doAnimation("pose_proudly")
	elseif (screenID == "not_interested_storm_male" or screenID == "not_interested_storm_female" or screenID == "storm_squadron_neutral_no_int") then
		CreatureObject(pNpc):doAnimation("shrug_hands")
	elseif (screenID == "storm_more_male" or screenID == "storm_more_female") then
		if (playerGender == 0) then
			CreatureObject(pNpc):doAnimation("explain")
		else
			CreatureObject(pNpc):doAnimation("nod_head_multiple")
		end

		SpaceHelpers:addStormSquadWaypoint(pPlayer)
		imperialBrokerConvoHandler:setBrokerStatus(pPlayer)
	elseif (screenID == "more_storm_neutral") then
		CreatureObject(pNpc):doAnimation("manipulate_medium")

		SpaceHelpers:addStormSquadWaypoint(pPlayer)
		imperialBrokerConvoHandler:setBrokerStatus(pPlayer)

	-- Imperial Insquisition
	elseif (screenID == "not_interested_inquisition_male") then
		CreatureObject(pNpc):doAnimation("sigh_deeply")
	elseif (screenID == "not_interested_inquisition_female") then
		CreatureObject(pNpc):doAnimation("shrug_shoulders")

	elseif (screenID == "what_inquisition_male" or screenID == "what_inquisition_female") then
		CreatureObject(pNpc):doAnimation("manipulate_medium")

		SpaceHelpers:addImperialInquisitionSquadWaypoint(pPlayer)
		imperialBrokerConvoHandler:setBrokerStatus(pPlayer)
	elseif (screenID == "more_inquisition_neutral") then
		CreatureObject(pNpc):doAnimation("whisper")

		SpaceHelpers:addImperialInquisitionSquadWaypoint(pPlayer)
		imperialBrokerConvoHandler:setBrokerStatus(pPlayer)

	-- Player is rebel
	elseif (screenID == "rebel_player") then
		if (CreatureObject(pPlayer):getSpecies() == SPECIES_WOOKIEE) then
			-- Wookiee wants to be pilot
			clonedConversation:addOption("@conversation/imperial_broker:s_61a663b2", "pilot_wookiee")
		elseif (playerGender == 0) then
			-- Rebel male wants to be pilot
			clonedConversation:addOption("@conversation/imperial_broker:s_61a663b2", "pilot_rebel")
		else
			-- Rebel female wants to be pilot
			clonedConversation:addOption("@conversation/imperial_broker:s_61a663b2", "pilot_female")
		end
	elseif (screenID == "stop_bothering") then
		CreatureObject(pNpc):doAnimation("wave_on_dismissing")
		imperialBrokerConvoHandler:setRebelBrokerStatus(pPlayer)
	elseif (screenID == "pilot_wookiee") then
		CreatureObject(pNpc):doAnimation("belly_laugh")
		imperialBrokerConvoHandler:setRebelBrokerStatus(pPlayer)
	elseif (screenID == "pilot_rebel") then
		CreatureObject(pNpc):doAnimation("slow_down")
		imperialBrokerConvoHandler:setRebelBrokerStatus(pPlayer)
	elseif (screenID == "pilot_female") then
		CreatureObject(pNpc):doAnimation("slow_down")
		imperialBrokerConvoHandler:setRebelBrokerStatus(pPlayer)

	-- Player is Imperial Pilot - Handle retirement
	elseif (screenID == "request_retire") then
		CreatureObject(pNpc):doAnimation("point_accusingly")
	elseif (screenID == "want_retirement") then
		CreatureObject(pNpc):doAnimation("shake_head_no")
	elseif (screenID == "confirm_retirement") then
		CreatureObject(pNpc):doAnimation("dismiss")

		SpaceHelpers:surrenderPilot(pPlayer)
	end

	return pConvScreen
end

function imperialBrokerConvoHandler:setBrokerStatus(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	writeData(playerID .. ":ImperialBroker:", 1)
end

function imperialBrokerConvoHandler:setRebelBrokerStatus(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	writeData(playerID .. ":ImperialBroker:rebel:", 1)
end