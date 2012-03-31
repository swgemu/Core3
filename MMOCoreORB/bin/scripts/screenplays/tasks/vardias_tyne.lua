vardias_tyne_screenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	loc = {
		rhalia = {x = -351, z = 6, y = -5342},
		chonar = {x = 244, z = 7, y = -5611}
	},
	
	states = {
		quest1 = {started = 1, defeated = 2, completed = 4},
		quest2 = {started = 8, madepeace = 16, completed = 32}
	}
	
	
}

registerScreenPlay("vardias_tyne_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function vardias_tyne_screenplay:start()
	self:spawnActiveAreas()
	self:spawnMobiles()
end

function vardias_tyne_screenplay:spawnActiveAreas()
	local pActiveArea1 = spawnSceneObject("tatooine", "object/active_area.iff", self.loc.rhalia.x, self.loc.rhalia.z, self.loc.rhalia.y, 0, 0, 0, 0, 0)
	local pActiveArea2 = spawnSceneObject("tatooine", "object/active_area.iff", self.loc.chonar.x, self.loc.chonar.z, self.loc.chonar.y, 0, 0, 0, 0, 0)
	
	if (pActiveArea1 ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea1)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "vardias_tyne_screenplay", "notifyEnteredArea1", pActiveArea1)
	end
	
	if (pActiveArea2 ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea2)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "vardias_tyne_screenplay", "notifyEnteredArea2", pActiveArea2)
	end
	
end

function vardias_tyne_screenplay:spawnMobiles()
	 if (not isZoneEnabled("tatooine")) then
 	  	return 0
 	 end
	local pVardias = spawnMobile("tatooine", "vardias_tyne", 1, 104, 0.1, -5382, -96, 0)
end

--------------------------------------
--   Common functions                -
--------------------------------------
function vardias_tyne_screenplay:hasState(player, state)
	if (player == nil) then
		return false
	end
	
	local val = player:hasScreenPlayState(state, "vardias_tyne")
	
	if (val == 1) then
		return true
	end
	
	return false
end

function vardias_tyne_screenplay:hasSpawned(objectID, key)
	local val = readData(objectID .. ":vardias_tyne:spawned:" .. key)
	
	if (val == 1) then
		return true
	end
	
	return false
end

function vardias_tyne_screenplay:setSpawned(objectID, key)
	writeData(objectID .. ":vardias_tyne:spawned:" .. key, 1)
end

function vardias_tyne_screenplay:deleteSpawnedSetting(objectID, key)
	deleteData(objectID .. ":vardias_tyne:spawned:" .. key)
end

function vardias_tyne_screenplay:writeObjectData(objectID, key, value)
	if (objectID == nil) then
		return 0
	end
	
	writeData(objectID .. ":vardias_tyne:" .. key, value)
end

function vardias_tyne_screenplay:readObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end
	
	return readData(objectID .. ":vardias_tyne:" .. key)
end

function vardias_tyne_screenplay:deleteObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end
	
	deleteData(objectID .. ":vardias_tyne:" .. key)
end

function vardias_tyne_screenplay:setState(creatureObject, state)
	creatureObject:setScreenPlayState(state, "vardias_tyne")
end

function vardias_tyne_screenplay:removeState(creatureObject, state)
	creatureObject:removeScreenPlayState(state, "vardias_tyne")
