local ObjectManager = require("managers.object.object_manager")

local CRYSTAL_OBJECT = "object/tangible/loot/quest/force_sensitive/force_crystal.iff"

villageElderConvoHandler = conv_handler:new {}

function villageElderConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "intro") then
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pInvItem = getContainerObjectByTemplate(pInventory, CRYSTAL_OBJECT, true)

			if (pInvItem ~= nil) then
				clonedConversation:addOption("@conversation/village_elder_1:s_9dc8bf5d", "already_have_crystal") -- String does not change between phases, can use phase 1 string on all phases
			else
				clonedConversation:addOption("@conversation/village_elder_1:s_9dc8bf5d", "give_new_crystal") -- String does not change between phases, can use phase 1 string on all phases
			end
		end
		return conversationScreen
	elseif (screenID == "give_new_crystal") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pItem = getContainerObjectByTemplate(pInventory, CRYSTAL_OBJECT, true)

			if (pItem == nil) then
				if (SceneObject(pInventory):isContainerFullRecursive()) then
					CreatureObject(pPlayer):sendSystemMessage("@error_message:inv_full")
				else
					pItem = giveItem(pInventory, CRYSTAL_OBJECT, -1)

					if (pItem == nil) then
						CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
					end
				end
			end
		end
	end

	return pConvScreen
end
