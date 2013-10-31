package.path = package.path .. ";scripts/screenplays?.lua"
require("screenplay")

OLD_MAN_MIN_SPAWN_DISTANCE = 32
OLD_MAN_MAX_SPAWN_DISTANCE = 64
OLD_MAN_TEMPLATE = "old_man"
OLD_MAN_RESPAWN_TIME = 0
OLD_MAN_HEADING = 0
OLD_MAN_ID_STRING = ":old_man_id"
OLD_MAN_EVENT_SCHEDULED_STRING = "old_man_event_scheduled"
OLD_MAN_NOT_SCHEDULED = 0
OLD_MAN_SCHEDULED = 1
OLD_MAN_SPAWNED = 2
--OLD_MAN_SPAWN_TIME = 12 * 60 * 60 * 1000 -- 12 hours as base
OLD_MAN_DESPAWN_TIME = 5 * 60 * 1000 -- 5 minutes
--OLD_MAN_SPAWN_TIME = 12 * 60 * 1000 -- 12 minutes as base for testing
OLD_MAN_SPAWN_TIME = 12 * 1000 -- 12 seconds as base for testing
--OLD_MAN_DESPAWN_TIME = 30 * 1000 -- 30 seconds as base for testing
OLD_MAN_STOP_FOLLOW_TIME = 15 * 1000 -- 15 seconds
OLD_MAN_SPATIAL_CHAT_TIME = 5 * 1000 -- 5 seconds
OLD_MAN_GREETING_STRING = "@quest/force_sensitive/intro:oldman_greeting"
OLD_MAN_NO_OLD_MAN_SPAWNED = 0

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

-- Read persitent data from the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param key the key to read the value from.
-- @return the value written on the key.
function OldMan.getScreenPlayStateFromPlayer(pCreatureObject, key)
	return OldMan.withCreatureObject(pCreatureObject, function(creatureObject)
		return creatureObject:getScreenPlayState(key)
	end)
end

-- Read transient data from the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param key the key to read the value from.
-- @return the value written on the key.
function OldMan.readTransientDataFromThePlayer(pCreatureObject, key)
	return OldMan.withCreatureObject(pCreatureObject, function(creatureObject)
		return readData(creatureObject:getObjectID() .. key)
	end)
end

-- Read the id of the old man from the player he was spawned for.
-- @param pCreatureObject pointer to the creature object of the player who got the old man spawned.
-- @return the id of the old man stored on the player.
function OldMan.readOldManIdFromPlayer(pCreatureObject)
	return OldMan.readTransientDataFromThePlayer(pCreatureObject, OLD_MAN_ID_STRING)
end

-- Write persistent data to the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param key the key to write the value to.
-- @param value the value to write.
function OldMan.setScreenPlayStateOnPlayer(pCreatureObject, key, value)
	OldMan.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:setScreenPlayState(value, key)
	end)
end

-- Clear persistent data to the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param key the key to clear the value in.
-- @param value the value to clear.
function OldMan.removeScreenPlayStateOnPlayer(pCreatureObject, key, value)
	OldMan.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:removeScreenPlayState(value, key)
	end)
end

-- Write transient data to the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param key the key to write the value to.
-- @param value the value to write.
function OldMan.writeTransientDataToThePlayer(pCreatureObject, key, value)
	OldMan.withCreatureObject(pCreatureObject, function(creatureObject)
		writeData(creatureObject:getObjectID() .. key, value)
	end)
end

-- Save the id of the old man to only enable the old man for the player he was spawned for.
-- @param pCreatureObject pointer to the creature object of the player who got the old man spawned.
-- @param pOldMan pointer to the creature object of the spawned old man.
function OldMan.saveOldManIdOnPlayer(pCreatureObject, pOldMan)
	OldMan.withCreatureObject(pOldMan, function(oldManCreatureObject)
		OldMan.writeTransientDataToThePlayer(pCreatureObject, OLD_MAN_ID_STRING, oldManCreatureObject:getObjectID())
	end)