end
--------------------------------------
--   ActiveArea observers            -
--------------------------------------
function vardias_tyne_screenplay:notifyEnteredArea1(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		
		if (self:hasState(player, self.states.quest1.started)) then
			if (not self:hasSpawned(objectID, "rhalia")) then
				self:setSpawned(objectID, "rhalia")
				
				local pRhalia = spawnMobile("tatooine", "bounty_hunter", 0, self.loc.rhalia.x, self.loc.rhalia.z, self.loc.rhalia.y, 0, 0)
				local rhalia = LuaSceneObject(pRhalia)
				local rhaliaCreo = LuaCreatureObject(pRhalia)
				rhalia:setCustomObjectName("Rhalia Jinsari")
				rhaliaCreo:setPvpStatusBitmask(1)	
								
				self:writeObjectData(objectID, "rhalia", rhalia:getObjectID())
				self:writeObjectData(rhalia:getObjectID(), "questOwnerID", objectID)
								
				
				createObserver(OBJECTDESTRUCTION, "vardias_tyne_screenplay", "notifyDefeatedRhalia", pRhalia)
				createObserver(OBJECTINRANGEMOVED, "vardias_tyne_screenplay", "notifyRhaliaBark", pRhalia)
				
			end
		end
	end
	
	return 0
end

function vardias_tyne_screenplay:notifyEnteredArea2(pActiveArea, pMovingObject)

	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		
		if (self:hasState(player, self.states.quest2.started)) then
			if (not self:hasSpawned(objectID, "chonar")) then
				self:setSpawned(objectID, "chonar")
				
				local pChonar = spawnMobile("tatooine", "dim_u_monk", 0, self.loc.chonar.x, self.loc.chonar.z, self.loc.chonar.y, 0, 0)
				local chonar = LuaSceneObject(pChonar)
				chonar:setCustomObjectName("Brother Chonar")
				local chonarCreo = LuaCreatureObject(pChonar)
				chonarCreo:setPvpStatusBitmask(0)
				chonar:setContainerComponent("chonar_container_component")				
							
				self:writeObjectData(objectID, "chonar", chonar:getObjectID())
				self:writeObjectData(chonar:getObjectID(), "questOwnerID", objectID)							
				
				createObserver(OBJECTINRANGEMOVED, "vardias_tyne_screenplay", "notifyChonarBark", pChonar)
				
			end
		end
	end
	
	
end

--------------------------------------
--   Destruction Observers           -
--------------------------------------
function vardias_tyne_screenplay:notifyDefeatedRhalia(pVictim, pAttacker)
	local victim = LuaCreatureObject(pVictim)
	local ownerID = self:readObjectData(victim:getObjectID(), "questOwnerID")
	local pOwner = getCreatureObject(ownerID)
	
	if (pOwner == nil) then
		return 0;
	end
			
	local player = LuaCreatureObject(pOwner)
	local pointerPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pointerPlayerObject)
	vardias_tyne_screenplay:setState(player, vardias_tyne_screenplay.states.quest1.defeated)
	local pVardiasWaypoint = playerObject:addWaypoint("tatooine", "Vardias Tyne", "Vardias Tyne", 104, -5382,WAYPOINTBLUE, true, true)
	player:sendSystemMessage("Return to Vardias Tyne")
	self:deleteObjectData(objectID, "rhalia")
	self:deleteObjectData(victim:getObjectID(), "questOwnerID")
	
	return 1
end



