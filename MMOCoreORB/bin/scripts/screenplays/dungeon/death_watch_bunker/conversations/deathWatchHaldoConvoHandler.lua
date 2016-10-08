local ObjectManager = require("managers.object.object_manager")

deathWatchHaldoConvoHandler = conv_handler:new {}

-- Screenplay states: 1 - Talked to Haldo, 2 - Helped Haldo, 4 - Killed Haldo

function deathWatchHaldoConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_foreman_stage")) then
		return convoTemplate:getScreen("intro_noquest")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_haldo")) then
		return convoTemplate:getScreen("thank_you")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "death_watch_haldo")) then
		return convoTemplate:getScreen("return_intro")
	else
		return convoTemplate:getScreen("intro")
	end
end

function deathWatchHaldoConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "intro") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pCure = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", true)
			if (pCure ~= nil) then
				clonedConversation:addOption("@conversation/death_watch_insane_miner:s_dad50efa", "please_give")
			end
		end
		clonedConversation:addOption("@conversation/death_watch_insane_miner:s_3fb7180e", "medical_droid")
		clonedConversation:addOption("@conversation/death_watch_insane_miner:s_4fe1bc67", "wont_help")
	elseif (screenID == "please_hurry") then
		CreatureObject(pPlayer):setScreenPlayState(1, "death_watch_haldo")
	elseif (screenID == "wont_help") then
		DeathWatchBunkerScreenPlay:spawnAggroHaldo(pNpc, pPlayer)
	elseif (screenID == "thank_you") then
		if (not CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_haldo")) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pCure = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", true)

				if (pCure == nil) then
					CreatureObject(pPlayer):sendSystemMessage("Error: Cure not found in inventory.")
					return 0
				end

				SceneObject(pCure):destroyObjectFromWorld()
				SceneObject(pCure):destroyObjectFromDatabase()

				if (SceneObject(pInventory):isContainerFullRecursive() == true) then
					CreatureObject(pPlayer):sendSystemMessage("@error_message:inv_full")
					return 0
				else
					local pBattery = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true)
					if (pBattery == nil) then
						pBattery = giveItem(pInventory,"object/tangible/dungeon/death_watch_bunker/drill_battery.iff", -1)
						if (pBattery == nil) then
							CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
							return 0
						end
					end
				end

				CreatureObject(pPlayer):setScreenPlayState(2, "death_watch_haldo")
			else
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to find player inventory.")
			end
		end
	end

	return pConvScreen
end
