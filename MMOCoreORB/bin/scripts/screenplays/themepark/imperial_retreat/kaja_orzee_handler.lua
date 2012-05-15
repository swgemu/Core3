imperial_retreat_kaja_orzee_screenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	loc = {
		kaja = {x= 2407.8, z = 292.1, y = -3940.3},
		moff = {x= 2252.9, z = 107.9, y = -4670}
	},
	
	states = {
		quest1 = {started = 1, escorting = 2, completed = 8},
		quest2 = {started = 16, defeated = 32, completed = 64}
	}
}

registerScreenPlay("imperial_retreat_kaja_orzee_screenplay", true)


--------------------------------------
--   Initialize screenplay           -
--------------------------------------

function imperial_retreat_kaja_orzee_screenplay:start()
	self:spawnActiveAreas()
	self:spawnMobiles()
end

function imperial_retreat_kaja_orzee_screenplay:spawnActiveAreas()
	local pActiveArea1 = spawnSceneObject("naboo", "object/active_area.iff", self.loc.moff.x, self.loc.moff.z, self.loc.moff.y, 0,0,0,0,0)
	
	if (pActiveArea1 ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea1)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "imperial_retreat_kaja_orzee_screenplay", "notifyEnteredArea1", pActiveArea1)	
	end
end

function imperial_retreat_kaja_orzee_screenplay:spawnMobiles()
	spawnMobile("naboo", "kaja_orzee", 0,-3,0.2,-12.4,92,1418872)
end

--------------------------------------
--   Common Functions	             -
--------------------------------------

function imperial_retreat_kaja_orzee_screenplay:hasState(player, state)
	if (player == nil) then
		return false
	end
	
	local val = player:hasScreenPlayState(state, "imperial_retreat_kaja_orzee")
	
	if (val == 1) then
		return true
	end
	
	return false
end

function imperial_retreat_kaja_orzee_screenplay:setState(creatureObject, state)
	creatureObject:setScreenPlayState(state, "imperial_retreat_kaja_orzee")
end

function imperial_retreat_kaja_orzee_screenplay:hasSpawned(objectID, key)
	local val = readData(objectID .. ":imperial_retreat_kaja_orzee_screenplay:spawned:" .. key)
	
	if (val == 1) then
		return true
	end
	
	return false
end

function imperial_retreat_kaja_orzee_screenplay:setSpawned(objectID, key)
	writeData(objectID .. ":imperial_retreat_kaja_orzee_screenplay:spawned:" .. key)
end

function imperial_retreat_kaja_orzee_screenplay:deleteSpawned(objectID, key)
	deleteData(objectID .. ":imperial_retreat_kaja_orzee_screenplay:spawned:" .. key)
end

function imperial_retreat_kaja_orzee_screenplay:writeObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end
	
	return readData(objectID .. ":imperial_retreat_kaja_orzee_screenplay:" .. key)
end

function imperial_retreat_kaja_orzee_screenplay:deleteObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end
	
	deleteData(objectID .. ":imperial_retreat_kaja_orzee_screenplay:" .. key)
end

function imperial_retreat_kaja_orzee_screenplay:readObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end
	
	readData(objectID .. ":imperial_retreat_kaja_orzee_screenplay:" .. key)
end

--------------------------------------
--	 ActiveArea Observers			--
--------------------------------------

