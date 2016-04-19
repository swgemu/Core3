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
	waypointDescription = "@quest/force_sensitive/exit:exit_sum",
	mobileList = {
		{ template = "mellichae", minimumDistance = 3, maximumDistance = 6, referencePoint = 0 },
		{ template = "daktar_bloodmoon", minimumDistance = 3, maximumDistance = 6, referencePoint = 0 },
		{ template = "sith_shadow_mercenary", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow_mercenary", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow_mercenary", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow_thug", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow_thug", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
		{ template = "sith_shadow_thug", minimumDistance = 32, maximumDistance = 64, referencePoint = 0 }
	},
	despawnTime =  60* 60* 1000, -- 1 hour
	activeAreaRadius = 72 -- Make sure we grab the entering of radius.
}

-- Event handler for killing Mellichae and looting him.
function MellichaeOutroTheater:onLoot(pLootedCreature, pLooter, nothing)
	if (pLootedCreature == nil or pLooter == nil) then
		return 1
	end

	Logger:log("Mellichae Looted.", LT_INFO)

	-- We need to see which player/group got loot rights...
	local pInventory = SceneObject(pLootedCreature):getSlottedObject("inventory")

	if (pInventory == nil) then
		return 1
	end

	local ownerID = SceneObject(pInventory):getContainerOwnerID()

	local looterID = SceneObject(pLooter):getObjectID()

	local theaterID = readData(looterID .. self.taskName .. "theaterId")
	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		return 1
	end

	if (CreatureObject(pLooter):isGrouped()) then
		looterID = CreatureObject(pLooter):getGroupID()
	end

	local ownedSpawn = SpawnMobiles.isFromSpawn(pTheater, MellichaeOutroTheater.taskName, pLootedCreature)

	if (looterID == ownerID) and (ownedSpawn == true) then
		createLoot(pInventory, "mellichae_outro", 0, true)
		QuestManager.completeQuest(pLooter, QuestManager.quests.FS_THEATER_FINAL)
		CreatureObject(pLooter):sendSystemMessage("@quest/force_sensitive/exit:final_complete") --	Congratulations, you have completed the Force sensitive quests! You are now qualified to begin the Jedi Padawan Trials.
		VillageJediManagerCommon.setJediProgressionScreenPlayState(pLooter, VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE) -- Killed him.
		deleteData(SceneObject(pLooter):getObjectID() .. ":totalNum:Shrines:Red")
		deleteData(SceneObject(pLooter):getObjectID() .. ":totalNum:Shrines:Green")
	end

	return 1

end

-- Event handler for the enter active area event.
function MellichaeOutroTheater:onEnteredActiveArea(pCreatureObject, spawnedSithShadowsList)
	if (pCreatureObject == nil or spawnedSithShadowsList == nil or spawnedSithShadowsList[1] == nil) then
		return
	end

	local playerID = SceneObject(pCreatureObject):getObjectID()

	local theaterID = readData(playerID .. self.taskName .. "theaterId")

	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		return
	end

	local ownedSpawn = SpawnMobiles.isFromSpawn(pTheater, MellichaeOutroTheater.taskName, spawnedSithShadowsList[1])

	-- Shouldn't be here...
	if (VillageJediManagerCommon.hasJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_ACCEPTED_MELLICHAE) == false) then
		if (ownedSpawn == false) then
			return
		end
	end

	foreach(spawnedSithShadowsList, function(pMobile)
		if (pMobile ~= nil) then
			if (SceneObject(pMobile):getDisplayedName() ~= "Mellichae") then
				AiAgent(pMobile):setDefender(pCreatureObject)
			end

			if (SceneObject(pMobile):getDisplayedName() == "Daktar Bloodmoon") then
				local greetingString = LuaStringIdChatParameter("@quest/force_sensitive/exit:taunt1")
				local firstName = CreatureObject(pCreatureObject):getFirstName()
				greetingString:setTT(firstName)
				spatialChat(pMobile, greetingString:_getObject()) -- %TT, You shall pay for your tresspass here - SOLDIERS - defend the crystals! Let no one leave here alive.
			end
		end
	end)

	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pCreatureObject)
	QuestManager.completeQuest(pCreatureObject, QuestManager.quests.FS_THEATER_CAMP)
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_THEATER_FINAL)
end

-- Event handler for the successful spawn event.
function MellichaeOutroTheater:onSuccessfulSpawn(pCreatureObject, spawnedSithShadowsList)
	if (pCreatureObject == nil or spawnedSithShadowsList == nil or spawnedSithShadowsList[1] == nil or spawnedSithShadowsList[2] == nil) then
		return
	end

	VillageJediManagerCommon.setJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_ACCEPTED_MELLICHAE)

	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_THEATER_CAMP)
	createObserver(LOOTCREATURE, self.taskName, "onLoot", spawnedSithShadowsList[1])
	createObserver(DAMAGERECEIVED, self.taskName, "onDamageReceived", spawnedSithShadowsList[1])
	createObserver(DAMAGERECEIVED, self.taskName, "onDamageReceived", spawnedSithShadowsList[2])

	writeData(SceneObject(spawnedSithShadowsList[1]):getObjectID() .. ":mell:encounter:belongs:to", SceneObject(pCreatureObject):getObjectID())
	writeData(SceneObject(spawnedSithShadowsList[2]):getObjectID() .. ":mell:encounter:belongs:to", SceneObject(pCreatureObject):getObjectID())

	for i=1,2 do
		MellichaeOutroTheater:spawnScenePowerShrines(pCreatureObject, spawnedSithShadowsList[1], "red", i)
		writeData(SceneObject(pCreatureObject):getObjectID() .. ":totalNum:Shrines:Red", i)

		MellichaeOutroTheater:spawnScenePowerShrines(pCreatureObject, spawnedSithShadowsList[1], "green", i)
		writeData(SceneObject(pCreatureObject):getObjectID() .. ":totalNum:Shrines:Green", i)
	end