end

-- Check if the player is online.
-- @param pCreatureObject pointer to the creature object of the player who should be checked if online.
-- @return true if the player is online.
function OldMan.isPlayerOnline(pCreatureObject)
	return OldMan.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		return playerObject:isOnline()
	end) == true
end

-- Check if the player is in a building or not.
-- @param pCreatureObject pointer to the creature object of the player that should be checked for being in a building or not.
-- @return true if the player is in a building.
function OldMan.isPlayerInABuilding(pCreatureObject)
	return OldMan.withSceneObject(pCreatureObject, function(sceneObject)
		return not (sceneObject:getParentID() == NOTINABUILDING)
	end) == true
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

-- Check if the player is in a postion where the old man can be spawned.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the player is in a position where the old man can be spawned.
function OldMan.canOldManBeSpawned(pCreatureObject)
	return (OldMan.isPlayerOnline(pCreatureObject) and not OldMan.isPlayerInABuilding(pCreatureObject) and not OldMan.isPlayerInNpcCity(pCreatureObject))
end

-- Set a creature to follow another creature.
-- @param pCreatureObject pointer to the creature who should follow another creature.
-- @param pFollowObject pointer to the creature object of the creature to follow.
function OldMan.setToFollow(pCreatureObject, pFollowObject)
	OldMan.withCreatureAiAgent(pCreatureObject, function(aiAgent)
		aiAgent:setFollowObject(pFollowObject)
	end)
end

-- Function to handle the stop follow player event for the old man.
-- @param pCreatureObject pointer to the creature object of the player who got an old man that should stop following.
function OldMan:handleStopFollowPlayerEvent(pCreatureObject)
	local oldManId = OldMan.readOldManIdFromPlayer(pCreatureObject)
	local pOldMan = getSceneObject(oldManId)
	OldMan.setToFollow(pOldMan, nil)
end

-- Get the first name of the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return the first name of the player.
function OldMan.getPlayerFirstName(pCreatureObject)
	local firstName = OldMan.withCreatureObject(pCreatureObject, function(creatureObject)
		return creatureObject:getFirstName()
	end)
	
	if firstName == nil then
		return ""
	end
	
	return firstName
end

-- FUnction that sends the greeting string to the player from the old man.
-- @param pOldMan pointer to the creature object of the old man.
-- @param pCreatureObject pointer to the creature object of the player.
function OldMan.sendGreetingString(pOldMan, pCreatureObject)
	local greetingString = LuaStringIdChatParameter(OLD_MAN_GREETING_STRING)
	local firstName = OldMan.getPlayerFirstName(pCreatureObject)
	greetingString:setTT(firstName)
	spatialChat(pOldMan, greetingString:_getObject())
end

-- Function to handle the spatial chat event for the old man.
-- @param pCreatureObject pointer to the creature object of the player who got an old man that should say something in spatial chat.
function OldMan:handleSpatialChatEvent(pCreatureObject)
	local oldManId = OldMan.readOldManIdFromPlayer(pCreatureObject)
	local pOldMan = getSceneObject(oldManId)
	OldMan.sendGreetingString(pOldMan, pCreatureObject)
end

-- Despawn the old man.
-- @param pointer to the creature object of the old man.
function OldMan.despawnOldMan(pOldMan)
	OldMan.withSceneObject(pOldMan, function(sceneObject)
		sceneObject:destroyObjectFromWorld()
	end)
end

-- Function to handle the despawn of the old man.
-- @param pCreatureObject pointer to the creature object of the player whos old man should despawn.
function OldMan:handleDespawnEvent(pCreatureObject)
	local oldManId = OldMan.readOldManIdFromPlayer(pCreatureObject)
	local pOldMan = getSceneObject(oldManId)
	OldMan.despawnOldMan(pOldMan)
	OldMan.writeTransientDataToThePlayer(pCreatureObject, OLD_MAN_ID_STRING, OLD_MAN_NO_OLD_MAN_SPAWNED)
	OldMan.createSpawnOldManEvent(pCreatureObject)
