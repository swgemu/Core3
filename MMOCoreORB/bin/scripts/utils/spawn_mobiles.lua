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
	return ObjectManager.withSceneObject(pSceneObject, function(sceneObject)
		local inUse = readData(sceneObject:getObjectID() .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING)
		if inUse == PREFIX_IN_USE then
			Logger:log(sceneObject:getObjectID() .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING .. " = true")
		else
			Logger:log(sceneObject:getObjectID() .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING .. " = false")
		end
		return inUse ~= PREFIX_IN_USE
	end)
end

-- Get the spawn point parameters for the specified spawn point generation.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param mobileList a list with information about what mobiles to spawn.
-- @param spawnPoints a list of already generated spawn points.
-- @param spawnObjectNumber the sequence number of the spawn point that should be generated.
-- @return a table with the relvant spawn point parameters containing, x, y, min and max.
function SpawnMobiles.getSpawnPointParameters(pSceneObject, mobileList, spawnPoints, spawnObjectNumber)
	if spawnObjectNumber < 1 or spawnObjectNumber > table.getn(mobileList) or mobileList[spawnObjectNumber]["referencePoint"] < 0 then
		return nil
	end

	if (spawnPoints == nil and mobileList[spawnObjectNumber]["referencePoint"] ~= 0) or
	   (spawnPoints ~= nil and mobileList[spawnObjectNumber]["referencePoint"] > table.getn(spawnPoints)) then
		return nil
	end

	local parameters = {}

	parameters["min"] = mobileList[spawnObjectNumber]["minimumDistance"]
	parameters["max"] = mobileList[spawnObjectNumber]["maximumDistance"]

	if mobileList[spawnObjectNumber]["referencePoint"] == 0 then
		ObjectManager.withSceneObject(pSceneObject, function(sceneObject)
			parameters["x"] = sceneObject:getWorldPositionX()
			parameters["y"] = sceneObject:getWorldPositionY()
		end)
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

	for spawnObjectNumber = 1, table.getn(mobileList), 1 do
		local spawnPointParams = SpawnMobiles.getSpawnPointParameters(pSceneObject, mobileList, spawnPoints, spawnObjectNumber)
		if spawnPointParams ~= nil then
			local spawnPoint = getSpawnPoint(pSceneObject, spawnPointParams["x"], spawnPointParams["y"], spawnPointParams["min"], spawnPointParams["max"], forceSpawn)
			if spawnPoint ~= nil then
				table.insert(spawnPoints, spawnPoint)
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
function SpawnMobiles.spawnMobileObjects(pSceneObject, mobileList, spawnPoints)
	local spawnedObjects = {}
	local success = true

	ObjectManager.withSceneObject(pSceneObject, function(sceneObject)
		for spawnNumber = 1, table.getn(spawnPoints), 1 do
			local spawnedObject = spawnMobile(sceneObject:getZoneName(),
											  mobileList[spawnNumber]["template"],
											  0,
											  spawnPoints[spawnNumber][1],
											  spawnPoints[spawnNumber][2],
											  spawnPoints[spawnNumber][3],
											  0,
											  sceneObject:getParentID())
			table.insert(spawnedObjects, spawnedObject)
			if spawnedObject == nil then
				success = false
				return
			end
		end
	end)

	if not success then
		for i = 1, table.getn(spawnedObjects), 1 do
			ObjectManager.withSceneObject(spawnedObjects[i], function(sceneObject)
				sceneObject:destroyObjectFromWorld()
			end)
		end

		return nil
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
	Logger:log(objectID .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING .. " set to " .. PREFIX_IN_USE)
	writeData(objectID .. prefix .. SPAWN_MOBILES_STRING .. NUMBER_OF_SPAWNS_STRING, table.getn(spawnedObjects))
	Logger:log(objectID .. prefix .. SPAWN_MOBILES_STRING .. NUMBER_OF_SPAWNS_STRING .. " set to " .. table.getn(spawnedObjects))

	for i = 1, table.getn(spawnedObjects), 1 do
		ObjectManager.withSceneObject(spawnedObjects[i], function(sceneObject)
			writeData(objectID .. prefix .. SPAWN_MOBILES_STRING .. i, sceneObject:getObjectID())
			Logger:log(objectID .. prefix .. SPAWN_MOBILES_STRING .. i .. " set to " .. sceneObject:getObjectID())
		end)
	end
end

