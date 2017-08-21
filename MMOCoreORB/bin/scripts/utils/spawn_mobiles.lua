-- This module includes functions to spawn and despawn mobiles.
-- The module generates spawn points, spawns the mobiles, saves the id of the spawned mobiles to use them when despawning them.
-- The module has no functionality that includes time, events or observers. That needs to be handled by the user of this module.
--
-- Using the SpawnMobile module:
-- To spawn the the mobiles, call the spawnMobiles function with the appropriate arguments. The format of the arguments are described below.
-- This function will return a list with pointers to all spawned mobiles.
-- To despawn the mobiles, call the despawnMobiles function with the appropriate arguments.
-- To get a list with all spawned mobiles, call the getSpawnedMobiles function with the appropriate arguments.
-- To check if a creature belongs to a spawn call the isFromSpawn function with the appropriate arguments
--
-- Arguments:
-- pSceneObject - pointer to the scene object of the spawn is related to.
-- prefix - a string used to store the id of all spawned mobiles. The information will not be stored persistent.
--          The module will check that no data is overwritten before storing anything.
-- x - the center x coordinate for the spawn. The spawned mobiles will use this point as the center for their spawn points.
-- y - the center y coordinate for the spawn. The spawned mobiles will use this point as the center for their spawn points.
-- mobileList - a list of all mobiles to spawn and their properties. The format of the items in this list is as follows:
--               - template - the template of the mobile to spawn.
--				 - minimumDistance - the minimum distance for the mobile to spawn at from the center reference point.
--				 - maximumDistance - the maximum distance for the mobile to spawn at from the center reference point.
--				 - referencePoint - index of the spawned mobile to use as center reference point for this mobile.
--									0 = use provided coordinates, 1 = use the spawn position of the first mobile in the mobileList, etc.
--									This value must be lower than the current list item number.

local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

local SpawnMobiles = {}

local PREFIX_IN_USE = 0x14053
local PREFIX_FREE = 0
local SPAWN_MOBILES_STRING = "_spawn_mobiles"
local IN_USE_STRING = "_in_use"
local NUMBER_OF_SPAWNS_STRING = "_number_of_spawns"

-- Check if the prefix is free to use.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to check.
-- @return true if the prefix is free to use.
function SpawnMobiles.isPrefixFree(pSceneObject, prefix)
	local objectID = SceneObject(pSceneObject):getObjectID()

	local inUse = readData(objectID .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING)
	if inUse == PREFIX_IN_USE then
		Logger:log(objectID .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING .. " = true")
	else
		Logger:log(objectID .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING .. " = false")
	end
	return inUse ~= PREFIX_IN_USE
end

function SpawnMobiles.isValidMobile(pMobile)
	return pMobile ~= nil and pMobile ~= -1
end


