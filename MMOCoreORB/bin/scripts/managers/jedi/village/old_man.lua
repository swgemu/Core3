package.path = package.path .. ";scripts/screenplays?.lua"
require("screenplay")

OLD_MAN_MIN_SPAWN_DISTANCE = 32
OLD_MAN_MAX_SPAWN_DISTANCE = 64
OLD_MAN_TEMPLATE = "old_man"
OLD_MAN_RESPAWN_TIME = 0
OLD_MAN_HEADING = 0
OLD_MAN_ID_STRING = ":old_man_id"

OldMan = ScreenPlay:new {}

-- Spawn the old man near the player.
-- @pCreatureObject pointer to the creature object of the player.
function OldMan.spawnOldMan(pCreatureObject)
	return OldMan.withSceneObject(pCreatureObject, function(sceneObject)
		local spawnPoint = getSpawnPoint(pCreatureObject, sceneObject:getWorldPositionX(), sceneObject:getWorldPositionY(), OLD_MAN_MIN_SPAWN_DISTANCE, OLD_MAN_MAX_SPAWN_DISTANCE)
		if spawnPoint ~= nil then
			return spawnMobile(sceneObject:getZoneName(), OLD_MAN_TEMPLATE, OLD_MAN_RESPAWN_TIME, spawnPoint[1], spawnPoint[2], spawnPoint[3], OLD_MAN_HEADING, sceneObject:getParentID())
		end
		return nil
	end)
end

-- Save the id of the old man to only enable the old man for the player he was spawned for.
-- @param pCreatureObject pointer to the creature object of the player who got the old man spawned.
-- @param pOldMan pointer to the creature object of the spawned old man.
function OldMan.saveOldManIdOnPlayer(pCreatureObject, pOldMan)
	OldMan.withCreatureObject(pCreatureObject, function(playerCreatureObject)
		OldMan.withCreatureObject(pOldMan, function(oldManCreatureObject)
			writeData(playerCreatureObject:getObjectID() .. OLD_MAN_ID_STRING, oldManCreatureObject:getObjectID())
		end)
	end)
end

-- Check if the player is online.
-- @param pCreatureObject pointer to the creature object of the player who should be checked if online.
-- @return true if the player is online.
function OldMan.isPlayerOnline(pCreatureObject)
	return OldMan.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		return playerObject:isOnline()
	end)
end

-- Check if the player is in a building or not.
-- @param pCreatureObject pointer to the creature object of the player that should be checked for being in a building or not.
-- @return true if the player is in a building.
function OldMan.isPlayerInABuilding(pCreatureObject)
	return OldMan.withSceneObject(pCreatureObject, function(sceneObject)
		return not (sceneObject:getParentID() == NOTINABUILDING)
	end)
end

-- Check if the player is in a NPC city.
-- @param pCreatureObject pointer to the creature object of the player who should be checked for being in a NPC city.
-- return true if the player is within a NPC city.
function OldMan.isPlayerInNpcCity(pCreatureObject)
	return OldMan.withSceneObject(pCreatureObject, function(sceneObject)
		local pCityRegion = getCityRegionAt(sceneObject:getZoneName(), sceneObject:getWorldPositionX(), sceneObject:getWorldPositionY())
		local inNpcCity = OldMan.withCityRegion(pCityRegion, function(cityRegion)
			return not cityRegion:isClientRegion()
		end)
		return inNpcCity == true
	end) == true
end

-- Function to handle the old man event.
-- @param pCreatureObject pointer to the creature object who should have an event created for spawning the old man.
function OldMan:handleSpawnOldManEvent(pCreatureObject)
	if OldMan.isPlayerOnline(pCreatureObject) and not OldMan.isPlayerInABuilding(pCreatureObject) and 
           not OldMan.isPlayerInNpcCity(pCreatureObject) then
		local pOldMan = OldMan.spawnOldMan(pCreatureObject)
		if pOldMan ~= nil then
			OldMan.saveOldManIdOnPlayer(pCreatureObject, pOldMan)
		else
			OldMan.createSpawnOldManEvent(pCreatureObject)
		end
	else
		OldMan.createSpawnOldManEvent(pCreatureObject)
	end
end

-- Generate an event to spawn the old man for the player.
-- @param pCreatureObject pointer to the creature object who should have an event created for spawning the old man.
function OldMan.createSpawnOldManEvent(pCreatureObject)
	createEvent(20000, "OldMan", "handleSpawnOldManEvent", pCreatureObject)
end

-- Check if the old man belongs to the player or not.
-- @param pConversingPlayer pointer to the creature object of the conversing player.
-- @param pConversingNpc pointer to the creature object of the old man.
-- @return true if the old man belongs to the player.
function OldMan.oldManBelongsToThePlayer(pConversingPlayer, pConversingNpc)
	return OldMan.withCreatureObject(pConversingPlayer, function(playerCreatureObject)
		return OldMan.withCreatureObject(pConversingNpc, function(oldManCreatureObject)
			return readData(playerCreatureObject:getObjectID() .. OLD_MAN_ID_STRING) == oldManCreatureObject:getObjectID()
		end) == true
	end) == true
end

return OldMan
