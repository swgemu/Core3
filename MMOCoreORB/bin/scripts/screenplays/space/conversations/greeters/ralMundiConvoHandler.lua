ralMundiConvoHandler = conv_handler:new {}

function ralMundiConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	-- Does not have JTL check??
	-- return convoTemplate:getScreen("no_jtl")

	--if (shipment quest complete) then
	--	return convoTemplate:getScreen("welcome_i_cannot")
	--end




	CreatureObject(pNpc):doAnimation("beckon")

	return convoTemplate:getScreen("initial_greeting")
end

function ralMundiConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local stringFile = "@conversation/ral_mundi"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "why_are_they") then
		CreatureObject(pNpc):doAnimation("explain")
	elseif (screenID == "thats_too_bad") then
		CreatureObject(pNpc):doAnimation("laugh_cackle")
	end

	return pConvScreen
end

