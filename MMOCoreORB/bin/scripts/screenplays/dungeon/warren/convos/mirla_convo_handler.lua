local ObjectManager = require("managers.object.object_manager")

MirlaConversationHandler = conv_handler:new {}

function MirlaConversationHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "mirla_password") then
		local code = readStringData("warren:cellPassword")
		clonedConversation:setDialogTextTO(code)
		dropObserver(SPATIALCHATSENT, pPlayer)
		createObserver(SPATIALCHATSENT, "Warren", "notifyTerminalChatSent", pPlayer)
	elseif (screenID == "mirla_2") then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_farewell_letter.iff", true)

			if (pItem ~= nil) then
				SceneObject(pItem):destroyObjectFromWorld()
				SceneObject(pItem):destroyObjectFromDatabase()

				local pGhost = CreatureObject(pPlayer):getPlayerObject()

				if (pGhost ~= nil) then
					PlayerObject(pGhost):awardBadge(38) --Warren Compassion
				end
			end
		end
	elseif (screenID == "mirla_1") then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_farewell_letter.iff", true)) then
			clonedConversation:addOption("@theme_park/warren/warren:mirla_1_reply_1", "mirla_2")
		end

		clonedConversation:addOption("@theme_park/warren/warren:mirla_1_reply_2", "mirla_3")
	end

	return pConvScreen
end

function MirlaConversationHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("mirla_start")
	end

	if (PlayerObject(pGhost):hasBadge(39)) then
		return convoTemplate:getScreen("mirla_done")
	elseif (PlayerObject(pGhost):hasBadge(38)) then
		return convoTemplate:getScreen("mirla_get_teraud")
	end

	return convoTemplate:getScreen("mirla_start")
end
