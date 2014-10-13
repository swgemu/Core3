-- This module handles an encounter in the quest system.
-- An encounter is an event where the player should encounter something after a while.
-- The module takes care of scheduling the event, tringgering the event, clean up etc.
-- The user supplies the module with information about what the encounter is about.
--
-- Parameters
-- taskName - need to be the name of the class inheriting the Encounter class to get the observers and events to work.
-- minimumTimeUntilEncounter - the minimum time until the encounter should happen in ms.
-- maximumTimeUntilEncounter - the maximum time until the encounter should happen in ms.
-- encounterDespawnTime - time in ms from the moment the encounter is spawned until it should be despawned.
-- customSpawnBehaviour - function that is called when the encounter has been spawned with the pCreatureObject
--                        and a list of pointers to the creature objects of the spawned objects
-- spawnObjectList - a list with one element per object that should be spawned in the encounter.
--					 It uses the format from the spawn mobile unit in utils.
--                   Each element should define a table with the following parameters:
--                    - template - the template of the mobile to spawn.
--				      - minimumDistance - the minimum distance for the mobile to spawn at from the center reference point.
--				      - maximumDistance - the maximum distance for the mobile to spawn at from the center reference point.
--				      - referencePoint - index of the spawned mobile to use as center reference point for this mobile.
--									     0 = use provided coordinates, 1 = use the spawn position of the first mobile in the mobileList, etc.
--									     This value must be lower than the current list item number.
--                    - followPlayer - boolean value indicating if the spawned object should be set to follow the player or not.

local Task = require("quest.tasks.task")
local PersistentEvent = require("quest.tasks.persistent_event")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
local Logger = require("utils.logger")

local NOTINABUILDING = 0
local ENCOUNTER_CLOSING_IN_TIME = 10 * 1000
local ENCOUNTER_AT_PLAYER_TIME = 30 * 1000

Encounter = Task:new {
	-- Task properties
	taskName = "",
	-- Encounter properties
	minimumTimeUntilEncounter = 0,
	maximumTimeUntilEncounter = 0,
	encounterDespawnTime = 0,
	spawnObjectList = {},
	onEncounterSpawned = nil,
	isEncounterFinished = nil,
	onEncounterClosingIn = nil,
	onEncounterAtPlayer = nil,
	spawnTask = nil,
	despawnTask = nil
}

-- Setup persistent events
function Encounter:setupSpawnAndDespawnEvents()
	if self.spawnTask == nil then
		self.spawnTask = PersistentEvent:new {
			-- Task properties
			taskName = self.taskName .. "_spawn_task",
			taskFinish = nil,
			-- PersistentEvent properties
			minimumTimeUntilEvent = self.minimumTimeUntilEncounter,
			maximumTimeUntilEvent = self.maximumTimeUntilEncounter,
			handlerName = self.taskName,
			handlerFunction = "handleSpawnEvent",
			-- Spawn task properties
			encounter = self
		}
	end

	if self.despawnTask == nil then
		self.despawnTask = PersistentEvent:new {
			-- Task properties
			taskName = self.taskName .. "_despawn_task",
			taskFinish = nil,
			-- PersistentEvent properties
			minimumTimeUntilEvent = self.encounterDespawnTime,
			maximumTimeUntilEvent = self.encounterDespawnTime,
			handlerName = self.taskName,
			handlerFunction = "handleDespawnEvent",
			-- Spawn task properties
			encounter = self
		}
	end
end

-- Start the encounter.
-- @param pCreatureObject pointer to the creature object of the player.
function Encounter:taskStart(pCreatureObject)
	Logger:log("Starting spawn task in " .. self.taskName, LT_INFO)
	self:setupSpawnAndDespawnEvents()
	self.spawnTask:start(pCreatureObject)
	return true
end

-- Check if the player is online.
-- @param pCreatureObject pointer to the creature object of the player who should be checked if online.
-- @return true if the player is online.
function Encounter:isPlayerOnline(pCreatureObject)
	return ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		return playerObject:isOnline()
	end) == true
end

-- Check if the player is in a building or not.
-- @param pCreatureObject pointer to the creature object of the player that should be checked for being in a building or not.
-- @return true if the player is in a building.
function Encounter:isPlayerInABuilding(pCreatureObject)
	return ObjectManager.withSceneObject(pCreatureObject, function(sceneObject)
		return not (sceneObject:getParentID() == NOTINABUILDING)
	end) == true
end

-- Check if the player is in a NPC city.
-- @param pCreatureObject pointer to the creature object of the player who should be checked for being in a NPC city.
-- return true if the player is within a NPC city.
function Encounter:isPlayerInNpcCity(pCreatureObject)
	return ObjectManager.withSceneObject(pCreatureObject, function(sceneObject)
		local pCityRegion = getCityRegionAt(sceneObject:getZoneName(), sceneObject:getWorldPositionX(), sceneObject:getWorldPositionY())
		local inNpcCity = ObjectManager.withCityRegion(pCityRegion, function(cityRegion)
			return not cityRegion:isClientRegion()
		end)
		return inNpcCity == true
	end) == true
end

