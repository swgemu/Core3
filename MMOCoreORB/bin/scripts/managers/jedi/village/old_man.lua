local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")

local OldMan = {}
OldManPublicEventsAndObservers = {}
local OldManPrivate = {}

-- Expose private functions for testing.
function OldMan.exposePrivateFunctions()
	if BUSTED_TEST then
		OldMan.private = OldManPrivate
		OldMan.global = OldManPublicEventsAndObservers
	end
end

-- Hide private functions.
function OldMan.hidePrivateFunctions()
	OldMan.private = {}
	OldMan.global = {}
end

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
OLD_MAN_SPAWN_TIME = 30 * 1000 -- 12 seconds as base for testing
--OLD_MAN_DESPAWN_TIME = 30 * 1000 -- 30 seconds as base for testing
OLD_MAN_STOP_FOLLOW_TIME = 15 * 1000 -- 15 seconds
OLD_MAN_SPATIAL_CHAT_TIME = 5 * 1000 -- 5 seconds
OLD_MAN_GREETING_STRING = "@quest/force_sensitive/intro:oldman_greeting"
OLD_MAN_NO_OLD_MAN_SPAWNED = 0
OLD_MAN_INVENTORY_STRING = "inventory"
OLD_MAN_FORCE_CRYSTAL_STRING = "object/tangible/loot/quest/force_sensitive/force_crystal.iff"

-- Spawn the old man near the player.
-- @pCreatureObject pointer to the creature object of the player.
function OldManPrivate.spawnOldMan(pCreatureObject)
	return ObjectManager.withSceneObject(pCreatureObject, function(sceneObject)
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
function OldManPrivate.getScreenPlayStateFromPlayer(pCreatureObject, key)
	return ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return creatureObject:getScreenPlayState(key)
	end)
end

-- Read transient data from the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param key the key to read the value from.
-- @return the value written on the key.
function OldManPrivate.readTransientDataFromThePlayer(pCreatureObject, key)
	return ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return readData(creatureObject:getObjectID() .. key)
	end)
end

-- Read the id of the old man from the player he was spawned for.
-- @param pCreatureObject pointer to the creature object of the player who got the old man spawned.
-- @return the id of the old man stored on the player.
function OldManPrivate.readOldManIdFromPlayer(pCreatureObject)
	return OldManPrivate.readTransientDataFromThePlayer(pCreatureObject, OLD_MAN_ID_STRING)
end

-- Write persistent data to the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param key the key to write the value to.
-- @param value the value to write.
function OldManPrivate.setScreenPlayStateOnPlayer(pCreatureObject, key, value)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:setScreenPlayState(value, key)
	end)
end

-- Clear persistent data to the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param key the key to clear the value in.
-- @param value the value to clear.
function OldManPrivate.removeScreenPlayStateOnPlayer(pCreatureObject, key, value)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:removeScreenPlayState(value, key)
	end)
end

-- Write transient data to the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param key the key to write the value to.
-- @param value the value to write.
function OldManPrivate.writeTransientDataToThePlayer(pCreatureObject, key, value)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		writeData(creatureObject:getObjectID() .. key, value)
	end)
end

-- Save the id of the old man to only enable the old man for the player he was spawned for.
-- @param pCreatureObject pointer to the creature object of the player who got the old man spawned.
-- @param pOldMan pointer to the creature object of the spawned old man.
function OldManPrivate.saveOldManIdOnPlayer(pCreatureObject, pOldMan)
	ObjectManager.withCreatureObject(pOldMan, function(oldManCreatureObject)
		OldManPrivate.writeTransientDataToThePlayer(pCreatureObject, OLD_MAN_ID_STRING, oldManCreatureObject:getObjectID())
	end)
end

-- Check if the player is online.
-- @param pCreatureObject pointer to the creature object of the player who should be checked if online.
-- @return true if the player is online.
function OldManPrivate.isPlayerOnline(pCreatureObject)
	return ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		return playerObject:isOnline()
	end) == true
end

-- Check if the player is in a building or not.
-- @param pCreatureObject pointer to the creature object of the player that should be checked for being in a building or not.
-- @return true if the player is in a building.
function OldManPrivate.isPlayerInABuilding(pCreatureObject)
	return ObjectManager.withSceneObject(pCreatureObject, function(sceneObject)
		return not (sceneObject:getParentID() == NOTINABUILDING)
	end) == true
end

