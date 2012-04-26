hedon_istee_screenplay = ScreenPlay:new {
	numberOfActs = 1,

	states = {
		quest1 = {started = 1, defeated = 2, completed = 8},
		quest2 = {started = 16, defeated = 32, completed = 64},
		quest3 = {started = 128, delivered = 256, completed = 512}
	},

	loc = {
		drog = {x = 1553, z = 15, y = 3488},
		rath = {x = 1800, z = 7, y = 3128},
		monk = {x = 1560, z = 7, y = 2970}
	}
}

registerScreenPlay("hedon_istee_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function hedon_istee_screenplay:start()
	self:spawnActiveAreas()
	self:spawnMobiles()
end

function hedon_istee_screenplay:spawnActiveAreas()
	local pActiveArea1 = spawnSceneObject("tatooine", "object/active_area.iff", self.loc.drog.x, self.loc.drog.z, self.loc.drog.y, 0, 0, 0, 0, 0)
	local pActiveArea2 = spawnSceneObject("tatooine", "object/active_area.iff", self.loc.rath.x, self.loc.rath.z, self.loc.rath.y, 0, 0, 0, 0, 0)
	--local pActiveArea3 = spawnSceneObject("tatooine", "object/active_area.iff", self.loc.monk.x, self.loc.monk.z, self.loc.monk.y, 0, 0, 0, 0, 0)

	--Drognuz Active Area
	if (pActiveArea1 ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea1)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "hedon_istee_screenplay", "notifyEnteredArea1", pActiveArea1)
	end

	--Bounty Hunter Active Area
	if (pActiveArea2 ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea2)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "hedon_istee_screenplay", "notifyEnteredArea2", pActiveArea2)
	end

	--Bomarr Monk Active Area
	if (pActiveArea3 ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea3)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "hedon_istee_screenplay", "notifyEnteredArea3", pActiveArea3)
	end
end

function hedon_istee_screenplay:spawnMobiles()
	spawnMobile("tatooine", "hedon_istee", 1, 1390, 0, 3195, 0, 0)
end

---
--Observer Notifications
---
function hedon_istee_screenplay:notifyEnteredArea1(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)

	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()

		if (self:hasState(player, self.states.quest1.started)) and (not self:hasState(player, self.states.quest1.defeated)) then
			if (not self:hasSpawned(objectID, "drognuz")) then
				self:setSpawned(objectID, "drognuz")

				--TODO: Randomize the spawn point
				local pDrognuz = spawnMobile("tatooine", "drognuz", 0, self.loc.drog.x, self.loc.drog.z, self.loc.drog.y, 0, 0)
				local drognuz = LuaSceneObject(pDrognuz)

				self:writeObjectData(objectID, "drognuz", drognuz:getObjectID())
				self:writeObjectData(drognuz:getObjectID(), "questOwnerID", objectID)

				createObserver(OBJECTDESTRUCTION, "hedon_itsee_screenplay", "notifyDrognuzDefeated", pDrognuz)
				createObserver(OBJECTINRANGEMOVED, "hedon_itsee_screenplay", "notifyDrognuzBark", pDrognuz)
			end
		end
	end
end

function hedon_istee_screenplay:notifyDrognuzDefeated(pDrognuz, pAttacker)
	local drognuz = LuaCreatureObject(pDrognuz)
	local ownerID = self:readObjectData(victim:getObjectID(), "questOwnerID")
	local pOwner = getCreatureObject(ownerID)

	if (pOwner == nil) then
		return 0;
	end

	local owner = LuaCreatureObject(pOwner)

	self:setState(owner, self.states.quest1.defeated)

	self:deleteObjectData(objectID, "drognuz")
	self:deleteObjectData(drognuz:getObjectID(), "questOwnerID")

	return 1
end

function hedon_istee_screenplay:notifyDrognuzBark(pDrognuz, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)

	if (movingObject:isCreatureObject()) then
		local drognuz = LuaCreatureObject(pDrognuz)
		local distance = drognuz:getDistanceTo(pMovingObject)

		if (distance == 0 or distance > 16) then
			return 0
		end

		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()

		if (self:hasState(player, self.states.quest1.started)) and (not self:hasState(player, self.states.quest1.defeated)) then
			if (self:hasSpawned(objectID, "drognuz")) then
				if (self:readObjectData(objectID, "drognuz_spoken") ~= 1) then
					spatialChat(pPrisoner, "@static_npc/tatooine/hedon_istee:npc_breech_1") --Grunt!
					self:writeObjectData(objectID, "drognuz_spoken", 1)

					return 1
				end
			end
		end
	end

	return 0
