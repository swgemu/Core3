local ObjectManager = require("managers.object.object_manager")

deathWatchMedicalDroidConvoHandler = {  }

function deathWatchMedicalDroidConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function deathWatchMedicalDroidConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("intro")
end

function deathWatchMedicalDroidConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "intro") then
			if (player:hasScreenPlayState(2, "death_watch_foreman_stage") and not player:hasScreenPlayState(4, "death_watch_foreman_stage")) then
				local pInventory = player:getSlottedObject("inventory")
				if (pInventory ~= nil) then
					if (SceneObject(pInventory):isContainerFullRecursive()) then
						clonedConversation:addOption("@conversation/death_watch_medical_droid:s_ab36bcfc", "inventory_full")
					else
						clonedConversation:addOption("@conversation/death_watch_medical_droid:s_ab36bcfc", "cure_issued")
					end
				end
			else
				player:sendSystemMessage("@dungeon/death_watch:not_authorized")
			end
			clonedConversation:addOption("@conversation/death_watch_medical_droid:s_82d3782a", "please_return")
		elseif (screenID == "cure_issued") then
				local pInventory = player:getSlottedObject("inventory")
				
				if (pInventory ~= nil) then
					if (getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", true) == nil) then
						local pCure = giveItem(pInventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", -1)
				
						if (pCure == nil) then
							player:sendSystemMessage("Error: Unable to generate item.")
						else
							player:sendSystemMessage("@system_msg:give_item_success")
						end
				end
			end
		end

		return conversationScreen
	end)
end