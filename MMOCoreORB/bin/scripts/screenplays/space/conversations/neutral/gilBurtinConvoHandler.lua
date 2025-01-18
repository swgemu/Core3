local SpaceHelpers = require("utils.space_helpers")

gilBurtinConvoHandler = conv_handler:new {}

function gilBurtinConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("you_dont_look")
	end

	-- Player is a neutral pilot
	if (SpaceHelpers:isNeutralPilot(pPlayer)) then
		return convoTemplate:getScreen("hey_ive_heard")
	-- Player is rebel or imperial pilot
	elseif (SpaceHelpers:isPilot(pPlayer)) then
		return convoTemplate:getScreen("hello_nice_to")
	-- Player is not a pilot at all, ask if they want to join
	else
		return convoTemplate:getScreen("yes__")
	end
end

function gilBurtinConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pConvTemplate == nil or pPlayer == nil or pNpc == nil) then
		return nil
	end

	local stringFile = "@conversation/gil_burtin"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	-- Handle Retirement
	if (screenID == "ive_come_to_retire") then
		CreatureObject(pNpc):doAnimation("explain")

	elseif (screenID == "yes_retire") then
		CreatureObject(pNpc):doAnimation("shrug_hands")
	elseif (screenID == "i_want_to_retire") then
		CreatureObject(pNpc):doAnimation("shake_head_no")

		SpaceHelpers:surrenderPilot(pPlayer)
	elseif (screenID == "yes_i_want") then
		CreatureObject(pNpc):doAnimation("shrug_hands")

	-- Handle Joining
	elseif (screenID == "yes__") then
		CreatureObject(pNpc):doAnimation("dismiss")
	elseif (screenID == "never_mind") then
		CreatureObject(pNpc):doAnimation("wave2")
	elseif (screenID == "ive_come_to_join") then
		CreatureObject(pPlayer):doAnimation("point_to_self")
		CreatureObject(pNpc):doAnimation("shrug_shoulders")
	elseif (screenID == "what_trouble") then
		CreatureObject(pPlayer):doAnimation("shrug_hands")
		CreatureObject(pNpc):doAnimation("gesticulate_wildly")
	elseif (screenID == "why_dont_you_1") then
		CreatureObject(pPlayer):doAnimation("shrug_shoulders")
		CreatureObject(pNpc):doAnimation("dismiss")
	elseif (screenID == "i_see") then
		CreatureObject(pPlayer):doAnimation("nod_head_once")
		CreatureObject(pNpc):doAnimation("slow_down")
	elseif (screenID == "so_where_is") then
		CreatureObject(pPlayer):doAnimation("nervous")
		CreatureObject(pNpc):doAnimation("sigh_deeply")
	elseif (screenID == "no_what_is") then
		CreatureObject(pPlayer):doAnimation("shake_head_no")
		CreatureObject(pNpc):doAnimation("shrug_hands")
	elseif (screenID == "not_really") then
		CreatureObject(pPlayer):doAnimation("shake_head_no")
		CreatureObject(pNpc):doAnimation("nod_head_multiple")
	elseif (screenID == "where_else_can") then
		CreatureObject(pNpc):doAnimation("explain")

	-- Handle Waypoints

	-- CorSec
	elseif (screenID == "corsec_") then
		CreatureObject(pNpc):doAnimation("nod_head_multiple")
	elseif (screenID == "tell_me_more_corsec") then
		SpaceHelpers:addCorsecPilotWaypoint(pPlayer)

	-- RSF
	elseif (screenID == "rsf") then
		CreatureObject(pNpc):doAnimation("laugh_cackle")
	elseif (screenID == "tell_me_more_rsf") then
		CreatureObject(pNpc):doAnimation("laugh_titter")

		SpaceHelpers:addRSFPilotWaypoint(pPlayer)
	elseif (screenID == "not_interested_rsf") then
		CreatureObject(pNpc):doAnimation("shrug_hands")

	-- Tatooine
	elseif (screenID == "tatooine") then
		CreatureObject(pNpc):doAnimation("nod_head_multiple")
	elseif (screenID == "tell_me_more_tatooine") then
		SpaceHelpers:addSmugglersPilotWaypoint(pPlayer)

	-- Rebel Alliance
	elseif (screenID == "rebel_alliance") then
		CreatureObject(pNpc):doAnimation("nod_head_multiple")
	elseif (screenID == "tell_me_more_rebel") then
		SpaceHelpers:addRebelPilotWaypoint(pPlayer)

	-- Empire
	elseif (screenID == "empire_coordinates") then
		CreatureObject(pPlayer):doAnimation("nod_head_once")
		CreatureObject(pNpc):doAnimation("slow_down")

		SpaceHelpers:addImperialPilotWaypoint(pPlayer)
	elseif (screenID == "yes_i_do") then
		CreatureObject(pPlayer):doAnimation("nod_head_multiple")
		CreatureObject(pNpc):doAnimation("point_to_self")
	elseif (screenID == "i_was_just") then
		CreatureObject(pPlayer):doAnimation("shrug_shoulders")
		CreatureObject(pNpc):doAnimation("rub_chin_thoughtful")
	elseif (screenID == "empire_coordinates2") then
		CreatureObject(pPlayer):doAnimation("point_accusingly")
		CreatureObject(pNpc):doAnimation("slow_down")

		SpaceHelpers:addImperialPilotWaypoint(pPlayer)
	elseif (screenID == "other_choices") then
		CreatureObject(pPlayer):doAnimation("shrug_shoulders")
		CreatureObject(pNpc):doAnimation("nervous")
	end

	return pConvScreen
end
