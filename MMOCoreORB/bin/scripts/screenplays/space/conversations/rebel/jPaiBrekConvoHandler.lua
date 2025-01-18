local SpaceHelpers = require("utils.space_helpers")

jPaiBrekConvoHandler = conv_handler:new {}

function jPaiBrekConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerFactionStatus = CreatureObject(pPlayer):getFactionStatus()

	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("nothing_i_can")
	end

	-- Player is a Rebel pilot
	if (SpaceHelpers:isRebelPilot(pPlayer) and faction == FACTIONREBEL and playerFactionStatus > ONLEAVE) then
		CreatureObject(pNpc):doAnimation("greet")

		return convoTemplate:getScreen("hello_rebel_pilot")
	-- Player is imperial
	elseif (faction == FACTIONIMPERIAL) then
		CreatureObject(pNpc):doAnimation("stretch")

		return convoTemplate:getScreen("is_there_something")
	-- Player is a pilot
	elseif (SpaceHelpers:isPilot(pPlayer)) then
		return convoTemplate:getScreen("hello_friend_good")
	end

	-- Player is not affiliated pilot
	return convoTemplate:getScreen("unknown_yes")
end

function jPaiBrekConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local stringFile = "@conversation/rebel_broker"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	-- Player is imperial
	if (screenID == "nice_meeting") then
		CreatureObject(pNpc):doAnimation("wave2")
	elseif (screenID == "yes_imp") then
		CreatureObject(pNpc):doAnimation("yawn")
	elseif (screenID == "are_you_recruiting") then
		CreatureObject(pNpc):doAnimation("shake_head_no")
	elseif (screenID == "i_dont_believe") then
		CreatureObject(pNpc):doAnimation("slow_down")
	elseif (screenID == "you_are_lying") then
		CreatureObject(pNpc):doAnimation("point_accusingly")

	-- Pilot Recruiting
	elseif (screenID == "who_are_you") then
		CreatureObject(pNpc):doAnimation("point_to_self")
	elseif (screenID == "become_pilot") then
		CreatureObject(pNpc):doAnimation("nod_head_multiple")
	elseif (screenID == "rebel_transmission") then
		CreatureObject(pNpc):doAnimation("snap_finger2")

	-- Naboo - Vortex Squadron
	elseif (screenID == "naboo_rebel") then
		CreatureObject(pNpc):doAnimation("pound_fist_palm")
	elseif (screenID == "vortex_location") then
		CreatureObject(pNpc):doAnimation("wave_finger_warning")

		SpaceHelpers:addVortexSquadWaypoint(pPlayer)

	-- Corellia - Akron's Havok Squad
	elseif (screenID == "corellia_rebel") then
		CreatureObject(pNpc):doAnimation("explain")
	elseif (screenID == "akron_location") then
		CreatureObject(pNpc):doAnimation("point_away")

		SpaceHelpers:addAkronSquadWaypoint(pPlayer)

	-- Tatooine - Crimson Phoenix Squadron
	elseif (screenID == "tatooine_rebel") then
		CreatureObject(pNpc):doAnimation("explain")
	elseif (screenID == "crimson_location") then
		CreatureObject(pNpc):doAnimation("manipulate_medium")

		SpaceHelpers:addCrimsonSquadWaypoint(pPlayer)

	-- Player is Rebel Pilot - Handle retirement
	elseif (screenID == "hello_rebel_pilot") then
		CreatureObject(pNpc):doAnimation("greet")
	elseif (screenID == "request_retire") then
		CreatureObject(pNpc):doAnimation("rub_chin_thoughtful")
	elseif (screenID == "want_retirement") then
		CreatureObject(pNpc):doAnimation("nod_head_once")
	elseif (screenID == "confirm_retirement") then
		CreatureObject(pNpc):doAnimation("sigh_deeply")

		SpaceHelpers:surrenderPilot(pPlayer)
	end

	return pConvScreen
end

