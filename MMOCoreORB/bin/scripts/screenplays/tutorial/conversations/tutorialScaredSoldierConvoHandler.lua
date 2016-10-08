local ObjectManager = require("managers.object.object_manager")

tutorialScaredSoldierConvoHandler = conv_handler:new {}

function tutorialScaredSoldierConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "need_weapon") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil) then
			return
		end

		addStartingWeaponsInto(pPlayer, pInventory)
		writeData(SceneObject(pPlayer):getObjectID() .. ":tutorial:givenWeapon", 1)
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:receive_weapon")
	end

	return pConvScreen
end

function tutorialScaredSoldierConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if (readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:givenWeapon") == 1) then
		return convoTemplate:getScreen("intro_repeat")
	else
		return convoTemplate:getScreen("intro")
	end
end
