FACTIONIMPERIAL = 0xDB4ACC54
FACTIONREBEL = 0x16148850


TicketGiverConversationHandler = Object:new {
}

function TicketGiverConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	
	local screenID = screen:getScreenID()
	
	local player = LuaCreatureObject(pConversingPlayer)
	local playerInv = LuaSceneObject(pConversingPlayer)
	local npc = LuaCreatureObject(pConversingNPC)

	stageOneResponses = { "imperial_destroy_7", } -- Starting the quest.
	lookInInventoryResponses = { "imperial_destroy_9" , } -- Look in the inventory.
	lookCorrectReponses = { "imperial_destroy_found_it", } -- Correct item.
	lookIncorrectResponses = { "imperial_destroy_not_it_1" , "imperial_destroy_not_it_2"} -- Incorrect item.
	stageTwoResponses = { "imperial_destroy_12", "imperial_destroy_13" } -- Received Ticket.
	stageThreeResponses = {} -- Mission complete.
	
	if (self:existsInTable(stageTwoResponses, screenID)) then
		local pInv = playerInv:getSlottedObject("inventory")
			
			if (pInv ~= nil) then
				if (npc:getFaction() == FACTIONIMPERIAL) then
					if (string.find(screenString, "velso") ~= nil) then
						local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff", false)	
						local pItem2 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff", false)
						local pItem3 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_intel.iff", false)
					elseif (string.find(screenString, "sabol") ~= nil) then
						local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler01.iff", false)	
						local pItem2 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler02.iff", false)
						local pItem3 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_intel.iff", false)
					elseif (string.find(screenString, "darkstone") ~= nil) then
					end
			elseif (npc:getFaction() == FACTIONREBEL) then
			elseif (npc:isNeutral()) then
			end
				
			if (pItem1 ~= nil) or (pItem2 ~= nil) or (pItem3 ~= nil) then
				if (npc:getFaction() == FACTIONIMPERIAL) then
					if (string.find(screenString, "velso") ~= nil) then
						pConversationScreen = screen:cloneScreen()
						local clonedScreen = LuaConversationScreen(pConversationScreen)
						clonedScreen:addOption("@conversation/corvette_velso_imperial_destroy:s_6e1e63ff", "imperial_destroy_look")
					elseif (string.find(screenString, "sabol") ~= nil) then
					elseif (string.find(screenString, "darkstone") ~= nil) then
					end
				elseif (npc:getFaction() == FACTIONREBEL) then
				elseif (npc:isNeutral()) then
				end
			end
		end
	elseif (self:existsInTable(lookInInventoryResponses, screenID)) then
		local pInv = playerInv:getSlottedObject("inventory")
			
			if (pInv ~= nil) then
				if (npc:getFaction() == FACTIONIMPERIAL) then
					if (string.find(screenString, "velso") ~= nil)
						local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff", false)	
						local pItem2 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff", false)
						local pItem3 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_intel.iff", false)
					elseif (string.find(screenString, "sabol") ~= nil)
						local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler01.iff", false)	
						local pItem2 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler02.iff", false)
						local pItem3 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_intel.iff", false)
					elseif (string.find(screenString, "darkstone") ~= nil)
					end
			elseif (npc:getFaction() == FACTIONREBEL) then
			elseif (npc:isNeutral()) then
			end	
				
			if (pItem1 ~= nil) then
				pConversationScreen = screen:cloneScreen()
				local clonedScreen = LuaConversationScreen(pConversationScreen)
				local screenString = clonedScreen:getDialogTextStringId()

				if (npc:getFaction() == FACTIONIMPERIAL) then
					if (string.find(screenString, "velso") ~= nil)
						clonedScreen:addOption("@conversation/corvette_velso_imperial_destroy:s_5b38e8f5", "imperial_destroy_not_it_1")
					elseif (string.find(screenString, "sabol") ~= nil)
						clonedScreen:addOption("@conversation/corvette_sabol_imperial1:s_3565de4e", "imperial_destroy_not_it_1")
					elseif (string.find(screenString, "darkstone") ~= nil)
					end
				elseif (npc:getFaction() == FACTIONREBEL) then
				elseif (npc:isNeutral()) then
				end
				
			elseif (pItem2 ~= nil) then
				pConversationScreen = screen:cloneScreen()
				local clonedScreen = LuaConversationScreen(pConversationScreen)

				local screenString = clonedScreen:getDialogTextStringId()

				if (npc:getFaction() == FACTIONIMPERIAL) then
					if (string.find(screenString, "velso") ~= nil)
						clonedScreen:addOption("@conversation/corvette_velso_imperial_destroy:s_88da44a4", "imperial_destroy_not_it_2")
					elseif (string.find(screenString, "sabol") ~= nil)
						clonedScreen:addOption("@conversation/corvette_sabol_imperial1:s_56ede5d3", "imperial_destroy_not_it_2")
					elseif (string.find(screenString, "darkstone") ~= nil)
					end
				elseif (npc:getFaction() == FACTIONREBEL) then
				elseif (npc:isNeutral()) then
				end
				
			elseif (pItem3 ~= nil) then
				pConversationScreen = screen:cloneScreen()
				local clonedScreen = LuaConversationScreen(pConversationScreen)

				local screenString = clonedScreen:getDialogTextStringId()

				if (npc:getFaction() == FACTIONIMPERIAL) then
					if (string.find(screenString, "velso") ~= nil)
						clonedScreen:addOption("@conversation/corvette_velso_imperial_destroy:s_5dc3f73a", "imperial_destroy_found_it")
					elseif (string.find(screenString, "sabol") ~= nil)
						
					elseif (string.find(screenString, "darkstone") ~= nil)
					end
				elseif (npc:getFaction() == FACTIONREBEL) then
				elseif (npc:isNeutral()) then
				end
				
			end
		end
	elseif (self:existsInTable(lookCorrectResponses, screenID)) then
		player:setScreenPlayState(CorvetteMain.stages.stageTwo, "CorvetteScreenPlay")

		local screenString = screen:getDialogTextStringId()

		if (npc:getFaction() == FACTIONIMPERIAL) then
			if (string.find(screenString, "velso") ~= nil)
				player:setScreenPlayState(1, "CorvetteMissionType")
			elseif (string.find(screenString, "sabol") ~= nil)
				player:setScreenPlayState(2, "CorvetteMissionType")		
			elseif (string.find(screenString, "darkstone") ~= nil)
				player:setScreenPlayState(4, "CorvetteMissionType")	
			end
		CorvetteMain:giveAuthorizationForm(pConversingPlayer, "imperial")
		elseif (npc:getFaction() == FACTIONREBEL) then
		elseif (npc:isNeutral()) then
		end
		
	elseif (self:existsInTable(lookIncorrectResponses, screenID)) then
			local pInv = playerInv:getSlottedObject("inventory")
				if (pInv ~= nil) then
					if (npc:getFaction() == FACTIONIMPERIAL) then
						if (string.find(screenString, "velso") ~= nil)
							local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff", false)	
							local pItem2 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff", false)
							
							if (pItem1 ~= nil) then
								local item1 = LuaSceneObject(pItem1)
								item1:destroyObjectFromWorld()
								item1:destroyObjectFromDatabase()
							end

							if (pItem2 ~= nil) then
								local item2 = LuaSceneObject(pItem1)
								item2:destroyObjectFromWorld()
								item1:destroyObjectFromDatabase()
							end
							local pPlayerObject = player:getSlottedObject("ghost")
							local playerObject = LuaPlayerObject(pPlayerObject)
							playerObject:increaseFactionStanding("imperial", 100)
							playerObject:increaseFactionStanding("rebel", 100)
							playerObject:increaseFactionStanding("jabba", 100)
					elseif (string.find(screenString, "sabol") ~= nil)
						local pItem1 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler01.iff", false)	
						local pItem2 = getContainerObjectByTemplate(pInv, "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler02.iff", false)
							
							if (pItem1 ~= nil) then
								local item1 = LuaSceneObject(pItem1)
								item1:destroyObjectFromWorld()
								item1:destroyObjectFromDatabase()
							end

							if (pItem2 ~= nil) then
								local item2 = LuaSceneObject(pItem1)
								item2:destroyObjectFromWorld()
								item1:destroyObjectFromDatabase()
							end
					elseif (string.find(screenString, "darkstone") ~= nil)
					end

					local pPlayerObject = player:getSlottedObject("ghost")
					local playerObject = LuaPlayerObject(pPlayerObject)
					playerObject:increaseFactionStanding("imperial", 100)
				elseif (npc:getFaction() == FACTIONREBEL) then
				elseif (npc:isNeutral()) then
					end
				end
	elseif (self:existsInTable(stageOneResponses, screenID)) then
		player:setScreenPlayState(CorvetteScreenPlay.stages.stageOne, "CorvetteMain")
	elseif (self:existsInTable(stageThreeResponses, screenID)) then
		player:setScreenPlayState(CorvetteScreenPlay.stages.stageOne, "CorvetteMain")
	end
	
	return pConversationScreen
