local SpaceHelpers = require("utils.space_helpers")

tutorialImperialBrokerConvoHandler = conv_handler:new {}

function tutorialImperialBrokerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()

	-- Greet
	if (screenID == "greet") then
		CreatureObject(pNpc):doAnimation("salute2")

	-- Recruiting
	elseif (screenID == "recruiting") then
		CreatureObject(pNpc):doAnimation("explain")
	elseif (screenID == "no_never_mind") then
		CreatureObject(pNpc):doAnimation("salute2")

	-- Black Epsilon
	elseif (screenID == "black_epsilon") then
		CreatureObject(pNpc):doAnimation("nod_head_once")
	elseif (screenID == "not_interested_be") then
		CreatureObject(pNpc):doAnimation("shrug_hands")
	elseif (screenID == "more_black_epsilon") then
		CreatureObject(pNpc):doAnimation("wave_finger_warning")
		SpaceHelpers:addBlackEpsilonSquadWaypoint(pPlayer)

	-- Storm Squadron
	elseif (screenID == "storm_squadron") then
		CreatureObject(pNpc):doAnimation("pose_proudly")
	elseif (screenID == "not_interested_storm") then
		CreatureObject(pNpc):doAnimation("shrug_hands")
	elseif (screenID == "more_storm") then
		CreatureObject(pNpc):doAnimation("manipulate_medium")
		SpaceHelpers:addStormSquadWaypoint(pPlayer)

	-- Imperial Inquisition
	elseif (screenID == "imperial_inquisition") then
		CreatureObject(pNpc):doAnimation("explain")
	elseif (screenID == "not_interested_inquisition") then
		CreatureObject(pNpc):doAnimation("shrug_hands")
	elseif (screenID == "more_inquisition") then
		CreatureObject(pNpc):doAnimation("whisper")
		SpaceHelpers:addImperialInquisitionSquadWaypoint(pPlayer)

	-- Goodbye
	elseif (screenID == "goodbye_salute") then
		CreatureObject(pNpc):doAnimation("salute2")
		CreatureObject(pPlayer):doAnimation("salute2")
	end

	return pConvScreen
end
