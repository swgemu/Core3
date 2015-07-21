local Encounter = require("quest.tasks.encounter")
local QuestManager = require("managers.quest.quest_manager")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
local Logger = require("utils.logger")
local SithShadowIntroTheater = require("managers.jedi.village.intro.sith_shadow_intro_theater")

SITH_SHADOW_THREATEN_STRING = "@quest/force_sensitive/intro:military_threaten"
SITH_SHADOW_MILITARY_TAKE_CRYSTAL = "@quest/force_sensitive/intro:military_take_crystal"
local READ_DISK_1_STRING = "@quest/force_sensitive/intro:read_disk1"
local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"

SithShadowEncounter = Encounter:new {
	-- Task properties
	taskName = "SithShadowEncounter",
	-- Encounter properties
	--minimumTimeUntilEncounter = 12 * 60 * 60 * 1000, -- 12 hours
	--maximumTimeUntilEncounter = 24 * 60 * 60 * 1000, -- 24 hours
	minimumTimeUntilEncounter = 1 * 60 * 1000, -- 12 hours
	maximumTimeUntilEncounter = 1 * 60 * 1000, -- 24 hours
	--encounterDespawnTime = 5 * 60 * 1000, -- 5 minutes
	encounterDespawnTime = 5 * 60 * 1000, -- 5 minutes
	spawnObjectList = {
		{ template = "sith_shadow", minimumDistance = 64, maximumDistance = 96, referencePoint = 0, followPlayer = true, setNotAttackable = false },
		{ template = "sith_shadow", minimumDistance = 4, maximumDistance = 8, referencePoint = 1, followPlayer = true, setNotAttackable = false }
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

	if spawnedSithShadows ~= nil and spawnedSithShadows[1] ~= nil then
		return CreatureObject(spawnedSithShadows[1]):getObjectID() == CreatureObject(pSithShadow):getObjectID()
	else
		return false
	end
end

-- Create the waypoint data pad as loot on the sith shadow.
-- @param pSithShadow pointer to the creature object of the sith shadow.
function SithShadowEncounter:addWaypointDatapadAsLoot(pSithShadow)
	local pInventory = SceneObject(pSithShadow):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	createLoot(pInventory, "sith_shadow_encounter_datapad", 0, true)
end

-- Event handler for the LOOTCREATURE event on one of the sith shadows.
-- @param pLootedCreature pointer to the sith shadow creature that is being looted.
-- @param pLooter pointer to the creature object of the looter.
-- @param nothing unused variable for the default footprint of event handlers.
-- @return 1 if the correct player looted the creature to remove the observer, 0 otherwise to keep the observer.
function SithShadowEncounter:onLoot(pLootedCreature, pLooter, nothing)
	if (pLootedCreature == nil or pLooter == nil) then
		return 0
	end

	Logger:log("Looting the sith shadow.", LT_INFO)
	if QuestManager.hasActiveQuest(pLooter, QuestManager.quests.TwO_MILITARY) then
		if self:isTheFirstSithShadowOfThePlayer(pLootedCreature, pLooter) then
			self:addWaypointDatapadAsLoot(pLootedCreature)
			QuestManager.completeQuest(pLooter, QuestManager.quests.TwO_MILITARY)
			QuestManager.completeQuest(pLooter, QuestManager.quests.GOT_DATAPAD)
			CreatureObject(pLooter):sendSystemMessage("@quest/quests:quest_journal_updated")
			return 1
		end
	end

	return 0
end

-- Handle the event PLAYERKILLED.
-- @param pCreatureObject pointer to the creature object of the killed player.
-- @param pKiller pointer to the creature object of the killer.
-- @param noting unused variable for the default footprint of event handlers.
-- @return 1 if the player was killed by one of the sith shadows, otherwise 0 to keep the observer.
function SithShadowEncounter:onPlayerKilled(pCreatureObject, pKiller, nothing)
	if (pCreatureObject == nil or pKiller == nil) then
		return 0
	end

	Logger:log("Player was killed.", LT_INFO)
	if SpawnMobiles.isFromSpawn(pCreatureObject, SithShadowEncounter.taskName, pKiller) then
		OldManEncounter:removeForceCrystalFromPlayer(pCreatureObject)
		spatialChat(pKiller, SITH_SHADOW_MILITARY_TAKE_CRYSTAL)
		OldManEncounter:start(pCreatureObject)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.TwO_MILITARY)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.LOOT_DATAPAD_1)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.GOT_DATAPAD)

		CreatureObject(pCreatureObject):sendSystemMessage("@quest/quests:task_failure")
		CreatureObject(pCreatureObject):sendSystemMessage("@quest/quests:quest_journal_updated")
		return 1
	end

	return 0
end

-- Handling of the encounter spawned event.
-- Register observer for looting one of the sith shadows.
-- @param pCreatureObject pointer to the creature object of the player who has this encounter.
-- @param spawnedObject list of pointers to the spawned sith shadows.
function SithShadowEncounter:onEncounterSpawned(pCreatureObject, spawnedObjects)
	if (pCreatureObject == nil or spawnedObjects == nil or spawnedObjects[1] == nil) then
		return
	end

	Logger:log("Register Sith Shadow Encounter observers.", LT_INFO)
	createObserver(LOOTCREATURE, self.taskName, "onLoot", spawnedObjects[1])
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pCreatureObject)
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.TwO_MILITARY)
end

-- Handling of the encounter closing in event.
-- Send a spatial chat from the first sith shadow.
-- @param pCreatureObject pointer to the creature object of the player who has this encounter.
-- @param spawnedObjects list of pointers to the spawned sith shadows.
function SithShadowEncounter:onEncounterClosingIn(pCreatureObject, spawnedObjects)
	if (pCreatureObject == nil or spawnedObjects == nil or spawnedObjects[1] == nil) then
		return
	end

	Logger:log("Sending threaten string.", LT_INFO)
	local threatenString = LuaStringIdChatParameter(SITH_SHADOW_THREATEN_STRING)
	threatenString:setTT(CreatureObject(pCreatureObject):getFirstName())
	spatialChat(spawnedObjects[1], threatenString:_getObject())
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.LOOT_DATAPAD_1)
	
	foreach(spawnedObjects, function(pMobile)
		if (pMobile ~= nil) then
			AiAgent(pMobile):setDefender(pCreatureObject)
		end
	end)
end

-- Check if the sith shadow encounter is finished or not.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the encounter is finished. I.e. the player has access to the village or lost the crystal.
function SithShadowEncounter:isEncounterFinished(pCreatureObject)
	if (pCreatureObject == nil) then
		return false
	end

	return QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.GOT_DATAPAD)
end

-- Handling of the activation of the looted datapad.
-- @param pSceneObject pointer to the datapad object.
-- @param pCreatureObject pointer to the creature object who activated the datapad.
function SithShadowEncounter:useWaypointDatapad(pSceneObject, pCreatureObject)
	Logger:log("Player used the looted waypoint datapad.", LT_INFO)
	if QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.GOT_DATAPAD) then
		SithShadowIntroTheater:start(pCreatureObject)

		CreatureObject(pCreatureObject):sendSystemMessage(READ_DISK_1_STRING)

		SceneObject(pSceneObject):destroyObjectFromWorld()
		SceneObject(pSceneObject):destroyObjectFromDatabase()
		QuestManager.completeQuest(pCreatureObject, QuestManager.quests.LOOT_DATAPAD_1)
	else
		CreatureObject(pCreatureObject):sendSystemMessage(READ_DISK_ERROR_STRING)
	end
end

return SithShadowEncounter
