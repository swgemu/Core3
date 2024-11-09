ioTsomcrenConvoHandler = conv_handler:new {}

function ioTsomcrenConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	--if (found shipment) then
	--	return convoTemplate:getScreen("wow_you_helped")
	--end

	CreatureObject(pNpc):doAnimation("rub_belly")

	return convoTemplate:getScreen("i_bet_an")
end

function ioTsomcrenConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local stringFile = "@conversation/greeter_coronet_shipwright_indifferent"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "why_dont_you") then
		CreatureObject(pNpc):doAnimation("explain")
	elseif (screenID == "thats_too_bad") then
		CreatureObject(pNpc):doAnimation("nod_head_once")
	end

	return pConvScreen
end