end

function TicketGiverConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaSceneObject(pPlayer)

	if (conversingPlayer:isPlayerCreature()) then
		local playerObject = LuaCreatureObject(pPlayer)
		local faction = playerObject:getFaction()
		local npc = LuaCreatureObject(pNpc)

		imperialScreens = {"imperial_destroy_13", "imperial_destroy_9", "imperial_destroy_start", "imperial_destroy_neutral"}
		neutralScreens = {}
		rebelScreens = {}

			if (playerObject:hasScreenPlayState(CorvetteMain.stages.stageTwo, "CorvetteMain") == 1) then
				if (npc:getFaction() == FACTIONIMPERIAL) then
					return convoTemplate:getScreen(imperialScreens[1])
				end
			elseif (playerObject:hasScreenPlayState(CorvetteMain.stages.stageOne, "CorvetteMain") == 1) then
				if (npc:getFaction() == FACTIONIMPERIAL) then
					return convoTemplate:getScreen(imperialScreens[2])
				end
			-- If they are the right faction...
			elseif (faction == npc:getFaction()) then
				if (npc:getFaction() == FACTIONIMPERIAL) then
					return convoTemplate:getScreen(imperialScreens[3])
				end
			end

		-- Not the faction.
		if (npc:getFaction() == FACTIONIMPERIAL) then
			return convoTemplate:getScreen(imperialScreens[4])
		end
	end
end

function TicketGiverConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function TicketGiverConversationHandler:existsInTable(table, item)
	for key, value in pairs(table) do
		if value == item then return true end
	end
	return false
end
