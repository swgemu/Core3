local Encounter = require("quest.tasks.encounter")
local QuestManager = require("managers.quest.quest_manager")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
local Logger = require("utils.logger")

SithShadowEncounter = Encounter:new {
	-- Task properties
	taskName = "SithShadowEncounter",
	-- Encounter properties
	--minimumTimeUntilEncounter = 12 * 60 * 60 * 1000, -- 12 hours
	--maximumTimeUntilEncounter = 24 * 60 * 60 * 1000, -- 24 hours
	minimumTimeUntilEncounter = 30 * 1000, -- 12 hours
	maximumTimeUntilEncounter = 60 * 1000, -- 24 hours
	--encounterDespawnTime = 5 * 60 * 1000, -- 5 minutes
	encounterDespawnTime = 60 * 1000, -- 5 minutes
	spawnObjectList = {
		{ template = "sith_shadow", minimumDistance = 64, maximumDistance = 96, referencePoint = 0, followPlayer = true },
		{ template = "sith_shadow", minimumDistance = 4, maximumDistance = 8, referencePoint = 1, followPlayer = true }
	},
	onEncounterSpawned = nil,
	isEncounterFinished = nil,
	onEncounterClosingIn = nil,
	onEncounterAtPlayer = nil
}

-- Check if the sith shadow is the first one spawned for the player.
-- @param pSithShadow pointer to the sith shadow.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the sith shadow is the first one spawned for the player.
function SithShadowEncounter:isTheFirstSithShadowOfThePlayer(pSithShadow, pCreatureObject)
	local spawnedSithShadows = SpawnMobiles.getSpawnedMobiles(pCreatureObject, self.taskName)

	if spawnedSithShadows ~= nil then
		return ObjectManager.withCreatureObject(spawnedSithShadows[1], function(sithShadowInList)
			return ObjectManager.withCreatureObject(pSithShadow, function(sithShadow)
				return sithShadowInList:getObjectID() == sithShadow:getObjectID()
			end) == true
		end) == true
	else
		return false
	end
end

-- Create the waypoint data pad as loot on the sith shadow.
-- @param pSithShadow pointer to the creature object of the sith shadow.
function SithShadowEncounter:addWaypointDatapadAsLoot(pSithShadow)
	ObjectManager.withInventoryPointer(pSithShadow, function(pInventory)
		createLoot(pInventory, "sith_shadow_encounter_datapad", 0, true)
	end)
end

-- Event handler for the LOOTCREATURE event on one of the sith shadows.
-- @param pLootedCreature pointer to the sith shadow creature that is being looted.
-- @param pLooter pointer to the creature object of the looter.
-- @param nothing unused variable for the default footprint of event handlers.
-- @return 1 if the correct player looted the creature to remove the observer, 0 otherwise to keep the observer.
function SithShadowEncounter:onLoot(pLootedCreature, pLooter, nothing)
	Logger:log("Looting the sith shadow.", LT_INFO)
	if self:isTheFirstSithShadowOfThePlayer(pLootedCreature, pLooter) then
		self:addWaypointDatapadAsLoot(pLootedCreature)
		return 1
	end

	return 0
end

-- Handle the event PLAYERKILLED.
-- @param pCreatureObject pointer to the creature object of the killed player.
-- @param pKiller pointer to the creature object of the killer.
-- @param noting unused variable for the default footprint of event handlers.
-- @return 1 if the player was killed by one of the sith shadows, otherwise 0 to keep the observer.
function SithShadowEncounter:onPlayerKilled(pCreatureObject, pKiller, nothing)
	Logger:log("Player was killed.", LT_INFO)
	if SpawnMobiles.isFromSpawn(pCreatureObject, SithShadowEncounter.taskName, pKiller) then
		OldManEncounter:removeForceCrystalFromPlayer(pCreatureObject)
		OldManEncounter:start(pCreatureObject)
		return 1
	end

	return 0
end

-- Handling of the encounter spawned event.
-- Register observer for looting one of the sith shadows.
-- @param pCreatureObject pointer to the creature object of the player who has this encounter.
-- @param spawnedObject list of pointers to the spawned sith shadows.
function SithShadowEncounter:onEncounterSpawned(pCreatureObject, spawnedObjects)
	Logger:log("Register Sith Shadow Encounter observers.", LT_INFO)
	createObserver(LOOTCREATURE, self.taskName, "onLoot", spawnedObjects[1])
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pCreatureObject)
end

-- Check if the sith shadow encounter is finished or not.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the encounter is finished. I.e. the player has access to the village or lost the crystal.
function SithShadowEncounter:isEncounterFinished(pCreatureObject)
	return not QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)
end

return SithShadowEncounter