end

-- Handle the event PLAYERKILLED, 0 keeps, 1 does not keep observer.
function MellichaeOutroTheater:onPlayerKilled(pCreatureObject, pKiller, nothing)
	if (pCreatureObject == nil or pKiller == nil) then
		return 1
	end

	Logger:log("Player was killed.", LT_INFO)
	CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/exit:final_fail") -- You have failed the Mellichae encounter, you will be given the oppertunity to attempt it again in the near future.
	OldManOutroEncounter:start(pCreatureObject)
	QuestManager.resetQuest(pCreatureObject, QuestManager.quests.FS_THEATER_CAMP)
	QuestManager.resetQuest(pCreatureObject, QuestManager.quests.FS_THEATER_FINAL)
	deleteData(SceneObject(pCreatureObject):getObjectID() .. ":totalNum:Shrines:Red")
	deleteData(SceneObject(pCreatureObject):getObjectID() .. ":totalNum:Shrines:Green")
	return 1
end

-- Handle the event object destruction for the red shrines in the camp.
function MellichaeOutroTheater:onPowerShrineDestroyed(pSceneObject, pKiller, nothing)
	if (pSceneObject == nil or pKiller == nil) then
		return 1
	end

	local ownerID = readData(SceneObject(pSceneObject):getObjectID() .. ":isShrineOwned:By")


	if (SceneObject(pSceneObject):getTemplateObjectPath() == "object/tangible/jedi/power_shrine_red.iff") then
		Logger:log("1 Red Shrine was destroyed.", LT_INFO)
		local numOfShrines = readData(ownerID .. ":totalNum:Shrines:Red")

		if (numOfShrines ~= nil) then
			writeData(ownerID .. ":totalNum:Shrines:Red", numOfShrines - 1)
		end
		SceneObject(pSceneObject):destroyObjectFromWorld()
		deleteData(SceneObject(pSceneObject):getObjectID() .. ":isShrineOwned:By")
		return 1

	elseif (SceneObject(pSceneObject):getTemplateObjectPath() == "object/tangible/jedi/power_shrine.iff") then
		Logger:log("1 Green Shrine was destroyed.", LT_INFO)
		local numOfShrines = readData(ownerID .. ":totalNum:Shrines:Green")

		if (numOfShrines ~= nil) then
			writeData(ownerID .. ":totalNum:Shrines:Green", numOfShrines - 1)
		end
		SceneObject(pSceneObject):destroyObjectFromWorld()
		deleteData(SceneObject(pSceneObject):getObjectID() .. ":isShrineOwned:By")
		return 1

	end
end

-- Handle the event damage done, if the shrines are still up then they will heal Mellichae/Daktar.
function MellichaeOutroTheater:onDamageReceived(pObject, pAttacker, damage)
	if (pObject == nil or pAttacker == nil) then
		return 1
	end

	-- Due to how this observer is setup, we are only tracking red shrines, daktar, and mellichae.
	-- Green shrines must be up for red healing, red must be up for Mellichae/Dak healing.

	if (SceneObject(pObject):getTemplateObjectPath() == "object/tangible/jedi/power_shrine_red.iff") then
		local creoOwnerId = readData(SceneObject(pObject):getObjectID() .. ":isShrineOwned:By")
		local numOfShrines = readData(creoOwnerId .. ":totalNum:Shrines:Green")

		if (numOfShrines ~= nil and numOfShrines > 0) then
			TangibleObject(pObject):setConditionDamage(0)
			SceneObject(pObject):playEffect("clienteffect/healing_healdamage.cef", "")
			return 0
		elseif (numOfShrines == nil or numOfShrines <= 0) then
			return 1
		end
	elseif (SceneObject(pObject):isCreatureObject()) then -- Not a Shrine.
		local creoOwnerId = readData(SceneObject(pObject):getObjectID() .. ":mell:encounter:belongs:to")
		local numOfShrines = readData(creoOwnerId .. ":totalNum:Shrines:Red")

		if (numOfShrines ~= nil and numOfShrines > 0 and damage > 0) then
			CreatureObject(pObject):healDamage(damage, 0)
			CreatureObject(pObject):healDamage(damage, 3)
			CreatureObject(pObject):healDamage(damage, 6)
			CreatureObject(pObject):playEffect("clienteffect/healing_healdamage.cef", "")
			return 0
		elseif (numOfShrines == nil or numOfShrines <= 0) then
			if (SceneObject(pObject):getDisplayedName() == "Daktar Bloodmoon") then -- Only Daktar should taunt.
				local greetingString = LuaStringIdChatParameter("@quest/force_sensitive/exit:taunt3") -- %TT, You may have destroyed my power crystals, but now I will destroy you! SOLDIERS ATTACK!!!
				local firstName = CreatureObject(pAttacker):getFirstName()
				greetingString:setTT(firstName)
				spatialChat(pObject, greetingString:_getObject())

				-- Do the extra spawn of 6 more sith shadows, only on Daktar so they don't spawn twice.
				for i=1,3 do
					local zoneName = CreatureObject(pObject):getZoneName()
					local randomDistance = getRandomNumber(32)
					local x = CreatureObject(pObject):getWorldPositionX() + randomDistance
					local y = CreatureObject(pObject):getWorldPositionY() + randomDistance
					local z = getTerrainHeight(pObject, x, y)

					local pMobile = spawnMobile(zoneName, "sith_shadow_mercenary", 0, x, z, y, 0, 0)
					if (pMobile ~= nil and SceneObject(pMobile):isAiAgent()) then
						AiAgent(pMobile):setDefender(pAttacker)
					end

					x = x + randomDistance
					y = y + randomDistance
					z = getTerrainHeight(pObject, x, y)
					pMobile = spawnMobile(zoneName,"sith_shadow_thug", 0, x, z, y, 0, 0)
					if (pMobile ~= nil and SceneObject(pMobile):isAiAgent()) then
						AiAgent(pMobile):setDefender(pAttacker)
					end

				end
			end
			return 1
		else
			return 0
		end
	end
