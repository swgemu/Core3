local GoToTheater = require("quest.tasks.go_to_theater")
local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
require("utils.helpers")

MellichaeOutroTheater = GoToTheater:new {
	-- Task properties
	taskName = "MellichaeOutroTheater",
	-- GoToTheater properties
	minimumDistance = 1024,
	maximumDistance = 1536,
	theater = "object/building/poi/anywhere_fs_intro_camp.iff",
	waypointDescription = "@string/en/quest/force_sensitive/exit:exit_sum",
	mobileList = {
		{ template = "mellichae", minimumDistance = 3, maximumDistance = 6, referencePoint = 0 },
		{ template = "daktar_bloodmoon", minimumDistance = 3, maximumDistance = 6, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 }
	},
	despawnTime = 2 * 60* 60* 1000, -- 2 hours
	activeAreaRadius = 64,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil
}

-- Check if the sith  is the first one spawned for the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the sith is the first one spawned for the player.
function MellichaeOutroTheater:isMellchae(pMellichae, pCreatureObject)
	local spawnedMobiles = self:getSpawnedMobileList(pCreatureObject)

	if spawnedMobiles ~= nil and spawnedMobiles[1] ~= nil then
		return CreatureObject(spawnedMobiles[1]):getObjectID() == CreatureObject(pMellichae):getObjectID()
	else
		return false
	end
end

-- Create the waypoint datapad as loot on the sith shadow.
-- @param pSithShadow pointer to the creature object of the sith shadow.
function MellichaeOutroTheater:addLoot(pMellichae)
	local pInventory = SceneObject(pMellichae):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	createLoot(pInventory, "mellichae_outro", 0, true)
end

-- Event handler for the LOOTCREATURE event on one of the sith shadows.
-- @param pLootedCreature pointer to the sith shadow creature that is being looted.
-- @param pLooter pointer to the creature object of the looter.
-- @param nothing unused variable for the default footprint of event handlers.
-- @return 1 if the correct player looted the creature to remove the observer, 0 otherwise to keep the observer.
function MellichaeOutroTheater:onLoot(pLootedCreature, pLooter, nothing)
	if (pLootedCreature == nil or pLooter == nil) then
		return 0
	end

	Logger:log("Looting mellichae", LT_INFO)
	if QuestManager.hasActiveQuest(pLooter, QuestManager.quests.FS_THEATER_FINAL) then
		if self:isMellchae(pLootedCreature, pLooter) then
			self:addLoot(pLootedCreature)
			QuestManager.completeQuest(pLooter, QuestManager.quests.FS_THEATER_FINAL)
			CreatureObject(pLooter):sendSystemMessage("@quest/force_sensitive/exit:final_complete") --	Congratulations, you have completed the Force sensitive quests! You are now qualified to begin the Jedi Padawan Trials.
			CreatureObject(pLooter):setScreenPlayState(16, "VillageScreenPlay") -- Killed him.
			deleteData(CreatureObject(pLooter):getObjectID() .. "fsOutro:ActiveShrines")
			return 1
		end
	end

	return 0
end

-- Event handler for the enter active area event.
-- The event will cause all spawned Sith Shadows to attack the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param spawnedSithShadowsList list with pointers to the spawned sith shadows.
function MellichaeOutroTheater:onEnteredActiveArea(pCreatureObject, spawnedSithShadowsList)
	if (pCreatureObject == nil or spawnedSithShadowsList == nil) then
		return
	end

	foreach(spawnedSithShadowsList, function(pMobile)
		if (pMobile ~= nil) then
			AiAgent(pMobile):setDefender(pCreatureObject)
		end
	end)
	local greetingString = LuaStringIdChatParameter("@quest/force_sensitive/exit:taunt1")
	local firstName = CreatureObject(pCreatureObject):getFirstName()
	greetingString:setTT(firstName)
	spatialChat(spawnedSithShadowsList[1], greetingString:_getObject()) -- %TT, You shall pay for your tresspass here - SOLDIERS - defend the crystals! Let no one leave here alive.
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_THEATER_FINAL)
end

