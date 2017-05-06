local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
require("utils.helpers")
local READ_DISK_2_STRING = "@quest/force_sensitive/intro:read_disk2"
local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"

SithShadowIntroTheater = GoToTheater:new {
	-- Task properties
	taskName = "SithShadowIntroTheater",
	-- GoToTheater properties
	minimumDistance = 1024,
	maximumDistance = 1536,
	theater = {
		{ template = "object/tangible/furniture/all/frn_all_light_lamp_table_s03.iff", xDiff =0.52, zDiff = 1.14, yDiff = -3.37, heading = 0 },
		{ template = "object/tangible/camp/camp_crate_s1.iff", xDiff =-3.78,zDiff = 0, yDiff = 0.91, heading = -18.91 },
		{ template = "object/weapon/ranged/pistol/pistol_dl44_metal.iff", xDiff =0.13, zDiff = 1.17, yDiff = -2.9, heading = -9.74 },
		{ template = "object/tangible/camp/camp_crate_s1.iff", xDiff =1.74, zDiff = 0, yDiff = -2.84, heading = -80.214 },
		{ template = "object/static/structure/general/camp_lawn_chair_s01.iff", xDiff =3.74, zDiff = 0, yDiff = 2.42, heading = -47.74 },
		{ template = "object/static/structure/general/camp_lawn_chair_s01.iff", xDiff =2.04, zDiff = 0, yDiff = 1.55, heading = 0.39 },
		{ template = "object/static/structure/general/camp_lawn_chair_s01.iff", xDiff =-0.26, zDiff = 0, yDiff = 5.28, heading = 111.15 },
		{ template = "object/static/structure/general/campfire_fresh.iff", xDiff =2.30, zDiff = 0, yDiff = 4.01, heading = 0 },
		{ template = "object/static/structure/general/camp_spit_s01.iff", xDiff =1.72, zDiff = 0, yDiff = 3.92, heading = 83.59 },
		{ template = "object/static/structure/general/camp_spit_s01.iff", xDiff =2.76, zDiff = 0, yDiff = 4.21, heading = 63.79 },
		{ template = "object/static/structure/general/camp_spit_s01.iff", xDiff =2.33, zDiff = 0, yDiff = 3.3, heading = -24.13 },
		{ template = "object/static/structure/general/trash_pile_s01.iff", xDiff =-3.48, zDiff = 0, yDiff = 2.61, heading = -120.3 },
		{ template = "object/static/structure/tatooine/debris_tatt_crate_1.iff", xDiff =1.78, zDiff = 0, yDiff = -2.7, heading = 7.45 },
		{ template = "object/static/structure/tatooine/debris_tatt_drum_dented_1.iff", xDiff =1.61, zDiff = 0, yDiff = -3.92, heading = -82.51 },
		{ template = "object/static/structure/tatooine/debris_tatt_crate_metal_1.iff", xDiff =-2.18, zDiff = 0, yDiff = 1.27, heading = -12.03 },
		{ template = "object/static/structure/general/camp_cot_s01.iff", xDiff =-1.2, zDiff = 0, yDiff = -4.84, heading = -20.05 },
		{ template = "object/static/structure/tatooine/tent_house_tatooine_style_01.iff", xDiff =-2.46, zDiff = 0, yDiff = -2.15, heading = -140.38 },
		{ template = "object/static/structure/tatooine/debris_tatt_drum_dented_1.iff", xDiff =0.32, zDiff = 0, yDiff = -3.04, heading = 9.74 },
		{ template = "object/static/structure/general/trash_pile_s01.iff", xDiff =-3.64, zDiff = 0, yDiff = 2.997, heading = 156.99 },
		{ template = "object/static/structure/tatooine/debris_tatt_crate_1.iff", xDiff =-2.3, zDiff = 0, yDiff = 1.28, heading = -110.58 },
		{ template = "object/static/structure/general/camp_cot_s01.iff", xDiff =-4.51, zDiff = 0, yDiff = -4.41, heading = 39.53 },
		{ template = "object/static/structure/general/camp_cot_s01.iff", xDiff =-5.42, zDiff = 0, yDiff = -1.45, heading = 99.69 },
		{ template = "object/static/structure/tatooine/debris_tatt_crate_metal_1.iff", xDiff =1.92, zDiff = 0, yDiff = -1.88, heading = -12.03 },
		{ template = "object/static/item/item_container_organic_food.iff", xDiff =-3.13, zDiff = 0, yDiff = 1.086, heading = 137.69 },
	},
	waypointDescription = "@quest/force_sensitive/intro:theater_sum",
	mobileList = {
		{ template = "sith_shadow_outlaw_mission", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow_outlaw_mission", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 }
	},
	activeAreaRadius = 64,
	flattenLayer = true
}

-- Check if the sith shadow is the first one spawned for the player.
-- @param pSithShadow pointer to the sith shadow.
-- @param pPlayer pointer to the creature object of the player.
-- @return true if the sith shadow is the first one spawned for the player.
function SithShadowIntroTheater:isTheFirstSithShadowOfThePlayer(pSithShadow, pPlayer)
	local spawnedSithShadows = self:getSpawnedMobileList(pPlayer)

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
			FsIntro:setCurrentStep(pLooter, 7)
			QuestManager.completeQuest(pLooter, QuestManager.quests.FS_THEATER_CAMP)
			QuestManager.completeQuest(pLooter, QuestManager.quests.GOT_DATAPAD_2)
			return 1
		end
	end

	return 0
end

-- Event handler for the enter active area event.
-- The event will cause all spawned Sith Shadows to attack the player.
-- @param pPlayer pointer to the creature object of the player.
-- @param spawnedSithShadowsList list with pointers to the spawned sith shadows.
function SithShadowIntroTheater:onEnteredActiveArea(pPlayer, spawnedSithShadowsList)
	if (pPlayer == nil or spawnedSithShadowsList == nil) then
		return
	end

	foreach(spawnedSithShadowsList, function(pMobile)
		if (SpawnMobiles.isValidMobile(pMobile)) then
			AiAgent(pMobile):setDefender(pPlayer)
		end
	end)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_2)
