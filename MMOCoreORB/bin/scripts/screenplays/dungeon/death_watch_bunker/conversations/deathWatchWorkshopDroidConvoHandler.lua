local ObjectManager = require("managers.object.object_manager")

deathWatchWorkshopDroidConvoHandler = {  }

function deathWatchWorkshopDroidConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()
	local pLastConversationScreen = nil
	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)
		return conversationTemplate:getScreen(optionLink)
	end
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end

function deathWatchWorkshopDroidConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

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

function deathWatchWorkshopDroidConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "no_battery_intro" or screenID == "intro") then
		CreatureObject(conversingNPC):playEffect("clienteffect/treadwell_chatter_01.cef", "")
	elseif (screenID == "clean_battery" or screenID == "end_convo") then
		CreatureObject(conversingNPC):playEffect("clienteffect/treadwell_chatter_02.cef", "")
	end

	if (screenID == "clean_battery") then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pBatt = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true)

			if (pBatt == nil) then
				CreatureObject(conversingPlayer):sendSystemMessage("Error: Battery not found in inventory.")
				return 0
			end

			SceneObject(pBatt):destroyObjectFromWorld()
			SceneObject(pBatt):destroyObjectFromDatabase()

			if (SceneObject(pInventory):isContainerFullRecursive() == true) then
				CreatureObject(conversingPlayer):sendSystemMessage("@error_message:inv_full")
			else
				local pCleanBatt = giveItem(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery_clean.iff", -1)

				if (pCleanBatt == nil) then
					CreatureObject(conversingPlayer):sendSystemMessage("Error: Unable to generate item.")
				else
					CreatureObject(conversingPlayer):sendSystemMessage("@dungeon/death_watch:battery_cleaned")
				end
			end
		else
			CreatureObject(conversingPlayer):sendSystemMessage("@dungeon/death_watch:need_battery")
		end
	end

	return conversationScreen
end
