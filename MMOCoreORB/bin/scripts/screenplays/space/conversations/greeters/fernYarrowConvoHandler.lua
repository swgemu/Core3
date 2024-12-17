fernYarrowConvoHandler = conv_handler:new {}

function fernYarrowConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("no_jtl")
	end

	if (SpaceHelpers:isRebelPilot(pPlayer)) then
		return convoTemplate:getScreen("rebel_pilot")
	end

	CreatureObject(pNpc):doAnimation("hands_above_head")

	return convoTemplate:getScreen("can_you_believe")
end

function fernYarrowConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local stringFile = "@conversation/greeter_dantooine_brother_imperial"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "whats_so_unbelievable") then
		CreatureObject(pNpc):doAnimation("pound_fist_palm")
	elseif (screenID == "isnt_fern_a") then
		CreatureObject(pNpc):doAnimation("gesticulate_wildly")
	elseif (screenID == "why_dont_you") then
		CreatureObject(pNpc):doAnimation("nervous")
	elseif (screenID == "why_doesnt_your") then
		CreatureObject(pNpc):doAnimation("rub_chin_thoughtful")
	end

	return pConvScreen
end

