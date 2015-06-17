local GoToTheater = require("quest.tasks.go_to_theater")
local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
require("utils.helpers")
local GoToDathomir = require("managers.jedi.village.intro.go_to_dathomir")
local READ_DISK_2_STRING = "@quest/force_sensitive/intro:read_disk2"
local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"

SithShadowIntroTheater = GoToTheater:new {
	-- Task properties
	taskName = "SithShadowIntroTheater",
	-- GoToTheater properties
	minimumDistance = 1024,
	maximumDistance = 1536,
	theater = "object/building/poi/anywhere_fs_intro_camp.iff",
	waypointDescription = "@quest/force_sensitive/intro:theater_sum",
	mobileList = {
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 }
	},
	despawnTime = 2 * 60* 60* 1000, -- 2 hours
	activeAreaRadius = 64,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil
}

-- Check if the sith shadow is the first one spawned for the player.
-- @param pSithShadow pointer to the sith shadow.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the sith shadow is the first one spawned for the player.
function SithShadowIntroTheater:isTheFirstSithShadowOfThePlayer(pSithShadow, pCreatureObject)
	local spawnedSithShadows = self:getSpawnedMobileList(pCreatureObject)

	if spawnedSithShadows ~= nil and spawnedSithShadows[1] ~= nil then
		return CreatureObject(spawnedSithShadows[1]):getObjectID() == CreatureObject(pSithShadow):getObjectID()
	else
		return false
	end
end

-- Create the waypoint datapad as loot on the sith shadow.
-- @param pSithShadow pointer to the creature object of the sith shadow.
function SithShadowIntroTheater:addWaypointDatapadAsLoot(pSithShadow)
	local pInventory = SceneObject(pSithShadow):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	createLoot(pInventory, "sith_shadow_intro_theater_datapad", 0, true)
end

-- Event handler for the LOOTCREATURE event on one of the sith shadows.
-- @param pLootedCreature pointer to the sith shadow creature that is being looted.
-- @param pLooter pointer to the creature object of the looter.
-- @param nothing unused variable for the default footprint of event handlers.
-- @return 1 if the correct player looted the creature to remove the observer, 0 otherwise to keep the observer.
function SithShadowIntroTheater:onLoot(pLootedCreature, pLooter, nothing)
	if (pLootedCreature == nil or pLooter == nil) then
		return 0
	end

	Logger:log("Looting the sith shadow.", LT_INFO)
	if QuestManager.hasActiveQuest(pLooter, QuestManager.quests.FS_THEATER_CAMP) then
		if self:isTheFirstSithShadowOfThePlayer(pLootedCreature, pLooter) then
			self:addWaypointDatapadAsLoot(pLootedCreature)
			QuestManager.completeQuest(pLooter, QuestManager.quests.FS_THEATER_CAMP)
			QuestManager.completeQuest(pLooter, QuestManager.quests.GOT_DATAPAD_2)
			return 1
		end
	end

	return 0
end

-- Event handler for the enter active area event.
-- The event will cause all spawned Sith Shadows to attack the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param spawnedSithShadowsList list with pointers to the spawned sith shadows.
function SithShadowIntroTheater:onEnteredActiveArea(pCreatureObject, spawnedSithShadowsList)
	if (pCreatureObject == nil or spawnedSithShadowsList == nil) then
		return
	end

	foreach(spawnedSithShadowsList, function(pMobile)
		if (pMobile ~= nil) then
			AiAgent(pMobile):setFollowObject(pCreatureObject)
		end
	end)
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.LOOT_DATAPAD_2)
end

-- Event handler for the successful spawn event.
-- The event will activate the FS_THEATER_CAMP quest for the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param spawnedSithShadowsList list with pointers to the spawned sith shadows.
function SithShadowIntroTheater:onSuccessfulSpawn(pCreatureObject, spawnedSithShadowsList)
	if (pCreatureObject == nil or spawnedSithShadowsList == nil or spawnedSithShadowsList[1] == nil) then
		return
	end

	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_THEATER_CAMP)
	createObserver(LOOTCREATURE, self.taskName, "onLoot", spawnedSithShadowsList[1])
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pCreatureObject)
end

-- Handle the event PLAYERKILLED.
-- @param pCreatureObject pointer to the creature object of the killed player.
-- @param pKiller pointer to the creature object of the killer.
-- @param noting unused variable for the default footprint of event handlers.
-- @return 1 if the player was killed by one of the sith shadows, otherwise 0 to keep the observer.
function SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pKiller, nothing)
	if (pCreatureObject == nil or pKiller == nil) then
		return 0
	end

	Logger:log("Player was killed.", LT_INFO)
	if SpawnMobiles.isFromSpawn(pCreatureObject, SithShadowIntroTheater.taskName, pKiller) then
		OldManEncounter:removeForceCrystalFromPlayer(pCreatureObject)
		spatialChat(pKiller, SITH_SHADOW_MILITARY_TAKE_CRYSTAL)
		OldManEncounter:start(pCreatureObject)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.TWO_MILITARY)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.LOOT_DATAPAD_1)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.GOT_DATAPAD_1)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.FS_THEATER_CAMP)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.LOOT_DATAPAD_2)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.GOT_DATAPAD_2)
		return 1
	end

	return 0
end

-- Handling of the activation of the theater waypoint datapad.
-- @param pSceneObject pointer to the datapad object.
-- @param pCreatureObject pointer to the creature object who activated the datapad.
function SithShadowIntroTheater:useTheaterDatapad(pSceneObject, pCreatureObject)
	Logger:log("Player used the looted theater datapad.", LT_INFO)
	if QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.GOT_DATAPAD_2) then
		CreatureObject(pCreatureObject):sendSystemMessage(READ_DISK_2_STRING)

		SceneObject(pSceneObject):destroyObjectFromWorld()
		SceneObject(pSceneObject):destroyObjectFromDatabase()

		QuestManager.completeQuest(pCreatureObject, QuestManager.quests.LOOT_DATAPAD_2)
		GoToDathomir:start(pCreatureObject)
	else
		CreatureObject(pCreatureObject):sendSystemMessage(READ_DISK_ERROR_STRING)
	end
end

return SithShadowIntroTheater