--------------------------------------
--   Movement Observers              -
--------------------------------------
function vardias_tyne_screenplay:notifyRhaliaBark(pRhalia, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local rhalia = LuaCreatureObject(pRhalia)
		local distance = rhalia:getDistanceTo(pMovingObject)
		
		if (distance == 0 or distance > 16) then
			return 0
		end
		
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
			
		if (self:hasState(player, self.states.quest1.started)) then
			if (self:hasSpawned(objectID, "rhalia")) then
				if (self:readObjectData(objectID, "rhalia_spoken") ~= 1) then
					spatialChat(pRhalia, "@static_npc/tatooine/vardias_tyne:npc_breech_1") --I'm not being paid to capture you, but I won't let you stand in my way.
					self:writeObjectData(objectID, "rhalia_spoken", 1)
				
					return 1
				end
			end
		end
	end
	
	return 0
end

function vardias_tyne_screenplay:notifyChonarBark(pChonar, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local chonar = LuaCreatureObject(pChonar)
		local distance = chonar:getDistanceTo(pMovingObject)
		
		if (distance == 0 or distance > 16) then
			return 0
		end
		
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
			
		if (self:hasState(player, self.states.quest2.started)) then
			if (self:hasSpawned(objectID, "chonar")) then
				if (self:readObjectData(objectID, "chonar_spoken") ~= 1) then
					spatialChat(pChonar, "@static_npc/tatooine/vardias_tyne:npc_breech_2") --I hope this will be a worthwhile communication between us
					self:writeObjectData(objectID, "chonar_spoken", 1)
				
					return 1
				end
			end
		end
	end
	
	return 0
end

--------------------------------------
--   Data cleanup functions          -
--------------------------------------
function vardias_tyne_screenplay:despawnQuest1(objectID)
	local rhaliaID = self:readObjectData(objectID, "rhalia")
		
	local pRhalia = getCreatureObject(rhaliaID)
		
	if (pRhalia ~= nil) then
		local rhalia = LuaSceneObject(pRhalia)
		rhalia:destroyObjectFromWorld()
	end
	
	self:deleteObjectData(objectID, "rhalia")
	self:deleteObjectData(objectID, "rhalia_spoken")
	self:deleteSpawnedSetting(objectID, "rhalia")
	
	return 0
	
end

function vardias_tyne_screenplay:despawnQuest2(pPlayerCreo)
	
	playerCreo = LuaCreatureObject(pPlayerCreo)
	
	playerObjectID = playerCreo:getObjectID()
	local chonarID = self:readObjectData(playerObjectID, "chonar")
	
	local pChonar = getCreatureObject(chonarID)
		
	if (pChonar ~= nil) then
		local chonar = LuaSceneObject(pChonar)
		chonar:destroyObjectFromWorld()
	end
	
	self:deleteObjectData(playerObjectID, "chonar")
	self:deleteObjectData(playerObjectID, "chonar_spoken")
	self:deleteSpawnedSetting(playerObjectID, "chonar")
	clearScreenPlayData(pPlayerCreo,"vardias_tyne_screenplay")	
	return 0
	
end




--------------------------------------
-- Vardias_Tyne Conversation Handler -
--------------------------------------
vardias_tyne_handler = Object:new {
}

function vardias_tyne_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	
	local screenID = screen:getScreenID()
	
	local playerCreo = LuaCreatureObject(conversingPlayer)
	-- local playerObjectPointer = player:getPlayerObject()
	
	if (screenID == "npc_2_1") then
		self:beginQuest1(playerCreo)
	
	elseif (screenID == "npc_2_2") then
		self:beginQuest2(playerCreo, conversingPlayer)
	
	elseif (screenID == "npc_reset_1") then
		self:resetQuest1(playerCreo)
	
	elseif (screenID == "npc_reward_1") then
		self:rewardQuest1(playerCreo)
	
	elseif (screenID == "npc_reset_2") then
		self:resetQuest2(playerCreo, conversingPlayer)
		
	elseif (screenID == "npc_reward_2") then
		self:rewardQuest2(playerCreo, conversingPlayer)
	
	end
	
	return conversationScreen
end

function vardias_tyne_handler:beginQuest1(playerCreo)
	local pPlayerObject = playerCreo:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	local pRhaliaWaypoint = playerObject:addWaypoint("tatooine", "Rhalia Jinsari", "Last known location of the bounty hunter Rhalia Jinsari", vardias_tyne_screenplay.loc.rhalia.x, vardias_tyne_screenplay.loc.rhalia.y,WAYPOINTBLUE, true, true)
	vardias_tyne_screenplay:setState(playerCreo, vardias_tyne_screenplay.states.quest1.started)
end

function vardias_tyne_handler:beginQuest2(playerCreo, pPlayerCreo)
	local pPlayerObject = playerCreo:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	local playerSceo = LuaSceneObject(pPlayerCreo)
	local pInventory = playerSceo:getSlottedObject("inventory")
	local pBanthaStatue = giveItem(pInventory, "object/tangible/mission/quest_item/vardias_tyne_q2_needed.iff", -1)
	
	if (pBanthaStatue == nil) then
		return 0
	end
	
	local banthaStatue = LuaSceneObject(pBanthaStatue)
	banthaStatue:setCustomObjectName("Bantha Statue")
	vardias_tyne_screenplay:writeObjectData(banthaStatue:getObjectID(), "questOwnerID", playerCreo:getObjectID())
	banthaStatue:sendTo(pPlayerCreo)
	
	--In case the server resets, we need to keep the object id of the Bantha Statue persistent, to avoid having to loop through inventory later.
	writeScreenPlayData(pPlayerCreo, "vardias_tyne_screenplay", "banthaStatueID", banthaStatue:getObjectID())
	
	local pChonarWaypoint = playerObject:addWaypoint("tatooine", "Brother Chonar", "Brother Chonar, a Dim-U monk",vardias_tyne_screenplay.loc.chonar.x, vardias_tyne_screenplay.loc.chonar.y,WAYPOINTBLUE, true, true)
	vardias_tyne_screenplay:setState(playerCreo, vardias_tyne_screenplay.states.quest2.started)
end

function vardias_tyne_handler:resetQuest1(playerCreo)
	
	vardias_tyne_screenplay:removeState(playerCreo, vardias_tyne_screenplay.states.quest1.started)
		
end

function vardias_tyne_handler:resetQuest2(playerCreo, pPlayerCreo)
	local pBanthaStatueSceo = getSceneObject(tonumber(readScreenPlayData(pPlayerCreo, "vardias_tyne_screenplay", "banthaStatueID")))
	local banthaStatueSceo = LuaSceneObject(pBanthaStatueSceo)
	banthaStatueSceo:destroyObjectFromWorld()
	banthaStatueSceo:destroyObjectFromDatabase()
	vardias_tyne_screenplay:removeState(playerCreo, vardias_tyne_screenplay.states.quest2.started)
		
end


function vardias_tyne_handler:rewardQuest1(playerCreo)
	vardias_tyne_screenplay:despawnQuest1(playerCreo:getObjectID())
	
	playerCreo:addCashCredits(4000, true)
	vardias_tyne_screenplay:setState(playerCreo, vardias_tyne_screenplay.states.quest1.completed)
end


function vardias_tyne_handler:rewardQuest2(playerCreo, pPlayerCreo)
	vardias_tyne_screenplay:despawnQuest2(pPlayerCreo)
	local pPlayerObject = playerCreo:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)
	local playerSceo = LuaSceneObject(pPlayerCreo)
	local pInventory = playerSceo:getSlottedObject("inventory")
	
	local pReward = giveItem(pInventory, "object/tangible/loot/quest/shellfish_harvester_schematic.iff", -1)
	local reward = LuaSceneObject(pReward)
	reward:sendTo(pPlayerCreo)

	vardias_tyne_screenplay:setState(playerCreo, vardias_tyne_screenplay.states.quest2.completed)
end

	
function vardias_tyne_handler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaCreatureObject(pPlayer)
	local pPlayerObject = conversingPlayer:getPlayerObject()
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")
	local inventory = LuaSceneObject(pInventory)
	
	if (pPlayerObject == nil) then
		return nil
	end
	
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	if (conversingPlayer:hasScreenPlayState(vardias_tyne_screenplay.states.quest2.completed, "vardias_tyne") == 1) then
		spatialChat(npc,"Thank you again for the help")
		return nil
	end
	
	if (conversingPlayer:hasScreenPlayState(vardias_tyne_screenplay.states.quest2.madepeace, "vardias_tyne") == 1) then
		return convoTemplate:getScreen("npc_reward_2")
	end
	
	if (conversingPlayer:hasScreenPlayState(vardias_tyne_screenplay.states.quest2.started, "vardias_tyne") == 1) then
		return convoTemplate:getScreen("npc_work_2")
	end
	
	if (conversingPlayer:hasScreenPlayState(vardias_tyne_screenplay.states.quest1.completed, "vardias_tyne") == 1) then
		return convoTemplate:getScreen("npc_1_2")
	end
	
	if (conversingPlayer:hasScreenPlayState(vardias_tyne_screenplay.states.quest1.defeated, "vardias_tyne") == 1) then
		return convoTemplate:getScreen("npc_reward_1")
	end
	
	if (conversingPlayer:hasScreenPlayState(vardias_tyne_screenplay.states.quest1.started, "vardias_tyne") == 1) then
		return convoTemplate:getScreen("npc_work_1")
	end
	
	
	
	return convoTemplate:getScreen("npc_1_1") --First quest
end





function vardias_tyne_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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



------------------------
--  Lua Components    --
------------------------

chonar_container_component = {}

function chonar_container_component:transferObject(pChonar, pObject, slot)

	local chonar = LuaSceneObject(pChonar)
	local object = LuaSceneObject(pObject)
	
	local chonarOwnerID = vardias_tyne_screenplay:readObjectData(chonar:getObjectID(), "questOwnerID")
	
	local pPlayerInv = object:getParent()
	local playerInv = LuaSceneObject(pPlayerInv)
	local pPlayerObj = playerInv:getParent()
	
	local playerCreo = LuaCreatureObject(pPlayerObj)
	local playerSceo = LuaSceneObject(pPlayerObj)
	local playerID = playerSceo:getObjectID()
	
	local banthaStatueID = readScreenPlayData(pPlayerObj, "vardias_tyne_screenplay", "banthaStatueID")
	
	if (object:getObjectID() ~= tonumber(banthaStatueID)) then
		spatialChat(pChonar, "@static_npc/tatooine/vardias_tyne:notit_2")
		return 1
	end
	
			
	if (chonarOwnerID == playerID) then 
		spatialChat(pChonar, "@static_npc/tatooine/vardias_tyne:npc_smuggle_2")
		vardias_tyne_screenplay:deleteObjectData(object:getObjectID(), "Bantha Statue")
		object:destroyObjectFromWorld()
		object:destroyObjectFromDatabase()
		
		playerCreo:sendSystemMessage("Return to Vardias Tyne")
		vardias_tyne_screenplay:setState(playerCreo, vardias_tyne_screenplay.states.quest2.madepeace)
	end
		
	return 1
end

function chonar_container_component:canAddObject()

	return 0
	
end

