local ObjectManager = require("managers.object.object_manager")

deathWatchWorkshopDroidConvoHandler = {  }

function deathWatchWorkshopDroidConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local pConversationSession = player:getConversationSession()
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
	end)
end

function deathWatchWorkshopDroidConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		if (player:hasScreenPlayState(16, "death_watch_foreman_stage") or not player:hasScreenPlayState(8, "death_watch_foreman_stage")) then
			player:sendSystemMessage("@dungeon/death_watch:not_authorized")
			return convoTemplate:getScreen("end_convo")
		end

		local pInventory = player:getSlottedObject("inventory")

		if (pInventory == nil) then
			player:sendSystemMessage("@dungeon/death_watch:need_battery")
			return convoTemplate:getScreen("no_battery_intro")
		end

		if (getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true) == nil) then
			player:sendSystemMessage("@dungeon/death_watch:need_battery")
			return convoTemplate:getScreen("no_battery_intro")
		end

		return convoTemplate:getScreen("intro")
	end)
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

	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		if (screenID == "clean_battery") then
			local pInventory = player:getSlottedObject("inventory")

			if (pInventory ~= nil) then
				local pBatt = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true)

				if (pBatt == nil) then
					player:sendSystemMessage("Error: Battery not found in inventory.")
					return 0
				end

				SceneObject(pBatt):destroyObjectFromWorld()
				SceneObject(pBatt):destroyObjectFromDatabase()

				if (SceneObject(pInventory):isContainerFullRecursive() == true) then
					player:sendSystemMessage("@error_message:inv_full")
				else
					local pCleanBatt = giveItem(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery_clean.iff", -1)

					if (pCleanBatt == nil) then
						player:sendSystemMessage("Error: Unable to generate item.")
					else
						player:sendSystemMessage("@dungeon/death_watch:battery_cleaned")
					end
				end
			else
				player:sendSystemMessage("@dungeon/death_watch:need_battery")
			end
		end

		return conversationScreen
	end)
end