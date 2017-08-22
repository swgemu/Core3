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
-- customSpawnBehaviour - function that is called when the encounter has been spawned with the pPlayer
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

local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
local Logger = require("utils.logger")

Encounter = Task:new {
	-- Task properties
	taskName = "",
	-- Encounter properties
	encounterDespawnTime = 0,
	despawnMessage = "",
	spawnObjectList = {},
	onEncounterSpawned = nil,
	onEncounterDespawned = nil,
	isEncounterFinished = nil,
	onEncounterInRange = nil,
	inRangeValue = 16,
}

-- Start the encounter.
-- @param pPlayer pointer to the creature object of the player.
function Encounter:taskStart(pPlayer)
	if not self:callFunctionIfNotNil(self.isEncounterFinished, true, pPlayer) then
		if not self:isPlayerInPositionForEncounter(pPlayer) or CreatureObject(pPlayer):isDead() then
			return false
		end

		local result = self:createEncounter(pPlayer)

		if (result) then
			createEvent(self.encounterDespawnTime, self.taskName, "handleDespawnEvent", pPlayer, "")
		end

		return result
	end

	return true
end

-- Check if the player is online.
-- @param pPlayer pointer to the creature object of the player who should be checked if online.
-- @return true if the player is online.
function Encounter:isPlayerOnline(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	return pGhost ~= nil and PlayerObject(pGhost):isOnline()
end

-- Check if the player is in a building or not.
-- @param pPlayer pointer to the creature object of the player that should be checked for being in a building or not.
-- @return true if the player is in a building.
function Encounter:isPlayerInABuilding(pPlayer)
	return SceneObject(pPlayer):getParentID() ~= 0
end

-- Check if the player is in a NPC city.
-- @param pPlayer pointer to the creature object of the player who should be checked for being in a NPC city.
-- return true if the player is within a NPC city.
function Encounter:isPlayerInNpcCity(pPlayer)
	local pCityRegion = getCityRegionAt(SceneObject(pPlayer):getZoneName(), SceneObject(pPlayer):getWorldPositionX(), SceneObject(pPlayer):getWorldPositionY())

	if (pCityRegion == nil) then
		return false
	end

	return CityRegion(pCityRegion):isClientRegion()
end

-- Check if the player is in a position where the encounter can be spawned.
-- @param pPlayer pointer to the player object of the player.
function Encounter:isPlayerInPositionForEncounter(pPlayer)
	if pPlayer == nil or SceneObject(pPlayer):getZoneName() == "" then
		return false
	end

	return self:isPlayerOnline(pPlayer) and not self:isPlayerInABuilding(pPlayer) and not self:isPlayerInNpcCity(pPlayer)
end

-- Empty handler for the handleEncounterInRange event.
-- @param pPlayer pointer to the player object of the player.
function Encounter:handleEncounterInRangeCheck(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local spawnedObjects = SpawnMobiles.getSpawnedMobiles(pPlayer, self.taskName)

	if (spawnedObjects == nil or spawnedObjects[1] == nil) then
		return
	end

	-- calculateDistance function is compared against squared range for accuracy
	if (CreatureObject(spawnedObjects[1]):isInRangeWithObject(pPlayer, self.inRangeValue)) then
		self:callFunctionIfNotNil(self.onEncounterInRange, nil, pPlayer, spawnedObjects)
	else
		createEvent(1000, self.taskName, "handleEncounterInRangeCheck", pPlayer, "")
	end
end

-- Create the events for the encounter.
-- @param pPlayer pointer to the creature object of the player.
-- @param spawnedObjects list with pointers to the spawned objects.
function Encounter:createEncounterEvents(pPlayer, spawnedObjects)
	Logger:log("Creating encounter distance heartbeat in " .. self.taskName .. ".", LT_INFO)
	createEvent(1000, self.taskName, "handleEncounterInRangeCheck", pPlayer, "")
end

-- Set all spawned objects to follow an object.
-- @param spawnedObjects list with pointers to the spawned objects.
-- @param objectToFollow pointer to the object to follow.
function Encounter:setSpawnedObjectsToFollow(spawnedObjects, objectToFollow)
	if spawnedObjects ~= nil then
		for i = 1, #spawnedObjects, 1 do
			if self.spawnObjectList[i]["setNotAttackable"] then
				CreatureObject(spawnedObjects[i]):setPvpStatusBitmask(0)
			end

			if self.spawnObjectList[i]["followPlayer"] then
				if self.spawnObjectList[i]["setNotAttackable"] then
					AiAgent(spawnedObjects[i]):setAiTemplate("follow")
				else
					AiAgent(spawnedObjects[i]):setAiTemplate("stationarynoleash")
				end
				AiAgent(spawnedObjects[i]):setFollowObject(objectToFollow)
			end
		end
	end
end

-- Create the encounter, spawn objects, setup observers and events.
-- @param pPlayer pointer to the creature object of the player.
function Encounter:createEncounter(pPlayer)
	Logger:log("Spawning mobiles in encounter " .. self.taskName .. ".", LT_INFO)
	local spawnedObjects = SpawnMobiles.spawnMobiles(pPlayer, self.taskName, self.spawnObjectList, true)

	if spawnedObjects ~= nil then
		Logger:log("Set spawned mobiles to follow in encounter " .. self.taskName .. ".", LT_INFO)
		self:setSpawnedObjectsToFollow(spawnedObjects, pPlayer)
		self:createEncounterEvents(pPlayer, spawnedObjects)
		self:callFunctionIfNotNil(self.onEncounterSpawned, nil, pPlayer, spawnedObjects)
		return true
	end

	printLuaError("Encounter:createEncounter failed to spawn mobiles for task " .. self.taskName .. " (playerID " .. SceneObject(pPlayer):getObjectID() .. "). Player location: " .. SceneObject(pPlayer):getWorldPositionX() .. ", " .. SceneObject(pPlayer):getWorldPositionY() .. " on " .. SceneObject(pPlayer):getZoneName())
	return false
end

-- Despawn encounter
-- Function to call from the despawn event.
-- @param pPlayer pointer to the creature object of the player.
function Encounter:handleDespawnEvent(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local spawnedObjects = SpawnMobiles.getSpawnedMobiles(pPlayer, self.taskName)

	if (spawnedObjects == nil) then
		self:doDespawn(pPlayer)
		return
	end

	for i = 1, #spawnedObjects, 1 do
		if SpawnMobiles.isValidMobile(spawnedObjects[i]) and AiAgent(spawnedObjects[i]):isInCombat() then
			createEvent(self.encounterDespawnTime, self.taskName, "handleDespawnEvent", pPlayer, "")
			return
		end
	end

	if (self.despawnMessage ~= "") then
		CreatureObject(pPlayer):sendSystemMessage(self.despawnMessage)
	end

	local runAway = false

	local mobX, mobY

	for i = 1, #spawnedObjects, 1 do
		if SpawnMobiles.isValidMobile(spawnedObjects[i]) and self.spawnObjectList[i]["runOnDespawn"] then
			CreatureObject(spawnedObjects[i]):setPvpStatusBitmask(0)
			AiAgent(spawnedObjects[i]):setAiTemplate("follow")
			runAway = true
			mobX = SceneObject(spawnedObjects[i]):getPositionX()
			mobY = SceneObject(spawnedObjects[i]):getPositionY()
		end
	end

	if (not runAway) then
		self:doDespawn(pPlayer)
		return
	end

	local playerX = SceneObject(pPlayer):getPositionX()
	local playerY = SceneObject(pPlayer):getPositionY()
	local newX, newY

	if (playerX < mobX) then
		newX = playerX - getRandomNumber(20,40)
	else
		newX = playerX + getRandomNumber(20,40)
	end

	if (playerY < mobY) then
		newY = playerY - getRandomNumber(20,40)
	else
		newY = playerY + getRandomNumber(20,40)
	end

	local newZ = getTerrainHeight(pPlayer, newX, newY)

	for i = 1, #spawnedObjects, 1 do
		if (SpawnMobiles.isValidMobile(spawnedObjects[i])) then
			local objectID = SceneObject(spawnedObjects[i]):getObjectID()
			writeData(objectID .. ":encounterNewX", newX)
			writeData(objectID .. ":encounterNewY", newY)
			writeData(objectID .. ":encounterNewZ", newZ)
			createEvent(1000, self.taskName, "doRunAway", spawnedObjects[i], "")
		end
	end

	createEvent(9000, self.taskName, "doDespawn", pPlayer, "")
end

function Encounter:doRunAway(pAiAgent)
	if pAiAgent == nil or not SceneObject(pAiAgent):isAiAgent() then
		return
	end

	local objectID = SceneObject(pAiAgent):getObjectID()
	local newX = readData(objectID .. ":encounterNewX")
	local newY = readData(objectID .. ":encounterNewY")
	local newZ = readData(objectID .. ":encounterNewZ")

	AiAgent(pAiAgent):setFollowObject(nil)
	AiAgent(pAiAgent):setAiTemplate("manualescort")

	AiAgent(pAiAgent):stopWaiting()
	AiAgent(pAiAgent):setWait(0)
	AiAgent(pAiAgent):setNextPosition(newX, newZ, newY, 0)
	AiAgent(pAiAgent):executeBehavior()

	deleteData(objectID .. ":encounterNewX")
	deleteData(objectID .. ":encounterNewY")
	deleteData(objectID .. ":encounterNewZ")
end

function Encounter:doDespawn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	Logger:log("Despawning mobiles in encounter " .. self.taskName .. ".", LT_INFO)

	SpawnMobiles.despawnMobiles(pPlayer, self.taskName, false)
	self:callFunctionIfNotNil(self.onEncounterDespawned, nil, pPlayer)

	self:finish(pPlayer)
end

return Encounter
