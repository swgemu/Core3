ImperialDestroyConversationHandler = Object:new {
}

function ImperialDestroyConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	
	local screenID = screen:getScreenID()
	
	local player = LuaCreatureObject(pConversingPlayer)
	local playerInv = LuaSceneObject(pConversingPlayer)
	
	if (screenID == "imperial_destroy_9") then
		local pInv = playerInv:getSlottedObject("inventory")
			
		if (pInv ~= nil) then
			local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff", false)	
			local pItem2 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff", false)
			local pItem3 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_intel.iff", false)
				
			if (pItem1 ~= nil) or (pItem2 ~= nil) or (pItem3 ~= nil) then
				screen:addOption("@conversation/corvette_velso_imperial_destroy:s_6e1e63ff", "imperial_destroy_look")
			end
		end
	elseif (screenID == "imperial_destroy_look") then
		local pInv = playerInv:getSlottedObject("inventory")
			
		if (pInv ~= nil) then
			local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff", false)	
				
			if (pItem1 ~= nil) then
				screen:addOption("@conversation/corvette_velso_imperial_destroy:s_5b38e8f5", "imperial_destroy_not_it_1")
			end

			local pItem2 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff", false)	
				
			if (pItem2 ~= nil) then
				screen:addOption("@conversation/corvette_velso_imperial_destroy:s_88da44a4", "imperial_destroy_not_it_2")
			end

			local pItem3 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_intel.iff", false)	
				
			if (pItem3 ~= nil) then
				screen:addOption("@conversation/corvette_velso_imperial_destroy:s_5dc3f73a", "imperial_destroy_found_it")
			end
		end
	elseif (screenID == "imperial_destroy_found_it") then
		player:setScreenPlayState(CorvetteScreenPlay.states.stages.stageTwo, "CorvetteScreenPlay")
		player:setScreenPlayState(CorvetteScreenPlay.states.types.ImperialDestroy, "CorvetteTypeScreenPlay")
		CorvetteScreenPlay:giveAuthorizationForm(pConversingPlayer)
	elseif (screenID == "imperial_destroy_not_it_1") then
			local pInv = playerInv:getSlottedObject("inventory")
				if (pInv ~= nil) then
					local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff", false)	
				
					if (pItem1 ~= nil) then
						local item1 = LuaSceneObject(pItem1)
						item1:destroyObjectFromWorld()
						item1:destroyObjectFromDatabase()
						
						local pPlayerObject = player:getSlottedObject("ghost")
						local playerObject = LuaPlayerObject(pPlayerObject)
	
						playerObject:increaseFactionStanding("imperial", 100)
					end
				end
	elseif (screenID == "imperial_destroy_not_it_2") then
			local pInv = playerInv:getSlottedObject("inventory")
				if (pInv ~= nil) then
					local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff", false)	
				
					if (pItem1 ~= nil) then
						local item1 = LuaSceneObject(pItem1)
						item1:destroyObjectFromWorld()
						item1:destroyObjectFromDatabase()
						
						local pPlayerObject = player:getSlottedObject("ghost")
						local playerObject = LuaPlayerObject(pPlayerObject)
	
						playerObject:increaseFactionStanding("imperial", 100)
					end
				end
	elseif (screenID == "imperial_destroy_7") then
		player:setScreenPlayState(CorvetteScreenPlay.states.stages.stageOne, "CorvetteScreenPlay")
	end
	
	return pConversationScreen
end

function ImperialDestroyConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaSceneObject(pPlayer)

	if (conversingPlayer:isPlayerCreature()) then
		local playerObject = LuaCreatureObject(pPlayer)
		local faction = playerObject:getFaction()

			if (playerObject:hasScreenPlayState(CorvetteScreenPlay.states.stages.stageTwo, "CorvetteScreenPlay") == 1) then
				return convoTemplate:getScreen("imperial_destroy_13")
			elseif (playerObject:hasScreenPlayState(CorvetteScreenPlay.states.stages.stageOne, "CorvetteScreenPlay") == 1) then
				return convoTemplate:getScreen("imperial_destroy_9")
			-- If they are Imperial...
			elseif (faction == 3679112276) then
				return convoTemplate:getScreen("imperial_destroy_start")
			end

		return convoTemplate:getScreen("imperial_destroy_neutral")
	end
end

function ImperialDestroyConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local player = LuaCreatureObject(pPlayer)
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
end