-- Event handler for the successful spawn event.
-- The event will activate the FS_THEATER_CAMP quest for the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param spawnedSithShadowsList list with pointers to the spawned sith shadows.
function MellichaeOutroTheater:onSuccessfulSpawn(pCreatureObject, spawnedSithShadowsList)
	if (pCreatureObject == nil or spawnedSithShadowsList == nil or spawnedSithShadowsList[1] == nil) then
		return
	end

	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_THEATER_CAMP)
	createObserver(LOOTCREATURE, self.taskName, "onLoot", spawnedSithShadowsList[1])
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pCreatureObject)
	createObserver(DAMAGERECEIVED, self.taskName, "onDamageReceived", spawnedSithShadowsList[1])
	createObserver(DAMAGERECEIVED, self.taskName, "onDamageReceived", spawnedSithShadowsList[2])

	local boundaryCrystalsX1 = SceneObject(spawnedSithShadowsList[1]):getWorldPositionX() - 32
	local boundaryCrystalsX2 = SceneObject(spawnedSithShadowsList[1]):getWorldPositionX() + 32
	local boundaryCrystalsY2 = SceneObject(spawnedSithShadowsList[1]):getWorldPositionY() + 32
	local boundaryCrystalsY1 = SceneObject(spawnedSithShadowsList[1]):getWorldPositionY() - 32

	local pShrine = nil
	writeData(CreatureObject(pCreatureObject):getObjectID() .. "fsOutro:ActiveShrines", 4)

	-- Shrine 1
	pShrine = spawnSceneObject(SceneObject(pCreatureObject):getZoneName(), "object/tangible/jedi/power_shrine_red.iff", boundaryCrystalsX1, getTerrainHeight(spawnedSithShadowsList[1], boundaryCrystalsX1, boundaryCrystalsY1), boundaryCrystalsY1, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineDestroyed", pShrine)
	-- Shrine 2
	pShrine = spawnSceneObject(SceneObject(pCreatureObject):getZoneName(), "object/tangible/jedi/power_shrine_red.iff", boundaryCrystalsX1, getTerrainHeight(spawnedSithShadowsList[1], boundaryCrystalsX1, boundaryCrystalsY2), boundaryCrystalsY2, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineDestroyed", pShrine)
	--Shrine 3
	pShrine = spawnSceneObject(SceneObject(pCreatureObject):getZoneName(), "object/tangible/jedi/power_shrine_red.iff", boundaryCrystalsX2, getTerrainHeight(spawnedSithShadowsList[1], boundaryCrystalsX2, boundaryCrystalsY1), boundaryCrystalsY1, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineDestroyed", pShrine)
	-- Shrine 4
	pShrine = spawnSceneObject(SceneObject(pCreatureObject):getZoneName(), "object/tangible/jedi/power_shrine_red.iff", boundaryCrystalsX2, getTerrainHeight(spawnedSithShadowsList[1], boundaryCrystalsX2, boundaryCrystalsY2), boundaryCrystalsY2, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineDestroyed", pShrine)
end

-- Handle the event PLAYERKILLED.
-- @param pCreatureObject pointer to the creature object of the killed player.
-- @param pKiller pointer to the creature object of the killer.
-- @param noting unused variable for the default footprint of event handlers.
-- @return 1 if the player was killed by one of the sith shadows, otherwise 0 to keep the observer.
function MellichaeOutroTheater:onPlayerKilled(pCreatureObject, pKiller, nothing)
	if (pCreatureObject == nil or pKiller == nil) then
		return 0
	end

	Logger:log("Player was killed.", LT_INFO)
	if SpawnMobiles.isFromSpawn(pCreatureObject, MellichaeOutroTheater.taskName, pKiller) then
		CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/exit:final_fail") -- You have failed the Mellichae encounter, you will be given the oppertunity to attempt it again in the near future.
		OldManEncounter:start(pCreatureObject)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.FS_THEATER_FINAL)
		return 1
	end

	return 0
end

function MellichaeOutroTheater:onPowerShrineDestroyed(pSceneObject, pKiller, nothing)
	if (pSceneObject == nil or pKiller == nil) then
		return 0
	end

	local numOfShrines = readData(CreatureObject(pKiller):getObjectID() .. "fsOutro:ActiveShrines")

	if (numOfShrines ~= nil) then
		Logger:log("1 Shrine was destroyed.", LT_INFO)
		writeData(CreatureObject(pKiller):getObjectID() .. "fsOutro:ActiveShrines", numOfShrines - 1)
		return 1
	end

	return 0
end

function MellichaeOutroTheater:onDamageReceived(pCreatureObject, pAttacker, damage)
	if (pCreatureObject == nil or pAttacker == nil) then
		return 0
	end

	local numOfShrines = readData(CreatureObject(pAttacker):getObjectID() .. "fsOutro:ActiveShrines")

	if (numOfShrines <= 0) then
		local greetingString = LuaStringIdChatParameter("@quest/force_sensitive/exit:taunt3") -- %TT, You may have destroyed my power crystals, but now I will destroy you! SOLDIERS ATTACK!!!
		local firstName = CreatureObject(pAttacker):getFirstName()
		greetingString:setTT(firstName)
		spatialChat(pCreatureObject, greetingString:_getObject())
		return 1
	end

	if (damage > 0) then
		CreatureObject(pCreatureObject):healDamage(0, damage / 2)
		CreatureObject(pCreatureObject):healDamage(1, damage / 2)
		CreatureObject(pCreatureObject):healDamage(2, damage / 2)
		CreatureObject(pCreatureObject):playEffect("clienteffect", "healing_healdamage.cef")
		return 0
	end

	return 0
end

return MellichaeOutroTheater
