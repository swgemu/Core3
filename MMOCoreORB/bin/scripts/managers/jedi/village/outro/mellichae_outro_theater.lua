local GoToTheater = require("quest.tasks.go_to_theater")
local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
require("utils.helpers")

local RANDOM_NUM

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

-- This function checks to see if it's Mellichae and the correct one.
function MellichaeOutroTheater:isMellchae(pMellichae, pCreatureObject)
	local spawnedMobiles = self:getSpawnedMobileList(pCreatureObject)

	if spawnedMobiles ~= nil and spawnedMobiles[1] ~= nil then
		return CreatureObject(spawnedMobiles[1]):getObjectID() == CreatureObject(pMellichae):getObjectID()
	else
		return false
	end
end

-- We need to add loot to Mellichae to be dropped for the quest owner.
function MellichaeOutroTheater:addLoot(pMellichae)
	local pInventory = SceneObject(pMellichae):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	createLoot(pInventory, "mellichae_outro", 0, true)
end

-- Event handler for looting Mellichae.
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
			deleteData(CreatureObject(pLooter):getObjectID() .. "fsOutro:ActiveShrines:Red")
			return 1
		end
	end

	return 0
end

-- Event handler for the enter active area event.
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
function MellichaeOutroTheater:onSuccessfulSpawn(pCreatureObject, spawnedSithShadowsList)
	if (pCreatureObject == nil or spawnedSithShadowsList == nil or spawnedSithShadowsList[1] == nil) then
		return
	end

	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_THEATER_CAMP)
	createObserver(LOOTCREATURE, self.taskName, "onLoot", spawnedSithShadowsList[1])
	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pCreatureObject)
	createObserver(DAMAGERECEIVED, self.taskName, "onDamageReceived", spawnedSithShadowsList[1])
	createObserver(DAMAGERECEIVED, self.taskName, "onDamageReceived", spawnedSithShadowsList[2])

	RANDOM_NUM = getRandomNumber(10000, 19999)

	local zoneName = SceneObject(pCreatureObject):getZoneName()

	local pShrine = nil

	for i=1,4 do
		MellichaeOutroTheater:spawnScenePowerShrines(spawnedSithShadowsList[1], "red")
		MellichaeOutroTheater:spawnScenePowerShrines(spawnedSithShadowsList[1], "green")
	end

end

-- Handle the event PLAYERKILLED, 0 keeps, 1 does not keep observer.
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

-- Handle the event object destruction for the red shrines in the camp.
function MellichaeOutroTheater:onPowerShrineRedDestroyed(pSceneObject, pKiller, nothing)
	if (pSceneObject == nil or pKiller == nil) then
		return 0
	end

	local numOfShrines = readData(RANDOM_NUM .. "fsOutro:ActiveShrines:red")

	if (numOfShrines ~= nil) then
		Logger:log("1 red Shrine was destroyed.", LT_INFO)
		writeData(RANDOM_NUM .. "fsOutro:ActiveShrines:red", numOfShrines - 1)
		return 1
	end

	return 0
end

-- Handle the event object destruction for the green shrines in the camp.
function MellichaeOutroTheater:onPowerShrineGreenDestroyed(pSceneObject, pKiller, nothing)
	if (pSceneObject == nil or pKiller == nil) then
		return 0
	end

	local numOfShrines = readData(RANDOM_NUM .. "fsOutro:ActiveShrines:green")

	if (numOfShrines ~= nil) then
		Logger:log("1 green Shrine was destroyed.", LT_INFO)
		writeData(RANDOM_NUM .. "fsOutro:ActiveShrines:green", numOfShrines - 1)
		return 1
	end

	return 0
end

-- Handle the event damage done, if the shrines are still up then they will heal Mellichae/Daktar.
function MellichaeOutroTheater:onDamageReceived(pObject, pAttacker, damage)
	if (pObject == nil or pAttacker == nil) then
		return 0
	end

	local numOfShrinesRed = readData(RANDOM_NUM .. "fsOutro:ActiveShrines:red")
	local numOfShrinesGreen = readData(RANDOM_NUM .. "fsOutro:ActiveShrines:green")

	if (numOfShrinesGreen <= 0) then
		return 1
	end

	if (numOfShrinesRed <= 0) then
		local greetingString = LuaStringIdChatParameter("@quest/force_sensitive/exit:taunt3") -- %TT, You may have destroyed my power crystals, but now I will destroy you! SOLDIERS ATTACK!!!
		local firstName = CreatureObject(pAttacker):getFirstName()
		greetingString:setTT(firstName)
		spatialChat(pObject, greetingString:_getObject())
		return 1
	end

	if (damage > 0) then -- Need data on healing, but it seems like it healed the same amount no matter how many were left.
		CreatureObject(pObject):healDamage(0, damage / 2)
		CreatureObject(pObject):healDamage(1, damage / 2)
		CreatureObject(pObject):healDamage(2, damage / 2)
		CreatureObject(pObject):playEffect("clienteffect", "healing_healdamage.cef")
		return 0
	end

	return 0
end

-- For spawning the extra shrine scene objects.
function MellichaeOutroTheater:spawnScenePowerShrines(pMellichae, color)
	local planet = SceneObject(pMellichae):getZoneName()
	local theX = CreatureObject(pMellichae):getWorldPositionX()
	local theY = CreatureObject(pMellichae):getWorldPositionY()
	local boundaryCrystalsLoc = getSpawnPoint(pMellichae, theX, theY, 16, 32)
	local numOfShrines = readData(RANDOM_NUM .. "fsOutro:ActiveShrines:" .. color)

	if (color == "red") then
		local pShrine = spawnSceneObject(planet, "object/tangible/jedi/power_shrine_red.iff", boundaryCrystalsLoc[1], boundaryCrystalsLoc[2], boundaryCrystalsLoc[3], 1, 0, 0, 0)
		createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineRedDestroyed", pShrine)
		createObserver(DAMAGERECEIVED, self.taskName, "onDamageReceived", pShrine)
	elseif (color == "green") then
		local pShrine = spawnSceneObject(planet, "object/tangible/jedi/power_shrine.iff", boundaryCrystalsLoc[1], boundaryCrystalsLoc[2], boundaryCrystalsLoc[3], 1, 0, 0, 0)
		createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineGreenDestroyed", pShrine)
	end


	if (numOfShrines ~= nil) then
		writeData(RANDOM_NUM .. "fsOutro:ActiveShrines:" .. color, numOfShrines + 1)
	else
		writeData(RANDOM_NUM .. "fsOutro:ActiveShrines:" .. color, 1)
	end
end

return MellichaeOutroTheater