-- Check if the player is in a NPC city.
-- @param pCreatureObject pointer to the creature object of the player who should be checked for being in a NPC city.
-- return true if the player is within a NPC city.
function OldManPrivate.isPlayerInNpcCity(pCreatureObject)
	return ObjectManager.withSceneObject(pCreatureObject, function(sceneObject)
		local pCityRegion = getCityRegionAt(sceneObject:getZoneName(), sceneObject:getWorldPositionX(), sceneObject:getWorldPositionY())
		local inNpcCity = ObjectManager.withCityRegion(pCityRegion, function(cityRegion)
			return not cityRegion:isClientRegion()
		end)
		return inNpcCity == true
	end) == true
end

-- Check if the player is in a postion where the old man can be spawned.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the player is in a position where the old man can be spawned.
function OldManPrivate.canOldManBeSpawned(pCreatureObject)
	return (OldManPrivate.isPlayerOnline(pCreatureObject) and not OldManPrivate.isPlayerInABuilding(pCreatureObject) and not OldManPrivate.isPlayerInNpcCity(pCreatureObject))
end

-- Set a creature to follow another creature.
-- @param pCreatureObject pointer to the creature who should follow another creature.
-- @param pFollowObject pointer to the creature object of the creature to follow.
function OldManPrivate.setToFollow(pCreatureObject, pFollowObject)
	ObjectManager.withCreatureAiAgent(pCreatureObject, function(aiAgent)
		aiAgent:setFollowObject(pFollowObject)
	end)
end

-- Function to handle the stop follow player event for the old man.
-- @param pCreatureObject pointer to the creature object of the player who got an old man that should stop following.
function OldManPublicEventsAndObservers:handleStopFollowPlayerEvent(pCreatureObject)
	local oldManId = OldManPrivate.readOldManIdFromPlayer(pCreatureObject)
	local pOldMan = getSceneObject(oldManId)
	OldManPrivate.setToFollow(pOldMan, nil)
end

-- Get the first name of the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return the first name of the player.
function OldManPrivate.getPlayerFirstName(pCreatureObject)
	local firstName = ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
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
function OldManPrivate.sendGreetingString(pOldMan, pCreatureObject)
	local greetingString = LuaStringIdChatParameter(OLD_MAN_GREETING_STRING)
	local firstName = OldManPrivate.getPlayerFirstName(pCreatureObject)
	greetingString:setTT(firstName)
	spatialChat(pOldMan, greetingString:_getObject())
end

-- Function to handle the spatial chat event for the old man.
-- @param pCreatureObject pointer to the creature object of the player who got an old man that should say something in spatial chat.
function OldManPublicEventsAndObservers:handleSpatialChatEvent(pCreatureObject)
	local oldManId = OldManPrivate.readOldManIdFromPlayer(pCreatureObject)
	local pOldMan = getSceneObject(oldManId)
	OldManPrivate.sendGreetingString(pOldMan, pCreatureObject)
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.OLD_MAN_INITIAL)
end

-- Despawn the old man.
-- @param pointer to the creature object of the old man.
function OldManPrivate.despawnOldMan(pOldMan)
	ObjectManager.withSceneObject(pOldMan, function(sceneObject)
		sceneObject:destroyObjectFromWorld()
	end)
end

-- Function to handle the despawn of the old man.
-- @param pCreatureObject pointer to the creature object of the player whos old man should despawn.
function OldManPublicEventsAndObservers:handleDespawnEvent(pCreatureObject)
	local oldManId = OldManPrivate.readOldManIdFromPlayer(pCreatureObject)
	local pOldMan = getSceneObject(oldManId)
	OldManPrivate.despawnOldMan(pOldMan)
	OldManPrivate.writeTransientDataToThePlayer(pCreatureObject, OLD_MAN_ID_STRING, OLD_MAN_NO_OLD_MAN_SPAWNED)
	OldMan.createSpawnOldManEvent(pCreatureObject)
end

-- Schedule despawn of the old man.
-- @param pCreatureObject pointer to the creature object of the player whos old man should be despawned.
-- @param time time until the old man should despawn.
function OldMan.scheduleDespawnOfOldMan(pCreatureObject, time)
	createEvent(time, "OldManPublicEventsAndObservers", "handleDespawnEvent", pCreatureObject)
end