-- Get the spawn point parameters for the specified spawn point generation.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param mobileList a list with information about what mobiles to spawn.
-- @param spawnPoints a list of already generated spawn points.
-- @param spawnObjectNumber the sequence number of the spawn point that should be generated.
-- @return a table with the relvant spawn point parameters containing, x, y, min and max.
function SpawnMobiles.getSpawnPointParameters(pSceneObject, mobileList, spawnPoints, spawnObjectNumber)
	if spawnObjectNumber < 1 or spawnObjectNumber > #mobileList or mobileList[spawnObjectNumber]["referencePoint"] < 0 then
		return nil
	end

	if (spawnPoints == nil and mobileList[spawnObjectNumber]["referencePoint"] ~= 0) or
		(spawnPoints ~= nil and mobileList[spawnObjectNumber]["referencePoint"] > #spawnPoints) then
		return nil
	end

	local parameters = {}

	parameters["min"] = mobileList[spawnObjectNumber]["minimumDistance"]
	parameters["max"] = mobileList[spawnObjectNumber]["maximumDistance"]

	if mobileList[spawnObjectNumber]["referencePoint"] == 0 then
		parameters["x"] = SceneObject(pSceneObject):getWorldPositionX()
		parameters["y"] = SceneObject(pSceneObject):getWorldPositionY()
	else
		parameters["x"] = spawnPoints[mobileList[spawnObjectNumber]["referencePoint"]][1]
		parameters["y"] = spawnPoints[mobileList[spawnObjectNumber]["referencePoint"]][3]
	end

	return parameters
end

-- Generate spawn points for all objects in the mobile list.
-- Return nil if not all spawn points were generated.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param mobileList a list with information about what mobiles to spawn.
-- @param forceSpawn force the spawn of the mobiles. Optional argument to force spawn in no spawn areas etc.
-- @return a list with spawn points to use for the mobiles, or nil if generation of spawn points failed.
function SpawnMobiles.generateSpawnPoints(pSceneObject, mobileList, forceSpawn)
	local spawnPoints = {}

	local zoneName = SceneObject(pSceneObject):getZoneName()

	for spawnObjectNumber = 1, #mobileList, 1 do
		local spawnPointParams = SpawnMobiles.getSpawnPointParameters(pSceneObject, mobileList, spawnPoints, spawnObjectNumber)
		if spawnPointParams ~= nil then
			local spawnPoint = getSpawnPoint(zoneName, spawnPointParams["x"], spawnPointParams["y"], spawnPointParams["min"], spawnPointParams["max"], forceSpawn)
			if spawnPoint ~= nil then
				spawnPoints[spawnObjectNumber] = spawnPoint
			else
				return nil
			end
		else
			return nil
		end
	end

	return spawnPoints
end

-- Spawn the objects at the spawn points.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param mobileList a list with information about what mobiles to spawn.
-- @param spawnPoints a list of spawn points to use.
-- @return a list with pointers to the spawned mobiles.
function SpawnMobiles.spawnMobileObjects(pSceneObject, prefix, mobileList, spawnPoints)
	local spawnedObjects = {}
	local playerID = SceneObject(pSceneObject):getObjectID()

	for spawnNumber = 1, #spawnPoints, 1 do
		local spawnedObject = nil

		if (readData(playerID .. prefix .. SPAWN_MOBILES_STRING .. spawnNumber .. ":noRespawn") ~= 1) then
			spawnedObject = spawnMobile(SceneObject(pSceneObject):getZoneName(), mobileList[spawnNumber]["template"], 0, spawnPoints[spawnNumber][1], spawnPoints[spawnNumber][2], spawnPoints[spawnNumber][3], getRandomNumber(360) - 180, SceneObject(pSceneObject):getParentID())
		end

		if (spawnedObject ~= nil) then
			AiAgent(spawnedObject):setNoAiAggro()
		end

		if (spawnedObject ~= nil) then
			spawnedObjects[spawnNumber] = spawnedObject
		else
			spawnedObjects[spawnNumber] = -1
		end
	end

	return spawnedObjects
end

-- Save id of the spawned mobile objects on the player for later use.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to use for storing information about the spawned mobiles.
-- @param spawnedObjects list with pointers to the spawned objects.
function SpawnMobiles.saveSpawnedMobileObjects(pSceneObject, prefix, spawnedObjects)
	local objectID = SceneObject(pSceneObject):getObjectID()

	writeData(objectID .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING, PREFIX_IN_USE)
	writeData(objectID .. prefix .. SPAWN_MOBILES_STRING .. NUMBER_OF_SPAWNS_STRING, #spawnedObjects)

	for i = 1, #spawnedObjects, 1 do
		if (spawnedObjects[i] ~= -1) then
			writeData(objectID .. prefix .. SPAWN_MOBILES_STRING .. i, SceneObject(spawnedObjects[i]):getObjectID())
		else
			writeData(objectID .. prefix .. SPAWN_MOBILES_STRING .. i, 0)
		end
	end
end

-- Generate the mobile objects.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to use for storing information about the spawned mobiles.
-- @param mobileList a list with information about what mobiles to spawn.
-- @param spawnPoints a list with spawn points to use for the mobile objects.
function SpawnMobiles.generateMobileObjects(pSceneObject, prefix, mobileList, spawnPoints)
	local spawnedObjects = SpawnMobiles.spawnMobileObjects(pSceneObject, prefix, mobileList, spawnPoints)
	SpawnMobiles.saveSpawnedMobileObjects(pSceneObject, prefix, spawnedObjects)

	return spawnedObjects
end

-- Spawn the mobiles with the supplied prefix.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to use for storing information about the spawned mobiles.
-- @param mobileList a list with information about what mobiles to spawn.
-- @param forceSpawn force the spawn of the mobiles. Optional argument to force spawn in no spawn areas etc.
-- @return a list with pointers to all spawned mobiles. If anything fails in this function it will clean up and return nil.
function SpawnMobiles.spawnMobilesWithPrefix(pSceneObject, prefix, mobileList, forceSpawn)
	local spawnPoints = SpawnMobiles.generateSpawnPoints(pSceneObject, mobileList, forceSpawn)

	if spawnPoints ~= nil and #spawnPoints > 0 then
		return SpawnMobiles.generateMobileObjects(pSceneObject, prefix, mobileList, spawnPoints)
	else
		printLuaError("SpawnMobiles.spawnMobilesWithPrefix, null spawnPoints table returned for location " .. SceneObject(pSceneObject):getWorldPositionX() .. " " .. SceneObject(pSceneObject):getWorldPositionY() .. " on " .. SceneObject(pSceneObject):getZoneName())
		return nil
	end
end

function SpawnMobiles.spawnMobilesWithLocAndPrefix(pSceneObject, prefix, mobileList)
	local spawnPoints = { }
	local baseX = SceneObject(pSceneObject):getWorldPositionX()
	local baseZ = SceneObject(pSceneObject):getWorldPositionZ()
	local baseY = SceneObject(pSceneObject):getWorldPositionY()

	for i = 1, #mobileList, 1 do
		local newX = baseX + mobileList[i].x
		local newY = baseY + mobileList[i].y
		local newZ = getTerrainHeight(pSceneObject, newX, newY)

		spawnPoints[i] = { newX, newZ, newY }
	end

	if spawnPoints ~= nil and #spawnPoints > 0 then
		return SpawnMobiles.generateMobileObjects(pSceneObject, prefix, mobileList, spawnPoints)
	else
		return nil
	end
end

-- Returns a list with pointers to the mobiles saved with the prefix.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to read the spawned mobiles from.
-- @return a list with pointers to the spawned mobiles or nil if none have been spawned.
function SpawnMobiles.getSpawnedMobilePointersList(pSceneObject, prefix)
	local spawnedMobiles = {}
	local playerID = SceneObject(pSceneObject):getObjectID()

	local numberOfSpawns = readData(playerID .. prefix .. SPAWN_MOBILES_STRING .. NUMBER_OF_SPAWNS_STRING)
	Logger:log(playerID .. prefix .. SPAWN_MOBILES_STRING .. NUMBER_OF_SPAWNS_STRING .. " = " .. numberOfSpawns, LT_INFO)

	for i = 1, numberOfSpawns, 1 do
		local mobileID = readData(playerID .. prefix .. SPAWN_MOBILES_STRING .. i)
		Logger:log(playerID .. prefix .. SPAWN_MOBILES_STRING .. i .. " = " .. mobileID, LT_INFO)
		local mobile

		if (mobileID == 0) then
			mobile = -1
		else
			mobile = getSceneObject(mobileID)
			
			if (mobile == nil) then
				mobile = -1
			end
		end

		spawnedMobiles[i] = mobile
	end

	return spawnedMobiles
end

-- Return a list with pointers to the objects that was spawned on the prefix.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to read the spawned mobiles from.
-- @return a list with pointers to the spawned mobiles or nil if none have been spawned.
function SpawnMobiles.getSpawnedMobiles(pSceneObject, prefix)
	if not SpawnMobiles.isPrefixFree(pSceneObject, prefix) then
		return SpawnMobiles.getSpawnedMobilePointersList(pSceneObject, prefix)
	else
		return nil
	end
end

-- Despawn the mobiles.
-- @param spawnedMobilesList a list of pointers to the spawned mobiles.
function SpawnMobiles.despawnMobilesInList(pSceneObject, spawnedMobilesList, prefix, storeRespawn)
	if spawnedMobilesList ~= nil then
		local playerID = SceneObject(pSceneObject):getObjectID()
		if (storeRespawn == nil) then
			storeRespawn = false
		end

		for i = 1, #spawnedMobilesList, 1 do
			if (storeRespawn and (spawnedMobilesList[i] == nil or spawnedMobilesList[i] == -1 or CreatureObject(spawnedMobilesList[i]):isDead())) then
				writeData(playerID .. prefix .. SPAWN_MOBILES_STRING .. i .. ":noRespawn", 1)
			end

			if (spawnedMobilesList[i] ~= nil and spawnedMobilesList[i] ~= -1) then
				if (CreatureObject(spawnedMobilesList[i]):isInCombat() or AiAgent(spawnedMobilesList[i]):getFollowObject() ~= nil) then
					createEvent(10000, "HelperFuncs", "despawnMobileTask", spawnedMobilesList[i], "")

					if (storeRespawn) then
						writeData(playerID .. prefix .. SPAWN_MOBILES_STRING .. i .. ":noRespawn", 1)
					end
				else
					SceneObject(spawnedMobilesList[i]):destroyObjectFromWorld()
				end
			end
		end
	end
end

function SpawnMobiles.clearStoredRespawnData(pSceneObject, prefix, mobileList)
	local playerID = SceneObject(pSceneObject):getObjectID()

	for i = 1, #mobileList, 1 do
		deleteData(playerID .. prefix .. SPAWN_MOBILES_STRING .. i .. ":noRespawn")
	end
end

-- Spawn the mobiles and store information about their ids.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to use for storing information about the spawned mobiles.
-- @param mobileList a list with information about what mobiles to spawn.
-- @param forceSpawn force the spawn of the mobiles. Optional argument to force spawn in no spawn areas etc.
-- @return a list with pointers to all spawned mobiles. If anything fails in this function it will clean up and return nil.
function SpawnMobiles.spawnMobiles(pSceneObject, prefix, mobileList, forceSpawn)
	forceSpawn = forceSpawn or false
	if SpawnMobiles.isPrefixFree(pSceneObject, prefix) then
		return SpawnMobiles.spawnMobilesWithPrefix(pSceneObject, prefix, mobileList, forceSpawn)
	else
		printLuaError("SpawnMobiles.spawnMobiles prefix " .. prefix .. " not free (playerID " .. SceneObject(pSceneObject):getObjectID() .. ")")
		return nil
	end
end

function SpawnMobiles.spawnMobilesWithLoc(pSceneObject, prefix, mobileList)
	if SpawnMobiles.isPrefixFree(pSceneObject, prefix) then
		return SpawnMobiles.spawnMobilesWithLocAndPrefix(pSceneObject, prefix, mobileList)
	else
		return nil
	end
end

-- Despawn the mobiles stored with the prefix.
-- This function will clean up the information stored with the prefix so that spawnMobiles can be called again with the same prefix.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to use for reading information about the mobiles to despawn.
function SpawnMobiles.despawnMobiles(pSceneObject, prefix, storeRespawn)
	SpawnMobiles.despawnMobilesInList(pSceneObject, SpawnMobiles.getSpawnedMobiles(pSceneObject, prefix), prefix, storeRespawn)
	writeData(SceneObject(pSceneObject):getObjectID() .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING, PREFIX_FREE)
end

-- Despawn the mobiles stored with the prefix.
-- This function will clean up the information stored with the prefix so that spawnMobiles can be called again with the same prefix.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to use for reading information about the mobiles to despawn.
-- @param pMobile pointer to the mobile that should be checked if it belongs to the spawn or not.
-- @return true if the mobile is from the spawn, false otherwise.
function SpawnMobiles.isFromSpawn(pSceneObject, prefix, pMobile)
	local spawnedMobiles = SpawnMobiles.getSpawnedMobiles(pSceneObject, prefix)
	local objectIdToCheck = SceneObject(pMobile):getObjectID()

	if spawnedMobiles ~= nil then
		for i = 1, #spawnedMobiles, 1 do
			if SpawnMobiles.isValidMobile(spawnedMobiles[i]) and objectIdToCheck == SceneObject(spawnedMobiles[i]):getObjectID() then
				return true
			end
		end
	end

	return false
end

return SpawnMobiles
