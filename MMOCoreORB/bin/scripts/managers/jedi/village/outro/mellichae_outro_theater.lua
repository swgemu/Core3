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
	waypointDescription = "@quest/force_sensitive/exit:exit_sum",
	mobileList = {
		{ template = "mellichae", minimumDistance = 3, maximumDistance = 6, referencePoint = 0 },
		{ template = "daktar_bloodmoon", minimumDistance = 3, maximumDistance = 6, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 }
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
		return 1
	end

	Logger:log("Looting mellichae", LT_INFO)
	if QuestManager.hasActiveQuest(pLooter, QuestManager.quests.FS_THEATER_FINAL) then
		if self:isMellchae(pLootedCreature, pLooter) then
			self:addLoot(pLootedCreature)
			QuestManager.completeQuest(pLooter, QuestManager.quests.FS_THEATER_FINAL)
			CreatureObject(pLooter):sendSystemMessage("@quest/force_sensitive/exit:final_complete") --	Congratulations, you have completed the Force sensitive quests! You are now qualified to begin the Jedi Padawan Trials.
			CreatureObject(pLooter):setScreenPlayState(16, "VillageScreenPlay") -- Killed him.
			return 0
		end
	end

	return 1
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

	local pMellichae = spawnedSithShadowsList[1]

	local numOfEachTypeOfShrine = 2

	for i=1,numOfEachTypeOfShrine do
		MellichaeOutroTheater:spawnScenePowerShrines(pCreatureObject, pMellichae, "red", 1)
		MellichaeOutroTheater:spawnScenePowerShrines(pCreatureObject, pMellichae, "green", 1)
	end

end

-- Handle the event PLAYERKILLED, 0 keeps, 1 does not keep observer.
function MellichaeOutroTheater:onPlayerKilled(pCreatureObject, pKiller, nothing)
	if (pCreatureObject == nil or pKiller == nil) then
		return 1
	end

	Logger:log("Player was killed.", LT_INFO)
	if SpawnMobiles.isFromSpawn(pCreatureObject, MellichaeOutroTheater.taskName, pKiller) then
		CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/exit:final_fail") -- You have failed the Mellichae encounter, you will be given the oppertunity to attempt it again in the near future.
		OldManEncounter:start(pCreatureObject)
		QuestManager.resetQuest(pCreatureObject, QuestManager.quests.FS_THEATER_FINAL)
		deleteData(SceneObject(pCreatureObject) .. ":fs:Shrine:num:red")
		deleteData(SceneObject(pCreatureObject) .. ":fs:Shrine:num:green")
		return 0
	end

	return 1
end

-- Handle the event object destruction for the red shrines in the camp.
function MellichaeOutroTheater:onPowerShrineRedDestroyed(pSceneObject, pKiller, nothing)
	if (pSceneObject == nil or pKiller == nil) then
		return 1
	end

	local numOfShrines = readData(SceneObject(pKiller):getObjectID() .. ":fs:Shrine:num:red")
	local owner = pKiller

	if (numOfShrines == nil) then
		if (CreatureObject(pKiller):isGrouped()) then
			local groupSize = CreatureObject(pKiller):getGroupSize()
			for i=1,groupSize do
				local pMember = CreatureObject(pKiller):getGroupMember(i)
				if (readData(SceneObject(pMember):getObjectID() .. ":fs:Shrine:num:red") ~= nil) then
					numOfShrines = readData(SceneObject(pMember) .. ":fs:Shrine:num:red")
					owner = pMember
				end
			end
		end
	end


	if (numOfShrines ~= nil) then
		Logger:log("1 red Shrine was destroyed.", LT_INFO)
		writeData(SceneObject(owner):getObjectID() .. ":fs:Shrine:num:red", numOfShrines - 1)
		SceneObject(pSceneObject):destroyObjectFromWorld()
		return 0
	elseif (numOfShrines < 1) then
		deleteData(SceneObject(owner):getObjectID() .. ":fs:Shrine:num:red")
		SceneObject(pSceneObject):destroyObjectFromWorld()
		return 0
	else
		return 1
	end
end

-- Handle the event object destruction for the green shrines in the camp.
function MellichaeOutroTheater:onPowerShrineGreenDestroyed(pSceneObject, pKiller, nothing)
	if (pSceneObject == nil or pKiller == nil) then
		return 1
	end


	local numOfShrines = readData(SceneObject(pKiller):getObjectID() .. ":fs:Shrine:num:green")
	local owner = pKiller

	if (numOfShrines == nil) then
		if (CreatureObject(pKiller):isGrouped()) then
			local groupSize = CreatureObject(pKiller):getGroupSize()
			for i=1,groupSize do
				local pMember = CreatureObject(pKiller):getGroupMember(i)
				if (readData(SceneObject(pMember) .. ":fs:Shrine:num:green") ~= nil) then
					numOfShrines = readData(SceneObject(pMember):getObjectID() .. ":fs:Shrine:num:green")
					owner = pMember
				end
			end
		end
	end


	if (numOfShrines ~= nil) then
		Logger:log("1 green Shrine was destroyed.", LT_INFO)
		writeData(SceneObject(owner):getObjectID() .. ":fs:Shrine:num:green", numOfShrines - 1)
		SceneObject(pSceneObject):destroyObjectFromWorld()
		return 0
	elseif (numOfShrines < 1) then
		deleteData(SceneObject(owner):getObjectID() .. ":fs:Shrine:num:green")
		SceneObject(pSceneObject):destroyObjectFromWorld()
		return 0
	else
		return 1
	end
end

-- Handle the event damage done, if the shrines are still up then they will heal Mellichae/Daktar.
function MellichaeOutroTheater:onDamageReceived(pObject, pAttacker, damage)
	if (pObject == nil or pAttacker == nil) then
		return 1
	end

	local numOfShrinesRed = readData(SceneObject(pAttacker):getObjectID() .. ":fs:Shrine:num:red")

	if (numOfShrinesRed == nil) then
		if (CreatureObject(pAttacker):isGrouped()) then
			local groupSize = CreatureObject(pAttacker):getGroupSize()
			for i=1,groupSize do
				local pMember = CreatureObject(pAttacker):getGroupMember(i)
				if (readData(SceneObject(pMember) .. ":fs:Shrine:num:red") ~= nil) then
					numOfShrinesRed = readData(SceneObject(pMember) .. ":fs:Shrine:num:red")
				end
			end
		end
	end


	local numOfShrinesGreen = readData(SceneObject(pAttacker):getObjectID() .. ":fs:Shrine:num:green")

	if (numOfShrinesGreen == nil) then
		if (CreatureObject(pAttacker):isGrouped()) then
			local groupSize = CreatureObject(pAttacker):getGroupSize()
			for i=1,groupSize do
				local pMember = CreatureObject(pAttacker):getGroupMember(i)
				if (readData(SceneObject(pMember) .. ":fs:Shrine:num:green") ~= nil) then
					numOfShrinesGreen = readData(SceneObject(pMember) .. ":fs:Shrine:num:green")
				end
			end
		end
	end

	if (numOfShrinesRed == nil and SceneObject(pObject):isCreatureObject()) then
		local greetingString = LuaStringIdChatParameter("@quest/force_sensitive/exit:taunt3") -- %TT, You may have destroyed my power crystals, but now I will destroy you! SOLDIERS ATTACK!!!
		local firstName = CreatureObject(pAttacker):getFirstName()
		greetingString:setTT(firstName)
		spatialChat(pObject, greetingString:_getObject())
		return 0
	end

	if (numOfShrinesGreen == nil and SceneObject(pObject):getTemplateObjectPath() == "object/tangible/jedi/power_shrine_red.iff") then
		return 0
	end

	if (damage > 0) then -- Need data on healing, but it seems like it healed the same amount no matter how many were left.
		if (SceneObject(pObject):isCreatureObject()) then
			CreatureObject(pObject):healDamage(damage / 2, 1)
			CreatureObject(pObject):healDamage(damage / 2, 2)
			CreatureObject(pObject):healDamage(damage / 2, 3)
			CreatureObject(pObject):playEffect("clienteffect/healing_healdamage.cef", "")
	else
		TangibleObject(pObject):setConditionDamage(0)
		SceneObject(pObject):playEffect("clienteffect/healing_healdamage.cef", "")
	end
	end

	return 1
end

-- For spawning the extra shrine scene objects.
function MellichaeOutroTheater:spawnScenePowerShrines(pCreatureObject, pMellichae, color, num)
	if (pMellichae == nil or pCreatureObject == nil) then
		return
	end

	local planet = SceneObject(pMellichae):getZoneName()
	local theX = SceneObject(pMellichae):getWorldPositionX()
	local theY = SceneObject(pMellichae):getWorldPositionY()
	local boundaryCrystalsLoc = getSpawnPoint(pMellichae, theX, theY, 32, 64, true)

	if (color == "red") then
		local pShrine = spawnSceneObject(planet, "object/tangible/jedi/power_shrine_red.iff", boundaryCrystalsLoc[1], boundaryCrystalsLoc[2], boundaryCrystalsLoc[3], 0, 0)
		TangibleObject(pShrine):setPvpStatusBitmask(1)
		createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineRedDestroyed", pShrine)
		createObserver(DAMAGERECEIVED, self.taskName, "onDamageReceived", pShrine)
		writeData(SceneObject(pCreatureObject):getObjectID() .. ":fs:Shrine:num:red", 1 + num)
		TangibleObject(pShrine):setMaxCondition(20000)
	elseif (color == "green") then
		local pShrine = spawnSceneObject(planet, "object/tangible/jedi/power_shrine.iff", boundaryCrystalsLoc[1], boundaryCrystalsLoc[2], boundaryCrystalsLoc[3], 0, 0)
		TangibleObject(pShrine):setPvpStatusBitmask(1)
		createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineGreenDestroyed", pShrine)
		writeData(SceneObject(pCreatureObject):getObjectID() .. ":fs:Shrine:num:green", 1 + num)
		TangibleObject(pShrine):setMaxCondition(20000)
	end
end

return MellichaeOutroTheater
