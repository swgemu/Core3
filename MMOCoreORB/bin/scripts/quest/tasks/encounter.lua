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
-- spawnObjectList - a list with one element per objec that should be spawned in the encounter.
--                   The first element is treated as the master object for the encounter.
--                   Each element should define a table with the following parameters:
--                    - template - a string with the template name of the object to spawn.
--                    - spawnedAroundPlayer - a boolean value indicating if the object should be spawned with the player as center or
--                                            if the master object should be the center of the generated spawn points.
--                    - minimumDistance - minimum distance for the spawn to the spawn center.
--                    - maximumDistance - maximum distance for the spawn to the spawn center.
--                    - followPlayer - boolean value indicating if the spawned object should be set to follow the player or not.

local Task = require("quest.tasks.task")
local PersistentEvent = require("quest.tasks.persistent_event")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

local NOTINABUILDING = 0
local ENCOUNTER_OBJECTS_STRING = "encounter_objects"
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
	isEncounterFinished = nil
}

-- Setup persistent events
function Encounter:setupSpawnAndDespawnEvents()
	self.spawnTask = PersistentEvent:new {
		-- Task properties
		taskName = "encounter_spawn_task",
		taskFinish = function(self, pCreatureObject) self.encounter:spawnEncounter(pCreatureObject) end,
		-- PersistentEvent properties
		minimumTimeUntilEvent = self.minimumTimeUntilEncounter,
		maximumTimeUntilEvent = self.maximumTimeUntilEncounter,
		-- Spawn task properties
		encounter = self
	}

	self.despawnTask = PersistentEvent:new {
		-- Task properties
		taskName = "encounter_despawn_task",
		taskFinish = function(self, pCreatureObject) self.encounter:despawnEncounter(pCreatureObject) end,
		-- PersistentEvent properties
		minimumTimeUntilEvent = self.encounterDespawnTime,
		maximumTimeUntilEvent = self.encounterDespawnTime,
		-- Spawn task properties
		encounter = self
	}
end

-- Start the encounter.
-- @param pCreatureObject pointer to the creature object of the player.
function Encounter:taskStart(pCreatureObject)
	self:setupSpawnAndDespawnEvents()
	self.spawnTask:start(pCreatureObject)
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
	error("The handleEncounterClosingIn function in " .. Task.taskName .. " has not been implemented.", 2)
end

-- Empty handler for the handleEncounterAtPlayer event.
-- @param pCreatureObject pointer to the player object of the player.
function Encounter:handleEncounterAtPlayer(pCreatureObject)
	error("The handleEncounterAtPlayer function in " .. Task.taskName .. " has not been implemented.", 2)
end

-- Create the events for the encounter.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param spawnedObjects list with pointers to the spawned objects.
function Encounter:createEncounterEvents(pCreatureObject, spawnedObjects)
	createEvent(ENCOUNTER_CLOSING_IN_TIME, self.taskName, "handleEncounterClosingIn", pCreatureObject)
	createEvent(ENCOUNTER_AT_PLAYER_TIME, self.taskName, "handleEncounterAtPlayer", pCreatureObject)
end

-- Set all spawned objects to follow the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param spawnedObjects list with pointers to the spawned objects.
function Encounter:setSpawnedObjectsToFollowThePlayer(pCreatureObject, spawnedObjects)
	for i = 1, table.getn(spawnedObjects), 1 do
		if self.spawnObjectList[i]["followPlayer"] then
			ObjectManager.withCreatureAiAgent(spawnedObjects[i], function(aiAgent)
				aiAgent:setFollowObject(pCreatureObject)
			end)
		end
	end
end

-- Create the encounter, spawn objects, setup observers and events.
-- @param pCreatureObject pointer to the creature object of the player.
function Encounter:createEncounter(pCreatureObject)
	local spawnedObjects = SpawnMobiles.spawnMobiles(pCreatureObject, self.taskName, self.spawnObjectList)

	if spawnedObjects ~= nil then
		self:setSpawnedObjectsToFollowThePlayer(pCreatureObject, spawnedObjects)
		self:createEncounterEvents(pCreatureObject, spawnedObjects)
		self:callFunctionIfNotNil(self.onEncounterSpawned, pCreatureObject, spawnedObjects)
	end
end

-- Spawn encounter
-- Function to call from the spawn event.
-- @param pCreatureObject pointer to the creature object of the player.
function Encounter:spawnEncounter(pCreatureObject)
	if self:isPlayerInPositionForEncounter(pCreatureObject) then
		self:createEncounter(pCreatureObject)
	end
	self.despawnTask:start(pCreatureObject)
end

-- Despawn encounter
-- Function to call from the despawn event.
-- @param pCreatureObject pointer to the creature object of the player.
function Encounter:despawnEncounter(pCreatureObject)
	SpawnMobiles.despawnMobiles(pCreatureObject, self.taskName)

	if not self:callFunctionIfNotNil(self.isEncounterFinished, pCreatureObject) then
		self.spawnTask:start(pCreatureObject)
	else
		self:finish(pCreatureObject)
	end
end

return Encounter
