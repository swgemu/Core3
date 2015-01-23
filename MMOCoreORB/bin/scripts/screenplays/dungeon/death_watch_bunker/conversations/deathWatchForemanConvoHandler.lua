local ObjectManager = require("managers.object.object_manager")

--[[ Foreman states:
1 - Spoke to foreman
2 - Started haldo quest
4 - Finished haldo quest
8 - Started battery quest
16 - Finished battery quest
32 - Started pumps quest
64 - Finished pumps quest
128 - Received mineral
]]

deathWatchForemanConvoHandler = {  }

function deathWatchForemanConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function deathWatchForemanConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)

		-- Player has not spoken to Foreman before
		if (player:hasScreenPlayState(1, "death_watch_foreman_stage") == 0) then
			return convoTemplate:getScreen("init")
		end

		--Player has spoken to Foreman but has not started Haldo quest
		if (player:hasScreenPlayState(2, "death_watch_foreman_stage") == 0) then
			return convoTemplate:getScreen("offer_quest_again")
		end

		-- Player has started but not completed Haldo quest
		if (player:hasScreenPlayState(4, "death_watch_foreman_stage") == 0) then
			return convoTemplate:getScreen("found_him_yet")
		end

		-- Player has completed Haldo quest but has not started quest to clean battery
		if (player:hasScreenPlayState(8, "death_watch_foreman_stage") == 0) then
			if (player:hasScreenPlayState(4, "death_watch_haldo") == 0) then
				return convoTemplate:getScreen("thank_you_didnt_kill")
			else
				return convoTemplate:getScreen("thank_you_killed")
			end
		end

		-- Player has started but not completed battery cleaning quest
		if (player:hasScreenPlayState(16, "death_watch_foreman_stage") == 0) then
			local pInventory = player:getSlottedObject("inventory")

			if (pInventory == nil) then
				return convoTemplate:getScreen("return_battery_not_clean")
			end

			local pBatt = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery_clean.iff", true)

			if (pBatt ~= nil) then
				if (player:hasScreenPlayState(4, "death_watch_haldo") == 0) then
					return convoTemplate:getScreen("return_battery_cleaned_no_haldo_kill")
				else
					return convoTemplate:getScreen("return_battery_cleaned_killed_haldo")
				end
			end

			return convoTemplate:getScreen("return_battery_not_clean")
		end

		-- Player has completed battery cleaning but not started pump quest
		if (player:hasScreenPlayState(32, "death_watch_foreman_stage") == 0) then
			return convoTemplate:getScreen("pump_room_upstairs")
		end

		-- Player has started but not completed pump quest
		if (player:hasScreenPlayState(64, "death_watch_foreman_stage") == 0) then
			if (player:hasScreenPlayState(2, "death_watch_foreman_stage_failed") == 1) then
				return convoTemplate:getScreen("try_pump_again")
			end
			return convoTemplate:getScreen("pump_timer_running")
		end

		-- Player has completed but not turned in pump quest
		if (player:hasScreenPlayState(128, "death_watch_foreman_stage") == 0) then
			if (player:hasScreenPlayState(4, "death_watch_haldo") == 1) then
				return convoTemplate:getScreen("pump_success_haldo_kill")
			end
			return convoTemplate:getScreen("pump_success_no_haldo_kill")
		end

		-- Player has completed entire chain, returning for more ore
		if (DeathWatchBunkerScreenPlay:checkTime(pPlayer) == true) then
			local pInventory = player:getSlottedObject("inventory")
			if (pInventory == nil) then
				return convoTemplate:getScreen("no_ore_yet")
			elseif (SceneObject(pInventory):hasFullContainerObjects()) then
				return convoTemplate:getScreen("more_ore_inv_full")
			else
				return convoTemplate:getScreen("more_ore")
			end
		else
			return convoTemplate:getScreen("no_ore_yet")
		end
	end)
end

function deathWatchForemanConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "great_remember_medicine") then
			player:setScreenPlayState(1, "death_watch_foreman_stage")
		end
		if (screenID == "what_i_expected") then
			player:removeScreenPlayState(2, "death_watch_foreman_stage")
		end
		if (screenID == "great_remember_medicine" or screenID == "return_great_remember_medicine") then
			DeathWatchBunkerScreenPlay:startForemanQuestStage(1, conversingPlayer)
			player:setScreenPlayState(2, "death_watch_foreman_stage")
		end
		if (screenID == "return_battery_cleaned_no_haldo_kill") then
			local pInventory = player:getSlottedObject("inventory")

			if (pInventory ~= nil) then
				local pBatt = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery_clean.iff", true)

				if (pBatt == nil) then
					player:sendSystemMessage("Error: Battery not found in inventory.")
					return 0
				end

				SceneObject(pBatt):destroyObjectFromWorld()
				SceneObject(pBatt):destroyObjectFromDatabase()
				player:setScreenPlayState(16, "death_watch_foreman_stage")
			end
		end
		if ((screenID == "thank_you_didnt_kill" or screenID == "thank_you_killed") and player:hasScreenPlayState(4, "death_watch_foreman_stage") == 0) then
			player:setScreenPlayState(4, "death_watch_foreman_stage")
		end

		if (screenID == "up_for_danger" or screenID == "speak_to_treadwell") then
			player:setScreenPlayState(8, "death_watch_foreman_stage")
		end
		if (screenID == "come_back_after_pumps" or screenID == "remember_tricky_pumps") then
			player:setScreenPlayState(32, "death_watch_foreman_stage")
			player:removeScreenPlayState(2, "death_watch_foreman_stage_failed")
			DeathWatchBunkerScreenPlay:startForemanQuestStage(2, conversingPlayer)
		end
		if (screenID == "ore_reward") then
			player:setScreenPlayState(128, "death_watch_foreman_stage")
		end
		if (screenID == "ore_reward" or screenID == "more_ore") then
			DeathWatchBunkerScreenPlay:storeTime(conversingPlayer)
			local pInventory = player:getSlottedObject("inventory")

			if (pInventory == nil) then
				return 0
			end

			local pOre = giveItem(pInventory, "object/tangible/loot/dungeon/death_watch_bunker/mining_drill_reward.iff", -1)

			if (pOre == nil) then
				player:sendSystemMessage("Error: Unable to generate item.")
				return 0
			end
		end
		if (screenID == "found_him_yet") then
			local pInventory = player:getSlottedObject("inventory")
			if (pInventory ~= nil) then
				if (getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true) ~= nil) then
					if (player:hasScreenPlayState(4, "death_watch_haldo") == 0) then
						clonedConversation:addOption("@conversation/death_watch_foreman:s_829888a9", "thank_you_didnt_kill")
					else
						clonedConversation:addOption("@conversation/death_watch_foreman:s_829888a9", "thank_you_killed")
					end
				end
			end
			clonedConversation:addOption("@conversation/death_watch_foreman:s_c825f420", "please_hurry")
			clonedConversation:addOption("@conversation/death_watch_foreman:s_baac9005", "what_i_expected")
		end
		if (screenID == "pump_room_upstairs") then
			if (player:hasScreenPlayState(4, "death_watch_haldo") == 0) then
				clonedConversation:addOption("@conversation/death_watch_foreman:s_d4b1da9f", "tricky_pumps_no_haldo_kill")
			else
				clonedConversation:addOption("@conversation/death_watch_foreman:s_d4b1da9f", "tricky_pumps_haldo_kill")
			end
			clonedConversation:addOption("@conversation/death_watch_foreman:s_3055077f", "choice_is_yours")
		end
		if (screenID == "pump_success_haldo_kill" or screenID == "pump_success_no_haldo_kill") then
			local pInventory = player:getSlottedObject("inventory")

			if (pInventory == nil) then
				return 0
			end

			if (SceneObject(pInventory):hasFullContainerObjects()) then
				if (screenID == "pump_success_haldo_kill") then
					clonedConversation:addOption("@conversation/death_watch_foreman:s_c04f0d0d", "ore_inv_full")
				else
					clonedConversation:addOption("@conversation/death_watch_foreman:s_5597accd", "ore_inv_full")
				end
			else
				if (screenID == "pump_success_haldo_kill") then
					clonedConversation:addOption("@conversation/death_watch_foreman:s_c04f0d0d", "used_in_armor")
				else
					clonedConversation:addOption("@conversation/death_watch_foreman:s_5597accd", "sneak_some_ore")
				end
			end
		end
		return conversationScreen
	end)
end