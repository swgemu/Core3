OevittPiboiConversationHandler = conv_handler:new {}

function OevittPiboiConversationHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if (screenID == "escapee_2") then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			giveItem(pInventory, "object/tangible/mission/quest_item/warren_passkey_s01.iff", -1)
		end
		
		local pGhost = CreatureObject(pPlayer):getPlayerObject()
		
		if (pGhost ~= nil) then
			PlayerObject(pGhost):addWaypoint("dantooine", "@theme_park/warren/warren_system_messages:waypoint_name", "", -546, -3846, WAYPOINTBLUE, true, true, 0)
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