function imperial_retreat_kaja_orzee_screenplay:notifyEnteredArea1(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		
		if (self:hasState(player, self.states.quest1.started)) and (not self:hasState(player, self.states.quest1.escorting)) then
			if (not self:hasSpawned(objectID, "moff")) then
				self:setSpawned(objectID, "moff")
				
				local pMoff = spawnMobile("naboo", "governor_grayed_wintozzen", 0, imperial_retreat_kaja_orzee_screenplay.loc.moff.x, imperial_retreat_kaja_orzee_screenplay.loc.moff.z, imperial_retreat_kaja_orzee_screenplay.loc.moff.y, 105, 0)
				local moff = LuaSceneObject(pMoff)
				
				self:writeObjectData(objectID, "moffID", moff:getObjectID())
				self:writeObjectData(moff:getObjectID(), "questOwnerID", objectID)
				
				createObserver(STOPCONVERSATION, "imperial_retreat_kaja_orzee_screenplay", "notifyStartEscort1", pMoff)
				
			end
		end
		
	end
end

--------------------------------------
--	 		Observers				--
--------------------------------------

function imperial_retreat_kaja_orzee_screenplay:notifyStartEscort1(pMoff, pPlayer)
	local moffCreature = LuaCreatureObject(pMoff)
	local moffAi = LuaAiAgent(pMoff)
	local player = LuaCreatureObject(pPlayer)
	
	local distance = moffCreature:getDistanceTo(pPlayer)
	
	if (distance == 0 or distance > 32) then
		return 0
	end
	
	moffAi:setFollowObject(pPlayer)
	playerObject:addWaypoint("naboo", "@theme_park_imperial/kaja_orzee:return_waypoint_name_1", "@theme_park_imperial/kaja_orzee:return_waypoint_description_1", imperial_retreat_kaja_orzee_screenplay.loc.kaja.x, imperial_retreat_kaja_orzee_screenplay.loc.kaja.y, WAYPOINTBLUE, true, true)
	self:setState(player, self.states.quest1.escorting)
	
	return 1
end


--------------------------------------
--   Data Cleanup Functions          -
--------------------------------------

function imperial_retreat_kaja_orzee_screenplay:despawnQuest1(objectID)
	local moffID = self:readObjectData(objectID, "moffID")

	local pMoff = getCreatureObject(moffID)
	
	if (pMoff ~= nill) then
		local moff = LuaSceneObject(pMoff)
		moff:destroyObjectFromWorld()
	end
	
	self:deleteObjectData(objectID, "moffID")
	self:deleteObjectData(moffID, "questOwnerID")
	self:deleteSpawned(objectID, "moff")
end

function imperial_retreat_kaja_orzee_screenplay:despawnQuest2(objectID)
	
end


--------------------------------------
--   Rewards / Completions           -
--------------------------------------

function imperial_retreat_kaja_orzee_screenplay:rewardQuest1(player, playerObject)
	self:despawnQuest1(player:getObjectID()) -- Cleanup
	
	player:addCashCredits(75, true)
	playerObject:increaseFactionStanding("imperial", 10)
	
	-- Set States
	self:setState(player, imperial_retreat_kaja_orzee_screenplay.states.quest1.completed)
end

function imperial_retreat_kaja_orzee_screenplay:rewardQuest2(player, playerObject)
	self:despawnQuest2(player:getObjectID()) -- Cleanup
	
	player:addCashCredits(150, true)
	playerObject:increaseFactionStanding("imperial", 10)
	
	-- Set States
	self:setState(player, imperial_retreat_kaja_orzee_screenplay.states.quest2.completed)
end



----------------------------------------------------
--   imperial_retreat_kaja_orzee Convo handler     -
----------------------------------------------------

imperial_retreat_kaja_orzee_handler = Object:new {
}

function imperial_retreat_kaja_orzee_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	
	local screenID = screen:getScreenID()
	
	local player = LuaCreatureObject(conversingPlayer)
	local playerObjectPointer = player:getPlayerObject()
	
	if (screenID == "accept_2_1") then -- Accepted Quest 1
		self:beginQuest1(player)
	elseif (screenID == "accept_1_2") then -- Accepted Quest 2
		self:beginQuest2(player)
	elseif (screenID == "npc_reset") then -- RESET
		-- TODO: Set this so if resets the current quest the player is on.
		player:removeScreenPlayState(imperial_retreat_kaja_orzee_screenplay.states.quest1.started, "imperial_retreat_kaja_orzee")
	end
	
	return conversationScreen

end

function imperial_retreat_kaja_orzee_handler:beginQuest1(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	-- waypoint and states
	playerObject:addWaypoint("naboo", "@theme_park_imperial/kaja_orzee:waypoint_name_1", "@theme_park_imperial/kaja_orzee:waypoint_description_1", imperial_retreat_kaja_orzee_screenplay.loc.moff.x, imperial_retreat_kaja_orzee_screenplay.loc.moff.y, WAYPOINTBLUE, true, true)
	imperial_retreat_kaja_orzee_screenplay:setState(player, imperial_retreat_kaja_orzee_screenplay.states.quest1.started)

end

function imperial_retreat_kaja_orzee_handler:beginQuest2(player)
	
end

function imperial_retreat_kaja_orzee_handler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaCreatureObject(pPlayer)
	local faction = conversingPlayer:getFaction()
	local pPlayerObject = conversingPlayer:getPlayerObject()
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")
	local inventory = LuaSceneObject(pInventory)
	
	if (pPlayerObject == nil) then 
		return nil
	end
	
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	if (conversingPlayer:hasScreenPlayState(imperial_retreat_kaja_orzee_screenplay.states.quest1.completed, "imperial_retreat_kaja_orzee") == 1) then
		return convoTemplate:getScreen("npc_1_2")
	
	elseif (conversingPlayer:hasScreenPlayState(imperial_retreat_kaja_orzee_screenplay.states.quest1.escorting, "imperial_retreat_kaja_orzee") == 1) then
		imperial_retreat_kaja_orzee_screenplay:rewardQuest1(conversingPlayer, playerObject)
		
		return convoTemplate:getScreen("npc_reward_1")	
		
	elseif (conversingPlayer:hasScreenPlayState(imperial_retreat_kaja_orzee_screenplay.states.quest1.started, "imperial_retreat_kaja_orzee") == 1) then
		return convoTemplate:getScreen("npc_backtowork")
		
	end
	
	-- Imperial Check
	if (faction ~= 3679112276) then
		return convoTemplate:getScreen("npc_dontknowyou_1")
	end
	
	return convoTemplate:getScreen("npc_1_1") -- 1st quest option
end

function imperial_retreat_kaja_orzee_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