end

-- Schedule despawn of the old man.
-- @param pCreatureObject pointer to the creature object of the player whos old man should be despawned.
-- @param time time until the old man should despawn.
function OldMan.scheduleDespawnOfOldMan(pCreatureObject, time)
	createEvent(time, "OldMan", "handleDespawnEvent", pCreatureObject)
end

-- Try to spawn the old man and create the needed events.
-- @param pCreatureObject pointer to the creature object of the player who should get the old man spawned.
-- @return true if everything were successful.
function OldMan.tryToSpawnOldMan(pCreatureObject)
	local pOldMan = OldMan.spawnOldMan(pCreatureObject)
	if pOldMan ~= nil then
		OldMan.saveOldManIdOnPlayer(pCreatureObject, pOldMan)
		OldMan.setToFollow(pOldMan, pCreatureObject)
		createEvent(OLD_MAN_STOP_FOLLOW_TIME, "OldMan", "handleStopFollowPlayerEvent", pCreatureObject)
		createEvent(OLD_MAN_SPATIAL_CHAT_TIME, "OldMan", "handleSpatialChatEvent", pCreatureObject)
		OldMan.scheduleDespawnOfOldMan(pCreatureObject, OLD_MAN_DESPAWN_TIME)
		return true
	else
		return false
	end
end

-- Function to handle the old man event.
-- @param pCreatureObject pointer to the creature object who should have an event created for spawning the old man.
function OldMan:handleSpawnOldManEvent(pCreatureObject)
	OldMan.removeScreenPlayStateOnPlayer(pCreatureObject, OLD_MAN_EVENT_SCHEDULED_STRING, OLD_MAN_SCHEDULED)
	if OldMan.canOldManBeSpawned(pCreatureObject) then
		if not OldMan.tryToSpawnOldMan(pCreatureObject) then
			OldMan.createSpawnOldManEvent(pCreatureObject)
		end
	else
		OldMan.createSpawnOldManEvent(pCreatureObject)
	end
end

-- Check if an event has already been scheduled for spawning the old man for this player.
-- @param pCreatureObject pointer to the creature object of the player.
-- return true if an event is already scheduled.
function OldMan.hasOldManSpawnEventScheduled(pCreatureObject)
	return OldMan.getScreenPlayStateFromPlayer(pCreatureObject, OLD_MAN_EVENT_SCHEDULED_STRING) == OLD_MAN_SCHEDULED
end

-- Generate an event to spawn the old man for the player.
-- @param pCreatureObject pointer to the creature object who should have an event created for spawning the old man.
function OldMan.createSpawnOldManEvent(pCreatureObject)
	if not OldMan.hasOldManSpawnEventScheduled(pCreatureObject) and OldMan.readOldManIdFromPlayer(pCreatureObject) == OLD_MAN_NO_OLD_MAN_SPAWNED then
		OldMan.setScreenPlayStateOnPlayer(pCreatureObject, OLD_MAN_EVENT_SCHEDULED_STRING, OLD_MAN_SCHEDULED)
		createEvent(true, OLD_MAN_SPAWN_TIME + math.random(OLD_MAN_SPAWN_TIME), "OldMan", "handleSpawnOldManEvent", pCreatureObject)
	end
end

-- Check if the old man belongs to the player or not.
-- @param pConversingPlayer pointer to the creature object of the conversing player.
-- @param pConversingNpc pointer to the creature object of the old man.
-- @return true if the old man belongs to the player.
function OldMan.oldManBelongsToThePlayer(pConversingPlayer, pConversingNpc)
	return OldMan.withCreatureObject(pConversingNpc, function(oldManCreatureObject)
		return OldMan.readOldManIdFromPlayer(pConversingPlayer) == oldManCreatureObject:getObjectID()
	end) == true
end

return OldMan