end

-- This is called from the base module to clean up anything extra...
function MellichaeOutroTheater:onTheaterDespawn(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	local pShrine = nil

	for i=1,2 do
		local shrineIDRed = readData(SceneObject(pCreatureObject):getObjectID() .. ":powershrine:".. "red" .. ":" .. tostring(i))
		local pShrineR = getSceneObject(shrineIDRed)

		if (pShrineR ~= nil) then
			SceneObject(pShrineR):destroyObjectFromWorld()
			SceneObject(pShrineR):destroyObjectFromDatabase()
			deleteData(SceneObject(pCreatureObject):getObjectID() .. ":powershrine:".. "red" .. ":" .. tostring(i))
			deleteData(shrineIDRed .. ":isShrineOwned:By")
		end

		local shrineIDGreen = readData(SceneObject(pCreatureObject):getObjectID() .. ":powershrine:".. "green" .. ":" .. tostring(i))
		local pShrineG = getSceneObject(shrineIDGreen)

		if (pShrineG ~= nil) then
			SceneObject(pShrineG):destroyObjectFromWorld()
			SceneObject(pShrineG):destroyObjectFromDatabase()
			deleteData(SceneObject(pCreatureObject):getObjectID() .. ":powershrine:".. "green" .. ":" .. tostring(i))
			deleteData(shrineIDGreen .. ":isShrineOwned:By")
		end

	end
end

-- For spawning the extra shrine scene objects.
function MellichaeOutroTheater:spawnScenePowerShrines(pCreatureObject, pMellichae, color, i)
	if (pMellichae == nil or pCreatureObject == nil) then
		return
	end

	local planet = SceneObject(pMellichae):getZoneName()
	local theX = SceneObject(pMellichae):getWorldPositionX()
	local theY = SceneObject(pMellichae):getWorldPositionY()
	local boundaryCrystalsLoc = getSpawnPoint(planet, theX, theY, 32, 64, true)

	if (color == "red") then
		local pShrine = spawnSceneObject(planet, "object/tangible/jedi/power_shrine_red.iff", boundaryCrystalsLoc[1], boundaryCrystalsLoc[2], boundaryCrystalsLoc[3], 0, 0)
		TangibleObject(pShrine):setMaxCondition(40000)
		createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineDestroyed", pShrine)
		createObserver(DAMAGERECEIVED, self.taskName, "onDamageReceived", pShrine)
		writeData(SceneObject(pShrine):getObjectID() .. ":isShrineOwned:By", SceneObject(pCreatureObject):getObjectID())
		writeData(SceneObject(pCreatureObject):getObjectID() .. ":powershrines:" .. color .. ":" .. tostring(i), SceneObject(pShrine):getObjectID())
	elseif (color == "green") then
		local pShrine = spawnSceneObject(planet, "object/tangible/jedi/power_shrine.iff", boundaryCrystalsLoc[1], boundaryCrystalsLoc[2], boundaryCrystalsLoc[3], 0, 0)
		TangibleObject(pShrine):setMaxCondition(40000)
		createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineDestroyed", pShrine)
		writeData(SceneObject(pShrine):getObjectID() .. ":isShrineOwned:By", SceneObject(pCreatureObject):getObjectID())
		writeData(SceneObject(pCreatureObject):getObjectID() .. ":powershrine:".. color .. ":" .. tostring(i), SceneObject(pShrine):getObjectID())
	end

end

return MellichaeOutroTheater
