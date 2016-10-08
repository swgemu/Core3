OevittPiboiConversationHandler = conv_handler:new {}

function OevittPiboiConversationHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if (screenID == "escapee_2") then
		WarrenScreenPlay:givePasskey1(pPlayer)
	end

	return pConvScreen
end

function OevittPiboiConversationHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pPasskey = getContainerObjectByTemplate(pInventory, WarrenScreenPlay.entranceKey, true)

		if (pPasskey ~= nil) then
			return convoTemplate:getScreen("escapee_haskey")
		end
	end

	return convoTemplate:getScreen("escapee_start")
end
