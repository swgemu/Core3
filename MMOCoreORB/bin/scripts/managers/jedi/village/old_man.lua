package.path = package.path .. ";scripts/screenplays?.lua"
require("screenplay")

OLD_MAN_MIN_SPAWN_DISTANCE = 32
OLD_MAN_MAX_SPAWN_DISTANCE = 64
OLD_MAN_TEMPLATE = "old_man"
OLD_MAN_RESPAWN_TIME = 0
OLD_MAN_HEADING = 0

OldMan = ScreenPlay:new {}

-- Spawn the old man near the player.
-- @pCreatureObject pointer to the creature object of the player.
function OldMan.spawnOldMan(pCreatureObject)
	OldMan.withSceneObject(pCreatureObject, function(sceneObject)
		local spawnPoint = getSpawnPoint(pCreatureObject, sceneObject:getWorldPositionX(), sceneObject:getWorldPositionY(), OLD_MAN_MIN_SPAWN_DISTANCE, OLD_MAN_MAX_SPAWN_DISTANCE)
		if spawnPoint ~= nil then
			spawnMobile(sceneObject:getZoneName(), OLD_MAN_TEMPLATE, OLD_MAN_RESPAWN_TIME, spawnPoint[1], spawnPoint[2], spawnPoint[3], OLD_MAN_HEADING, sceneObject:getParentID())
		end
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
		OldMan.spawnOldMan(pCreatureObject)
	else
		OldMan.createSpawnOldManEvent(pCreatureObject)
	end
end

-- Generate an event to spawn the old man for the player.
-- @param pCreatureObject pointer to the creature object who should have an event created for spawning the old man.
function OldMan.createSpawnOldManEvent(pCreatureObject)
	createEvent(20000, "OldMan", "handleSpawnOldManEvent", pCreatureObject)
end

return OldMan
