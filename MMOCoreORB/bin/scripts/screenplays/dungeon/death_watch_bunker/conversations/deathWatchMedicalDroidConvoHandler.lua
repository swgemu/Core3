local ObjectManager = require("managers.object.object_manager")

deathWatchMedicalDroidConvoHandler = conv_handler:new {}

function deathWatchMedicalDroidConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "intro") then
		if (CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_foreman_stage") and not CreatureObject(pPlayer):hasScreenPlayState(4, "death_watch_foreman_stage")) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				if (SceneObject(pInventory):isContainerFullRecursive()) then
					clonedConversation:addOption("@conversation/death_watch_medical_droid:s_ab36bcfc", "inventory_full")
				else
					clonedConversation:addOption("@conversation/death_watch_medical_droid:s_ab36bcfc", "cure_issued")
				end
			end
		else
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:not_authorized")
		end
		clonedConversation:addOption("@conversation/death_watch_medical_droid:s_82d3782a", "please_return")
	elseif (screenID == "cure_issued") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			if (getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", true) == nil) then
				local pCure = giveItem(pInventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", -1)

				if (pCure == nil) then
					CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
				else
					CreatureObject(pPlayer):sendSystemMessage("@system_msg:give_item_success")
				end
			end
		end
	end

	return pConvScreen
end