end

function hedon_istee_screenplay:notifyEnteredArea2(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)

	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()

		if (self:hasState(player, self.states.quest2.started)) and (not self:hasState(player, self.states.quest2.defeated)) then
			if (not self:hasSpawned(objectID, "rath")) then
				self:setSpawned(objectID, "rath")

				--TODO: Randomize the spawn point
				local pRath = spawnMobile("tatooine", "rath_kana", 0, self.loc.rath.x, self.loc.rath.z, self.loc.rath.y, 0, 0)
				local rath = LuaSceneObject(pRath)

				self:writeObjectData(objectID, "rath", drognuz:getObjectID())
				self:writeObjectData(rath:getObjectID(), "questOwnerID", objectID)

				createObserver(OBJECTDESTRUCTION, "hedon_itsee_screenplay", "notifyRathDefeated", pRath)
				createObserver(OBJECTINRANGEMOVED, "hedon_itsee_screenplay", "notifyRathBark", pRath)
			end
		end
	end
end

function hedon_istee_screenplay:notifyRathDefeated(pRath, pAttacker)
	local rath = LuaCreatureObject(pRath)
	local ownerID = self:readObjectData(victim:getObjectID(), "questOwnerID")
	local pOwner = getCreatureObject(ownerID)

	if (pOwner == nil) then
		return 0;
	end

	local owner = LuaCreatureObject(pOwner)

	self:setState(owner, self.states.quest2.defeated)

	self:deleteObjectData(objectID, "rath")
	self:deleteObjectData(rath:getObjectID(), "questOwnerID")

	return 1
end

function hedon_istee_screenplay:notifyRathBark(pRath, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)

	if (movingObject:isCreatureObject()) then
		local rath = LuaCreatureObject(pRath)
		local distance = rath:getDistanceTo(pMovingObject)

		if (distance == 0 or distance > 16) then
			return 0
		end

		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()

		if (self:hasState(player, self.states.quest2.started)) and (not self:hasState(player, self.states.quest2.defeated)) then
			if (self:hasSpawned(objectID, "rath")) then
				if (self:readObjectData(objectID, "rath_spoken") ~= 1) then
					spatialChat(pPrisoner, "@static_npc/tatooine/hedon_istee:npc_breech_2") --All the B'omarr want is that sacred scroll. You're in my way and must be removed.
					self:writeObjectData(objectID, "rath_spoken", 1)

					return 1
				end
			end
		end
	end

	return 0
end

function hedon_istee_screenplay:notifyEnteredArea3(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)

	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()

		if (self:hasState(player, self.states.quest3.started)) and (not self:hasState(player, self.states.quest3.defeated)) then
			if (not self:hasSpawned(objectID, "monk")) then
				self:setSpawned(objectID, "monk")

				--TODO: Randomize the spawn point
				local pMonk = spawnMobile("tatooine", "serene_floater", 0, self.loc.monk.x, self.loc.monk.z, self.loc.monk.y, 0, 0)
				local monk = LuaSceneObject(pRath)

				self:writeObjectData(objectID, "monk", monk:getObjectID())
				self:writeObjectData(monk:getObjectID(), "questOwnerID", objectID)

				createObserver(OBJECTINRANGEMOVED, "hedon_itsee_screenplay", "notifyMonkBark", pMonk)
			end
		end
	end
end

function hedon_istee_screenplay:notifyMonkBark(pMonk, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)

	if (movingObject:isCreatureObject()) then
		local monk = LuaCreatureObject(pMonk)
		local distance = monk:getDistanceTo(pMovingObject)

		if (distance == 0 or distance > 16) then
			return 0
		end

		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()

		if (self:hasState(player, self.states.quest3.started)) and (not self:hasState(player, self.states.quest3.delivered)) then
			if (self:hasSpawned(objectID, "monk")) then
				if (self:readObjectData(objectID, "monk_spoken") ~= 1) then
					--Check for the scroll
					--Has Scroll
					--spatialChat(pMonk, "@static_npc/tatooine/hedon_istee:npc_smuggle_3") --The scroll.  You have begun your travel down the path of enlightenment, sensualist.  We will watch from afar, but no longer through direct intervention.
					--Doesn't have scroll
					--spatialChat(pMonk, "@static_npc/tatooine/hedon_istee:dontknowyou_3") --Until that time has come, your life will be filled with false euphoria.
					--Bark when close.
					spatialChat(pMonk, "@static_npc/tatooine/hedon_istee:npc_breech_3") --May you come to know the serenity of emptiness, sensualist.
					self:writeObjectData(objectID, "monk_spoken", 1)
					return 1
				end
			end
		end
	end

	return 0
