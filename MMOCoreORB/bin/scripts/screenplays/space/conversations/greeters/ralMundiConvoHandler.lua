local SpaceHelpers = require("utils.space_helpers")

ralMundiConvoHandler = conv_handler:new {}

function ralMundiConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not isJtlEnabled()) then
		CreatureObject(pNpc):doAnimation("laugh_titter")
		CreatureObject(pPlayer):doAnimation("shrug_shoulders")

		return convoTemplate:getScreen("no_jtl")
	end

	if (SpaceHelpers:isRebelPilot(pPlayer)) then
		return convoTemplate:getScreen("rebel_pilot")
	elseif (SpaceHelpers:isImperialPilot(pPlayer)) then
		return convoTemplate:getScreen("imperial_pilot")
	elseif (SpaceHelpers:isNeutralPilot(pPlayer)) then
		return convoTemplate:getScreen("neutral_pilot")
	end

	CreatureObject(pNpc):doAnimation("greet")

	return convoTemplate:getScreen("not_pilot")
end

function ralMundiConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local stringFile = "@conversation/ral_mundi"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "why_are_they" or screenID == "free_ships") then
		CreatureObject(pNpc):doAnimation("explain")
	elseif (screenID == "thats_too_bad") then
		CreatureObject(pNpc):doAnimation("laugh_cackle")
	elseif (screenID == "need_starship") then
		CreatureObject(pNpc):doAnimation("rub_chin_thoughtful")
	elseif (screenID == "no_money") then
		CreatureObject(pNpc):doAnimation("shake_head_disgust")
	end

	return pConvScreen
end