-- Check if the player is in a position where the encounter can be spawned.
-- @param pCreatureObject pointer to the player object of the player.
function Encounter:isPlayerInPositionForEncounter(pCreatureObject)
	return (self:isPlayerOnline(pCreatureObject) and not self:isPlayerInABuilding(pCreatureObject) and not self:isPlayerInNpcCity(pCreatureObject))
end

-- Empty handler for the handleEncounterClosingIn event.
-- @param pCreatureObject pointer to the player object of the player.
function Encounter:handleEncounterClosingIn(pCreatureObject)
	Logger:log("Mobiles closing in in encounter " .. self.taskName .. ".", LT_INFO)
	local spawnedObjects = SpawnMobiles.getSpawnedMobiles(pCreatureObject, self.taskName)
	self:callFunctionIfNotNil(self.onEncounterClosingIn, nil, pCreatureObject, spawnedObjects)
end

-- Empty handler for the handleEncounterAtPlayer event.
-- @param pCreatureObject pointer to the player object of the player.
function Encounter:handleEncounterAtPlayer(pCreatureObject)
	Logger:log("Mobiles at player in encounter " .. self.taskName .. ".", LT_INFO)
	local spawnedObjects = SpawnMobiles.getSpawnedMobiles(pCreatureObject, self.taskName)
	self:setSpawnedObjectsToFollow(spawnedObjects, nil)
	self:callFunctionIfNotNil(self.onEncounterAtPlayer, nil, pCreatureObject, spawnedObjects)
end

-- Create the events for the encounter.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param spawnedObjects list with pointers to the spawned objects.
function Encounter:createEncounterEvents(pCreatureObject, spawnedObjects)
	Logger:log("Creating encounter events in " .. self.taskName .. ".", LT_INFO)
	createEvent(ENCOUNTER_CLOSING_IN_TIME, self.taskName, "handleEncounterClosingIn", pCreatureObject)
	createEvent(ENCOUNTER_AT_PLAYER_TIME, self.taskName, "handleEncounterAtPlayer", pCreatureObject)
end

-- Set all spawned objects to follow an object.
-- @param spawnedObjects list with pointers to the spawned objects.
-- @param objectToFollow pointer to the object to follow.
function Encounter:setSpawnedObjectsToFollow(spawnedObjects, objectToFollow)
	if spawnedObjects ~= nil then
		for i = 1, table.getn(spawnedObjects), 1 do
			if self.spawnObjectList[i]["setNotAttackable"] then
				ObjectManager.withCreatureObject(spawnedObjects[i], function(creo)
					creo:setPvpStatusBitmask(0)
				end)
			end
			if self.spawnObjectList[i]["followPlayer"] then
				ObjectManager.withCreatureAiAgent(spawnedObjects[i], function(aiAgent)
					aiAgent:setFollowObject(objectToFollow)
				end)
			end
		end
	end
end

-- Create the encounter, spawn objects, setup observers and events.
-- @param pCreatureObject pointer to the creature object of the player.
function Encounter:createEncounter(pCreatureObject)
	Logger:log("Spawning mobiles in encounter " .. self.taskName .. ".", LT_INFO)
	local spawnedObjects = SpawnMobiles.spawnMobiles(pCreatureObject, self.taskName, self.spawnObjectList)

	if spawnedObjects ~= nil then
		Logger:log("Set spawned mobiles to follow in encounter " .. self.taskName .. ".", LT_INFO)
		self:setSpawnedObjectsToFollow(spawnedObjects, pCreatureObject)
		self:createEncounterEvents(pCreatureObject, spawnedObjects)
		self:callFunctionIfNotNil(self.onEncounterSpawned, nil, pCreatureObject, spawnedObjects)
	end
end

-- Spawn encounter
-- Function to call from the spawn event.
-- @param pCreatureObject pointer to the creature object of the player.
function Encounter:handleSpawnEvent(pCreatureObject)
	Logger:log("Spawn encounter in " .. self.taskName .. " triggered.", LT_INFO)
	self:setupSpawnAndDespawnEvents()
	self.spawnTask:finish(pCreatureObject)

	if not self:callFunctionIfNotNil(self.isEncounterFinished, true, pCreatureObject) then
		if self:isPlayerInPositionForEncounter(pCreatureObject) then
			self:createEncounter(pCreatureObject)
		end

		self.despawnTask:start(pCreatureObject)
	else
		self:finish(pCreatureObject)
	end
end

-- Despawn encounter
-- Function to call from the despawn event.
-- @param pCreatureObject pointer to the creature object of the player.
function Encounter:handleDespawnEvent(pCreatureObject)
	Logger:log("Despawning mobiles in encounter " .. self.taskName .. ".", LT_INFO)
	self:setupSpawnAndDespawnEvents()
	self.despawnTask:finish(pCreatureObject)

	SpawnMobiles.despawnMobiles(pCreatureObject, self.taskName)

	if not self:callFunctionIfNotNil(self.isEncounterFinished, true, pCreatureObject) then
		self:taskStart(pCreatureObject)
	else
		self:finish(pCreatureObject)
	end
end

return Encounter
