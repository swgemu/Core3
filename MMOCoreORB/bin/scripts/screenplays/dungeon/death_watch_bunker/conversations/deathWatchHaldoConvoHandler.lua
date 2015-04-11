local ObjectManager = require("managers.object.object_manager")

deathWatchHaldoConvoHandler = {  }

-- Screenplay states: 1 - Talked to Haldo, 2 - Helped Haldo, 4 - Killed Haldo

function deathWatchHaldoConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function deathWatchHaldoConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if (not player:hasScreenPlayState(2, "death_watch_foreman_stage")) then
			return convoTemplate:getScreen("intro_noquest")
		elseif (player:hasScreenPlayState(2, "death_watch_haldo")) then
			return convoTemplate:getScreen("thank_you")
		elseif (player:hasScreenPlayState(1, "death_watch_haldo")) then
			return convoTemplate:getScreen("return_intro")
		else
			return convoTemplate:getScreen("intro")
		end
	end)
end

function deathWatchHaldoConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player, playerObject)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "intro") then
			local pInventory = player:getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pCure = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", true)
				if (pCure ~= nil) then
					clonedConversation:addOption("@conversation/death_watch_insane_miner:s_dad50efa", "please_give")
				end
			end
			clonedConversation:addOption("@conversation/death_watch_insane_miner:s_3fb7180e", "medical_droid")
			clonedConversation:addOption("@conversation/death_watch_insane_miner:s_4fe1bc67", "wont_help")
		elseif (screenID == "please_hurry") then
			player:setScreenPlayState(1, "death_watch_haldo")
		elseif (screenID == "wont_help") then
			DeathWatchBunkerScreenPlay:spawnAggroHaldo(conversingNPC, conversingPlayer)
		elseif (screenID == "thank_you") then
			if (not player:hasScreenPlayState(2, "death_watch_haldo")) then
				local pInventory = player:getSlottedObject("inventory")
				if (pInventory ~= nil) then
					local pCure = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", true)

					if (pCure == nil) then
						player:sendSystemMessage("Error: Cure not found in inventory.")
						return 0
					end

					SceneObject(pCure):destroyObjectFromWorld()
					SceneObject(pCure):destroyObjectFromDatabase()

					if (SceneObject(pInventory):hasFullContainerObjects() == true) then
						player:sendSystemMessage("@error_message:inv_full")
						return 0
					else
						local pBattery = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true)
						if (pBattery == nil) then
							pBattery = giveItem(pInventory,"object/tangible/dungeon/death_watch_bunker/drill_battery.iff", -1)
							if (pBattery == nil) then
								player:sendSystemMessage("Error: Unable to generate item.")
								return 0
							end
						end
					end

					player:setScreenPlayState(2, "death_watch_haldo")
				else
					player:sendSystemMessage("Error: Unable to find player inventory.")
				end
			end
		end

		return conversationScreen
	end)
end