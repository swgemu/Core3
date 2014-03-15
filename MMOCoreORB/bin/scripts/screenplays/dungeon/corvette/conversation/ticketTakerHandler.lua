TicketTakerConversationHandler = Object:new {
}

function TicketTakerConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	
	local screenID = screen:getScreenID()
	
	local player = LuaCreatureObject(pConversingPlayer)
	local playerInv = LuaSceneObject(pConversingPlayer)
	local faction = "imperial"
	
	if (screenID == "imperial_pilot_board") then
	
		if (CorvetteScreenPlay:findAvailableDungeon(faction) == false) then
			player:sendSystemMessage("@dungeon/space_dungeon:no_room_remaining")
			return pConversationScreen
		end
				
		local pInv = playerInv:getSlottedObject("inventory")
		
		if (pInv ~= nil) then
			local pItem = getContainerObjectByTemplate(pInv, "object/tangible/travel/travel_ticket/dungeon_ticket.iff", false)
				
			if (pItem ~= nil) then
				if (player:isGrouped()) then
					local gSize = player:getGroupSize()
					
					for i = 0, gSize do
						local groupMember = player:getGroupMember(i)
						if (groupMember ~= nil) then
							if (groupMember ~= pConversingPlayer) then
								local groupMemberC = LuaCreatureObject(groupMember)
								if (groupMemberC:isImperial()) then
									-- SUI popup for non-instance leader.
									local suiManager = LuaSuiManager()
									local suiMessage = "Do you wish to travel to the space dungeon?"
									suiManager:sendMessageBox(groupMember, groupMember, "@dungeon/space_dungeon:request_travel", suiMessage, "@ok", "CorvetteScreenPlay", "travelToDungeon")
								end
							else

							-- Handle instance functions for instance leader.
							-- Destroy ticket.
							local ticket = LuaSceneObject(pItem)
							ticket:destroyObjectFromWorld()
							ticket:destroyObjectFromDatabase()
				
							-- Here we go!
							player:sendSystemMessage("@dungeon/space_dungeon:validating_ticket")
							playerInv:switchZone("dungeon1", -20, 0, 0, 4336197)
							CorvetteScreenPlay:startInstance(faction, pConversingPlayer)
							end
						end
					end
				else
				
					-- Destroy ticket.
					local ticket = LuaSceneObject(pItem)
					ticket:destroyObjectFromWorld()
					ticket:destroyObjectFromDatabase()
				
					-- Here we go!
					player:sendSystemMessage("@dungeon/space_dungeon:validating_ticket")
					playerInv:switchZone("dungeon1", -20, 0, 0, 4336197)
					CorvetteMain:startInstance(faction, pConversingPlayer)
				
				end
			end
		end
	end
	
	return pConversationScreen
end

function TicketTakerConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaSceneObject(pPlayer)

	if (conversingPlayer:isPlayerCreature()) then
		local playerObject = LuaCreatureObject(pPlayer)
		local playerInv = LuaSceneObject(pPlayer)
		local pInv = playerInv:getSlottedObject("inventory")

			if (pInv ~= nil) then
				local pItem = getContainerObjectByTemplate(pInv, "object/tangible/travel/travel_ticket/dungeon_ticket.iff", false)
				if (pItem ~= nil) then
				-- They have a ticket... Let's see what type it's for.
					local state = playerObject:getScreenPlayState("CorvetteTypeScreenPlay")
			
					if (state > 0 and state < 6) then -- They have a valid ticket. Group checks!

						if (playerObject:isGrouped()) then
							local gSize = playerObject:getGroupSize()
							
							if (gSize > 10) then
								return convoTemplate:getScreen("imperial_pilot_too_many")
							end
							
							for i = 0, gSize do
								local groupMember = playerObject:getGroupMember(i)
								if (groupMember ~= nil) then
									local groupMemberC = LuaCreatureObject(groupMember)
							    		if (groupMemberC:isImperial() == false) then
										return convoTemplate:getScreen("imperial_pilot_too_many_and_not_imperial")
									else 
										return convoTemplate:getScreen("imperial_pilot_explain_mission")
									end
								end
							end
						else
							return convoTemplate:getScreen("imperial_pilot_explain_mission")
						end
					end
				end
			end

			-- Don't know you!
		return convoTemplate:getScreen("imperial_pilot_start")
	end
end

function TicketTakerConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
