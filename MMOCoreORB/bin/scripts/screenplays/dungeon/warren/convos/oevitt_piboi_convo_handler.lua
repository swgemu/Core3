OevittPiboiConversationHandler = conv_handler:new {}

function OevittPiboiConversationHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if (screenID == "escapee_2") then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			giveItem(pInventory, "object/tangible/mission/quest_item/warren_passkey_s01.iff", -1)
		end
	end

	return pConvScreen
end

function OevittPiboiConversationHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_passkey_s01.iff", true) ~= nil) then
		return convoTemplate:getScreen("escapee_haskey")
	end

	return convoTemplate:getScreen("escapee_start")
end