end

-- Event handler for the successful spawn event.
-- The event will activate the FS_THEATER_CAMP quest for the player.
-- @param pPlayer pointer to the creature object of the player.
-- @param spawnedSithShadowsList list with pointers to the spawned sith shadows.
function SithShadowIntroTheater:onObjectsSpawned(pPlayer, spawnedSithShadowsList)
	if (pPlayer == nil or spawnedSithShadowsList == nil) then
		return
	end

	if (SpawnMobiles.isValidMobile(spawnedSithShadowsList[1])) then
		createObserver(LOOTCREATURE, self.taskName, "onLoot", spawnedSithShadowsList[1])
	end
end

function SithShadowIntroTheater:onTheaterCreated(pPlayer)
	if (pPlayer == nil) then
		return
	end
	
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_THEATER_CAMP)
end

-- Handling of the activation of the theater waypoint datapad.
-- @param pSceneObject pointer to the datapad object.
-- @param pPlayer pointer to the creature object who activated the datapad.
function SithShadowIntroTheater:useTheaterDatapad(pSceneObject, pPlayer)
	Logger:log("Player used the looted theater datapad.", LT_INFO)
	if QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.GOT_DATAPAD_2) then
		CreatureObject(pPlayer):sendSystemMessage(READ_DISK_2_STRING)

		SceneObject(pSceneObject):destroyObjectFromWorld()
		SceneObject(pSceneObject):destroyObjectFromDatabase()

		QuestManager.completeQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_2)
		FsIntro:setCurrentStep(pPlayer, 8)
		GoToDathomir:start(pPlayer)
	else
		CreatureObject(pPlayer):sendSystemMessage(READ_DISK_ERROR_STRING)
	end
end

return SithShadowIntroTheater