end

--------------------------------------
--   Common functions                -
--------------------------------------
function hedon_istee_screenplay:hasState(player, state)
	if (player == nil) then
		return false
	end

	local val = player:hasScreenPlayState(state, "hedon_istee")

	if (val == 1) then
		return true
	end

	return false
end

function hedon_istee_screenplay:hasSpawned(objectID, key)
	local val = readData(objectID .. ":hedon_istee:spawned:" .. key)

	if (val == 1) then
		return true
	end

	return false
end

function hedon_istee_screenplay:setSpawned(objectID, key)
	writeData(objectID .. ":hedon_istee:spawned:" .. key, 1)
end

function hedon_istee_screenplay:deleteSpawnedSetting(objectID, key)
	deleteData(objectID .. ":hedon_istee:spawned:" .. key)
end

function hedon_istee_screenplay:writeObjectData(objectID, key, value)
	if (objectID == nil) then
		return 0
	end

	writeData(objectID .. ":hedon_istee:" .. key, value)
end

function hedon_istee_screenplay:readObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end

	return readData(objectID .. ":hedon_istee:" .. key)
end

function hedon_istee_screenplay:deleteObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end

	deleteData(objectID .. ":hedon_istee:" .. key)
end

function hedon_istee_screenplay:setState(creatureObject, state)
	creatureObject:setScreenPlayState(state, "hedon_istee")
end



---
--Hedon Istee Conversation Handler
---
hedon_istee_handler = Object:new {
}

function hedon_istee_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	local player = LuaCreatureObject(conversingPlayer)
	local playerObjectPointer = player:getPlayerObject()

	if (screenID == "npc_2_1") then
		self:beginQuest1(player)
	elseif (screenID == "npc_2_2") then
		self:beginQuest2(player)
	elseif (screenID == "npc_2_3") then
		self:beginQuest3(player)
	elseif (screenID == "npc_reset") then
		self:resetQuest(player)
	end

	return conversationScreen
end

function hedon_istee_handler:beginQuest1(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	--Waypoint to Drognuz
	playerObject:addWaypoint("tatooine", "Drognuz", "", hedon_istee_screenplay.loc.drog.x, hedon_istee_screenplay.loc.drog.y, WAYPOINTBLUE, true, true)

	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest1.started)
end

function hedon_istee_handler:beginQuest2(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	--playerObject:addWaypoint("dathomir", "@static_npc/dathomir/dathomir_imperialprison_hedon_istee:waypoint_name_2", "@static_npc/dathomir/dathomir_imperialprison_hedon_istee:waypoint_description_2", hedon_istee_screenplay.loc.djk.x, hedon_istee_screenplay.loc.djk.y, WAYPOINTBLUE, true, true)
	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest2.started)
end

function hedon_istee_handler:beginQuest3(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	--playerObject:addWaypoint("dathomir", "@static_npc/dathomir/dathomir_imperialprison_hedon_istee:waypoint_name_3", "@static_npc/dathomir/dathomir_imperialprison_hedon_istee:waypoint_description_3", hedon_istee_screenplay.loc.djm.x, hedon_istee_screenplay.loc.djm.y, WAYPOINTBLUE, true, true)
	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest3.started)
end

function hedon_istee_handler:resetQuest(player)
end

function hedon_istee_handler:getInitialScreen(pPlayer, npc, pConversationTemplate)
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

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest3.completed, "hedon_istee") == 1) then
		return convoTemplate:getScreen("nextQuest")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest3.delivered, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_reward_3")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest3.started, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_work_3")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest2.completed, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_1_3")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest2.defeated, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_reward_2")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest2.started, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_work_2")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest1.completed, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_1_2")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest1.defeated, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_reward_1")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest1.started, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_work_1")
	end

	--We need to check skill points here maybe?
	--if (faction ~= 3679112276) then
	--return convoTemplate:getScreen("notyet")
	--end

	return convoTemplate:getScreen("npc_1_1") --First quest
end

function hedon_istee_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