-- Generate the mobile objects.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to use for storing information about the spawned mobiles.
-- @param mobileList a list with information about what mobiles to spawn.
-- @param spawnPoints a list with spawn points to use for the mobile objects.
function SpawnMobiles.generateMobileObjects(pSceneObject, prefix, mobileList, spawnPoints)
	local spawnedObjects = SpawnMobiles.spawnMobileObjects(pSceneObject, mobileList, spawnPoints)

	if spawnedObjects ~= nil then
		SpawnMobiles.saveSpawnedMobileObjects(pSceneObject, prefix, spawnedObjects)
	end

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

	if spawnPoints ~= nil then
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

	ObjectManager.withSceneObject(pSceneObject, function(playerSceneObject)
		local numberOfSpawns = readData(playerSceneObject:getObjectID() .. prefix .. SPAWN_MOBILES_STRING .. NUMBER_OF_SPAWNS_STRING)
		Logger:log(playerSceneObject:getObjectID() .. prefix .. SPAWN_MOBILES_STRING .. NUMBER_OF_SPAWNS_STRING .. " = " .. numberOfSpawns, LT_INFO)

		for i = 1, numberOfSpawns, 1 do
			local mobileID = readData(playerSceneObject:getObjectID() .. prefix .. SPAWN_MOBILES_STRING .. i)
			Logger:log(playerSceneObject:getObjectID() .. prefix .. SPAWN_MOBILES_STRING .. i .. " = " .. mobileID, LT_INFO)
			local mobile = getSceneObject(mobileID)

			if mobile ~= nil then
				table.insert(spawnedMobiles, mobile)
			end
		end
	end)

	return spawnedMobiles
end

-- Return a list with pointers to the objects that was spawned on the prefix.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to read the spawned mobiles from.
-- @return a list with pointers to the spawned mobiles or nil if none have been spawned.
function SpawnMobiles.getSpawnedMobiles(pSceneObject, prefix)
	Logger:log("Getting spawned mobiles for prefix '" .. prefix .. "'.", LT_INFO)
	if not SpawnMobiles.isPrefixFree(pSceneObject, prefix) then
		return SpawnMobiles.getSpawnedMobilePointersList(pSceneObject, prefix)
	else
		return nil
	end
end

-- Despawn the mobiles.
-- @param spawnedMobilesList a list of pointers to the spawned mobiles.
function SpawnMobiles.despawnMobilesInList(spawnedMobilesList)
	if spawnedMobilesList ~= nil then
		for i = 1, table.getn(spawnedMobilesList), 1 do
			ObjectManager.withSceneObject(spawnedMobilesList[i], function(sceneObject)
				sceneObject:destroyObjectFromWorld()
			end)
		end
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
		return nil
	end
end

-- Despawn the mobiles stored with the prefix.
-- This function will clean up the information stored with the prefix so that spawnMobiles can be called again with the same prefix.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to use for reading information about the mobiles to despawn.
function SpawnMobiles.despawnMobiles(pSceneObject, prefix)
	SpawnMobiles.despawnMobilesInList(SpawnMobiles.getSpawnedMobiles(pSceneObject, prefix))
	ObjectManager.withSceneObject(pSceneObject, function(sceneObject)
		writeData(sceneObject:getObjectID() .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING, PREFIX_FREE)
	end)
end

-- Despawn the mobiles stored with the prefix.
-- This function will clean up the information stored with the prefix so that spawnMobiles can be called again with the same prefix.
-- @param pSceneObject pointer to the scene object that the spawn is related to.
-- @param prefix the prefix to use for reading information about the mobiles to despawn.
-- @param pMobile pointer to the mobile that should be checked if it belongs to the spawn or not.
-- @return true if the mobile is from the spawn, false otherwise.
function SpawnMobiles.isFromSpawn(pSceneObject, prefix, pMobile)
	local spawnedMobiles = SpawnMobiles.getSpawnedMobiles(pSceneObject, prefix)
	local objectIdToCheck = ObjectManager.withSceneObject(pMobile, function(mobile) return mobile:getObjectID() end)

	if spawnedMobiles ~= nil then
		for i = 1, table.getn(spawnedMobiles), 1 do
			local objectId = ObjectManager.withSceneObject(spawnedMobiles[i], function(spawnedObject) return spawnedObject:getObjectID() end)
			if objectIdToCheck == objectId then
				return true
			end
		end
	end

	return false
end

return SpawnMobiles