-- Try to spawn the old man and create the needed events.
-- @param pCreatureObject pointer to the creature object of the player who should get the old man spawned.
-- @return true if everything were successful.
function OldManPrivate.tryToSpawnOldMan(pCreatureObject)
	local pOldMan = OldManPrivate.spawnOldMan(pCreatureObject)
	if pOldMan ~= nil then
		OldManPrivate.saveOldManIdOnPlayer(pCreatureObject, pOldMan)
		OldManPrivate.setToFollow(pOldMan, pCreatureObject)
		createEvent(OLD_MAN_STOP_FOLLOW_TIME, "OldManPublicEventsAndObservers", "handleStopFollowPlayerEvent", pCreatureObject)
		createEvent(OLD_MAN_SPATIAL_CHAT_TIME, "OldManPublicEventsAndObservers", "handleSpatialChatEvent", pCreatureObject)
		OldMan.scheduleDespawnOfOldMan(pCreatureObject, OLD_MAN_DESPAWN_TIME)
		return true
	else
		return false
	end
end

-- Function to handle the old man event.
-- @param pCreatureObject pointer to the creature object who should have an event created for spawning the old man.
function OldManPublicEventsAndObservers:handleSpawnOldManEvent(pCreatureObject)
	OldManPrivate.removeScreenPlayStateOnPlayer(pCreatureObject, OLD_MAN_EVENT_SCHEDULED_STRING, OLD_MAN_SCHEDULED)
	if OldManPrivate.canOldManBeSpawned(pCreatureObject) then
		if not OldManPrivate.tryToSpawnOldMan(pCreatureObject) then
			OldMan.createSpawnOldManEvent(pCreatureObject)
		end
	else
		OldMan.createSpawnOldManEvent(pCreatureObject)
	end
end

-- Check if an event has already been scheduled for spawning the old man for this player.
-- @param pCreatureObject pointer to the creature object of the player.
-- return true if an event is already scheduled.
function OldManPrivate.hasOldManSpawnEventScheduled(pCreatureObject)
	return OldManPrivate.getScreenPlayStateFromPlayer(pCreatureObject, OLD_MAN_EVENT_SCHEDULED_STRING) == OLD_MAN_SCHEDULED
end

-- Check if the spawn event should be created.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the spawn event should be created.
function OldManPrivate.shouldSpawnOldManEventBeCreated(pCreatureObject)
	local eventNotScheduled = not OldManPrivate.hasOldManSpawnEventScheduled(pCreatureObject)
	local oldManNotSpawned = OldManPrivate.readOldManIdFromPlayer(pCreatureObject) == OLD_MAN_NO_OLD_MAN_SPAWNED
	local doesNotHaveCrystal = not VillageJediManagerCommon.hasJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL)
	return eventNotScheduled and oldManNotSpawned and doesNotHaveCrystal
end

-- Generate an event to spawn the old man for the player.
-- @param pCreatureObject pointer to the creature object who should have an event created for spawning the old man.
function OldMan.createSpawnOldManEvent(pCreatureObject)
	if OldManPrivate.shouldSpawnOldManEventBeCreated(pCreatureObject) then
		OldManPrivate.setScreenPlayStateOnPlayer(pCreatureObject, OLD_MAN_EVENT_SCHEDULED_STRING, OLD_MAN_SCHEDULED)
		local time = OLD_MAN_SPAWN_TIME + math.random(OLD_MAN_SPAWN_TIME)
		createEvent(true, time, "OldManPublicEventsAndObservers", "handleSpawnOldManEvent", pCreatureObject)
	end
end

-- Check if the old man belongs to the player or not.
-- @param pConversingPlayer pointer to the creature object of the conversing player.
-- @param pConversingNpc pointer to the creature object of the old man.
-- @return true if the old man belongs to the player.
function OldMan.oldManBelongsToThePlayer(pConversingPlayer, pConversingNpc)
	return ObjectManager.withCreatureObject(pConversingNpc, function(oldManCreatureObject)
		return OldManPrivate.readOldManIdFromPlayer(pConversingPlayer) == oldManCreatureObject:getObjectID()
	end) == true
end

-- Give the force crystal to the player.
-- @param pCreatureObject pointer to the creature object of the player.
function OldMan.giveForceCrystalToPlayer(pCreatureObject)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		local pInventory = creatureObject:getSlottedObject(OLD_MAN_INVENTORY_STRING)

		if pInventory ~= nil then
			giveItem(pInventory, OLD_MAN_FORCE_CRYSTAL_STRING, -1)
			VillageJediManagerCommon.setJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL)
			QuestManager.completeQuest(pCreatureObject, QuestManager.quests.OLD_MAN_INITIAL)
			QuestManager.completeQuest(pCreatureObject, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)
		end
	end)
end

return OldMan
