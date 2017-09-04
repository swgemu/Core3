local QuestManager = require("managers.quest.quest_manager")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
local Logger = require("utils.logger")

SITH_SHADOW_THREATEN_STRING = "@quest/force_sensitive/intro:military_threaten"
SITH_SHADOW_MILITARY_TAKE_CRYSTAL = "@quest/force_sensitive/intro:military_take_crystal"
local READ_DISK_1_STRING = "@quest/force_sensitive/intro:read_disk1"
local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"

SithShadowEncounter = Encounter:new {
	-- Task properties
	taskName = "SithShadowEncounter",
	-- Encounter properties
	encounterDespawnTime = 2 * 60 * 1000, -- 2 minutes
	spawnObjectList = {
		{ template = "sith_shadow_outlaw_mission", minimumDistance = 64, maximumDistance = 96, referencePoint = 0, followPlayer = true, setNotAttackable = false, runOnDespawn = true },
		{ template = "sith_shadow_outlaw_mission", minimumDistance = 4, maximumDistance = 8, referencePoint = 1, followPlayer = true, setNotAttackable = false, runOnDespawn = true }
	},
	onEncounterSpawned = nil,
	isEncounterFinished = nil,
	onEncounterInRange = nil,
	inRangeValue = 26,
}

-- Check if the sith shadow is the first one spawned for the player.
-- @param pSithShadow pointer to the sith shadow.
-- @param pPlayer pointer to the creature object of the player.
-- @return true if the sith shadow is the first one spawned for the player.
function SithShadowEncounter:isTheFirstSithShadowOfThePlayer(pSithShadow, pPlayer)
	local spawnedSithShadows = SpawnMobiles.getSpawnedMobiles(pPlayer, self.taskName)

	return spawnedSithShadows ~= nil and spawnedSithShadows[1] ~= nil and CreatureObject(spawnedSithShadows[1]):getObjectID() == CreatureObject(pSithShadow):getObjectID()
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
	if QuestManager.hasActiveQuest(pLooter, QuestManager.quests.TWO_MILITARY) then
		if self:isTheFirstSithShadowOfThePlayer(pLootedCreature, pLooter) then
			QuestManager.completeQuest(pLooter, QuestManager.quests.TWO_MILITARY)
			QuestManager.completeQuest(pLooter, QuestManager.quests.GOT_DATAPAD)
			return 1
		end
	end

	return 0
end

-- Handle the event PLAYERKILLED.
-- @param pPlayer pointer to the creature object of the killed player.
-- @param pKiller pointer to the creature object of the killer.
-- @param noting unused variable for the default footprint of event handlers.
-- @return 1 if the player was killed by one of the sith shadows, otherwise 0 to keep the observer.
function SithShadowEncounter:onPlayerKilled(pPlayer, pKiller, nothing)
	if (pPlayer == nil or pKiller == nil) then
		return 0
	end

	Logger:log("Player was killed.", LT_INFO)
	if SpawnMobiles.isFromSpawn(pPlayer, SithShadowEncounter.taskName, pKiller) then
		spatialChat(pKiller, SITH_SHADOW_MILITARY_TAKE_CRYSTAL)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.TWO_MILITARY)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_1)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.GOT_DATAPAD)
		OldManIntroEncounter:removeForceCrystalFromPlayer(pPlayer)
		createEvent(10 * 1000, "SithShadowEncounter", "handleDespawnEvent", pPlayer, "")
		return 1
	end

	return 0
end

-- Handling of the encounter spawned event.
-- Register observer for looting one of the sith shadows.
-- @param pPlayer pointer to the creature object of the player who has this encounter.
-- @param spawnedObject list of pointers to the spawned sith shadows.
function SithShadowEncounter:onEncounterSpawned(pPlayer, spawnedObjects)
	if (pPlayer == nil or spawnedObjects == nil or spawnedObjects[1] == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local pInventory = SceneObject(spawnedObjects[1]):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	SceneObject(pInventory):setContainerOwnerID(playerID)
	createLoot(pInventory, "sith_shadow_encounter_datapad", 0, true)

	createObserver(LOOTCREATURE, self.taskName, "onLoot", spawnedObjects[1])
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pPlayer)
	FsIntro:setCurrentStep(pPlayer, 4)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.TWO_MILITARY)
end

-- Handling of the encounter in range event.
-- Send a spatial chat from the first sith shadow.
-- @param pPlayer pointer to the creature object of the player who has this encounter.
-- @param spawnedObjects list of pointers to the spawned sith shadows.
function SithShadowEncounter:onEncounterInRange(pPlayer, spawnedObjects)
	if (pPlayer == nil or spawnedObjects == nil or spawnedObjects[1] == nil) then
		return
	end

	Logger:log("Sending threaten string.", LT_INFO)
	local threatenString = LuaStringIdChatParameter(SITH_SHADOW_THREATEN_STRING)
	threatenString:setTT(CreatureObject(pPlayer):getFirstName())
	spatialChat(spawnedObjects[1], threatenString:_getObject())
	QuestManager.activateQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_1)

	foreach(spawnedObjects, function(pMobile)
		if (pMobile ~= nil) then
			AiAgent(pMobile):setDefender(pPlayer)
		end
	end)
end

-- Check if the sith shadow encounter is finished or not.
-- @param pPlayer pointer to the creature object of the player.
-- @return true if the encounter is finished. I.e. the player has access to the village or lost the crystal.
function SithShadowEncounter:isEncounterFinished(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return not OldManIntroEncounter:hasForceCrystal(pPlayer) or QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.GOT_DATAPAD)
end

-- Handling of the activation of the looted datapad.
-- @param pSceneObject pointer to the datapad object.
-- @param pPlayer pointer to the creature object who activated the datapad.
function SithShadowEncounter:useWaypointDatapad(pSceneObject, pPlayer)
	Logger:log("Player used the looted waypoint datapad.", LT_INFO)
	if QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.GOT_DATAPAD) then

		SithShadowIntroTheater:start(pPlayer)

		CreatureObject(pPlayer):sendSystemMessage(READ_DISK_1_STRING)

		SceneObject(pSceneObject):destroyObjectFromWorld()
		SceneObject(pSceneObject):destroyObjectFromDatabase()
		QuestManager.completeQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_1)
		FsIntro:setCurrentStep(pPlayer, 6)
	else
		CreatureObject(pPlayer):sendSystemMessage(READ_DISK_ERROR_STRING)
	end
end

function SithShadowEncounter:taskFinish(pPlayer)
	if (pPlayer == nil) then
		return true
	end

	if (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.GOT_DATAPAD) and FsIntro:getCurrentStep(pPlayer) == 4) then
		FsIntro:setCurrentStep(pPlayer, 5)
	elseif not OldManIntroEncounter:hasForceCrystal(pPlayer) then
		FsIntro:startStepDelay(pPlayer, 1)
	end

	return true
end

return SithShadowEncounter
