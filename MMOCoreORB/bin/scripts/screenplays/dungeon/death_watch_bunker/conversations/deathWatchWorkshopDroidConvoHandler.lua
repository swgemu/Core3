local ObjectManager = require("managers.object.object_manager")

deathWatchWorkshopDroidConvoHandler = conv_handler:new {}

function deathWatchWorkshopDroidConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(16, "death_watch_foreman_stage") or not CreatureObject(pPlayer):hasScreenPlayState(8, "death_watch_foreman_stage")) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:not_authorized")
		return convoTemplate:getScreen("end_convo")
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:need_battery")
		return convoTemplate:getScreen("no_battery_intro")
	end

	if (getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true) == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:need_battery")
		return convoTemplate:getScreen("no_battery_intro")
	end

	return convoTemplate:getScreen("intro")
end

function deathWatchWorkshopDroidConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "no_battery_intro" or screenID == "intro") then
		CreatureObject(pNpc):playEffect("clienteffect/treadwell_chatter_01.cef", "")
	elseif (screenID == "clean_battery" or screenID == "end_convo") then
		CreatureObject(pNpc):playEffect("clienteffect/treadwell_chatter_02.cef", "")
	end

	if (screenID == "clean_battery") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pBatt = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true)

			if (pBatt == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Battery not found in inventory.")
				return 0
			end

			SceneObject(pBatt):destroyObjectFromWorld()
			SceneObject(pBatt):destroyObjectFromDatabase()

			if (SceneObject(pInventory):isContainerFullRecursive() == true) then
				CreatureObject(pPlayer):sendSystemMessage("@error_message:inv_full")
			else
				local pCleanBatt = giveItem(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery_clean.iff", -1)

				if (pCleanBatt == nil) then
					CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
				else
					CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:battery_cleaned")
				end
			end
		else
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:need_battery")
		end
	end

	return pConvScreen
end
