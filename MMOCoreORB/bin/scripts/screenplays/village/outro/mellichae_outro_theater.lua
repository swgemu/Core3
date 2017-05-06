local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
require("utils.helpers")

MellichaeOutroTheater = GoToTheater:new {
	-- Task properties
	taskName = "MellichaeOutroTheater",
	-- GoToTheater properties
	minimumDistance = 900,
	maximumDistance = 1500,
	theater = {
		{ template = "object/tangible/furniture/all/frn_all_light_lamp_table_s03.iff", xDiff = 0.52, zDiff = 1.14, yDiff = -3.37, heading = 0 },
		{ template = "object/tangible/camp/camp_crate_s1.iff", xDiff = -3.78, zDiff = 0, yDiff = 0.91, heading = -18.91 },
		{ template = "object/weapon/ranged/pistol/pistol_dl44_metal.iff", xDiff = 0.13, zDiff = 1.17, yDiff = -2.9, heading = -9.74 },
		{ template = "object/tangible/camp/camp_crate_s1.iff", xDiff = 1.74, zDiff = 0, yDiff = -2.84, heading = -80.214 },
		{ template = "object/static/structure/general/camp_lawn_chair_s01.iff", xDiff = 3.74, zDiff = 0, yDiff = 2.42, heading = -47.74 },
		{ template = "object/static/structure/general/camp_lawn_chair_s01.iff", xDiff = 2.04, zDiff = 0, yDiff = 1.55, heading = 0.39 },
		{ template = "object/static/structure/general/camp_lawn_chair_s01.iff", xDiff = -0.26, zDiff = 0, yDiff = 5.28, heading = 111.15 },
		{ template = "object/static/structure/general/campfire_fresh.iff", xDiff = 2.30, zDiff = 0, yDiff = 4.01, heading = 0 },
		{ template = "object/static/structure/general/camp_spit_s01.iff", xDiff = 1.72, zDiff = 0, yDiff = 3.92, heading = 83.59 },
		{ template = "object/static/structure/general/camp_spit_s01.iff", xDiff = 2.76, zDiff = 0, yDiff = 4.21, heading = 63.79 },
		{ template = "object/static/structure/general/camp_spit_s01.iff", xDiff = 2.33, zDiff = 0, yDiff = 3.3, heading = -24.13 },
		{ template = "object/static/structure/general/trash_pile_s01.iff", xDiff = -3.48, zDiff = 0, yDiff = 2.61, heading = -120.3 },
		{ template = "object/static/structure/tatooine/debris_tatt_crate_1.iff", xDiff = 1.78, zDiff = 0, yDiff = -2.7, heading = 7.45 },
		{ template = "object/static/structure/tatooine/debris_tatt_drum_dented_1.iff", xDiff = 1.61, zDiff = 0, yDiff = -3.92, heading = -82.51 },
		{ template = "object/static/structure/tatooine/debris_tatt_crate_metal_1.iff", xDiff = -2.18, zDiff = 0, yDiff = 1.27, heading = -12.03 },
		{ template = "object/static/structure/general/camp_cot_s01.iff", xDiff = -1.2, zDiff = 0, yDiff = -4.84, heading = -20.05 },
		{ template = "object/static/structure/tatooine/tent_house_tatooine_style_01.iff", xDiff = -2.46, zDiff = 0, yDiff = -2.15, heading = -140.38 },
		{ template = "object/static/structure/tatooine/debris_tatt_drum_dented_1.iff", xDiff = 0.32, zDiff = 0, yDiff = -3.04, heading = 9.74 },
		{ template = "object/static/structure/general/trash_pile_s01.iff", xDiff = -3.64, zDiff = 0, yDiff = 2.997, heading = 156.99 },
		{ template = "object/static/structure/tatooine/debris_tatt_crate_1.iff", xDiff = -2.3, zDiff = 0, yDiff = 1.28, heading = -110.58 },
		{ template = "object/static/structure/general/camp_cot_s01.iff", xDiff = -4.51, zDiff = 0, yDiff = -4.41, heading = 39.53 },
		{ template = "object/static/structure/general/camp_cot_s01.iff", xDiff = -5.42, zDiff = 0, yDiff = -1.45, heading = 99.69 },
		{ template = "object/static/structure/tatooine/debris_tatt_crate_metal_1.iff", xDiff = 1.92, zDiff = 0, yDiff = -1.88, heading = -12.03 },
		{ template = "object/static/item/item_container_organic_food.iff", xDiff = -3.13, zDiff = 0, yDiff = 1.086, heading = 137.69 },
		{ template = "object/tangible/jedi/power_shrine_red.iff", xDiff = -25, zDiff = 0, yDiff = 25, heading = 0 },
		{ template = "object/tangible/jedi/power_shrine.iff", xDiff = 25, zDiff = 0, yDiff = 25, heading = 0 },
		{ template = "object/tangible/jedi/power_shrine_red.iff", xDiff = 25, zDiff = 0, yDiff = -25, heading = 0 },
		{ template = "object/tangible/jedi/power_shrine.iff", xDiff = -25, zDiff = 0, yDiff = -25, heading = 0 },
	},
	waypointDescription = "@quest/force_sensitive/exit:exit_sum",
	mobileList = {
		{ template = "mellichae", minimumDistance = 3, maximumDistance = 6, referencePoint = 0 },
		{ template = "daktar_bloodmoon", minimumDistance = 3, maximumDistance = 6, referencePoint = 0 },
		{ template = "sith_shadow_mercenary", minimumDistance = 8, maximumDistance = 36, referencePoint = 0 },
		{ template = "sith_shadow_mercenary", minimumDistance = 8, maximumDistance = 36, referencePoint = 0 },
		{ template = "sith_shadow_thug", minimumDistance = 8, maximumDistance = 36, referencePoint = 0 },
		{ template = "sith_shadow_thug", minimumDistance = 8, maximumDistance = 36, referencePoint = 0 }
	},
	activeAreaRadius = 72, -- Make sure we grab the entering of radius.
	flattenLayer = true
}

-- Event handler for the enter active area event.
function MellichaeOutroTheater:onEnteredActiveArea(pPlayer, spawnedSithShadowsList)
	if (pPlayer == nil or spawnedSithShadowsList == nil or spawnedSithShadowsList[1] == nil) then
		return
	end

	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_THEATER_FINAL)
end

-- Event handler for the successful spawn event.
function MellichaeOutroTheater:onObjectsSpawned(pPlayer, spawnedSithShadowsList)
	if (pPlayer == nil or spawnedSithShadowsList == nil or not SpawnMobiles.isValidMobile(spawnedSithShadowsList[1]) or not SpawnMobiles.isValidMobile(spawnedSithShadowsList[2])) then
		return
	end

	createObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pPlayer)
	createObserver(OBJECTDESTRUCTION, self.taskName, "onMellichaeKilled", spawnedSithShadowsList[1])

	local mellichaeID = SceneObject(spawnedSithShadowsList[1]):getObjectID()
	local daktarID = SceneObject(spawnedSithShadowsList[2]):getObjectID()
	local playerID = SceneObject(pPlayer):getObjectID()

	writeData(mellichaeID .. "questOwner", playerID)
	writeData(daktarID .. "questOwner", playerID)
	writeData(playerID .. ":daktar", daktarID)
	writeData(playerID .. ":mellichae", mellichaeID)

	self:setupPowerShrines(pPlayer)

	local pTheater = self:getTheaterObject(pPlayer)

	if (pTheater ~= nil) then
		createEvent(10 * 1000, "MellichaeOutroTheater", "doHealingPulse", pPlayer, tostring(SceneObject(pTheater):getObjectID()))
	end
end

function MellichaeOutroTheater:onTheaterCreated(pPlayer)
	if (pPlayer == nil) then
		return
	end

	VillageJediManagerCommon.setJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_ACCEPTED_MELLICHAE)

	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_THEATER_FINAL)
end

function MellichaeOutroTheater:onMellichaeKilled(pMellichae, pKiller)
	if (pMellichae == nil) then
		return 1
	end

	local ownerID = readData(SceneObject(pMellichae):getObjectID() .. "questOwner")
	local pOwner = getSceneObject(ownerID)

	if (pOwner == nil) then
		return 1
	end

	local pTheater = self:getTheaterObject(pOwner)

	if (pTheater == nil) then
		return 1
	end

	local pInventory = SceneObject(pMellichae):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		SceneObject(pInventory):setContainerOwnerID(ownerID)
		createLoot(pInventory, "mellichae_outro", 1, true)
	end

	dropObserver(OBJECTDESTRUCTION, self.taskName, "onPlayerKilled", pOwner)
	QuestManager.completeQuest(pOwner, QuestManager.quests.FS_THEATER_FINAL)
	CreatureObject(pOwner):sendSystemMessage("@quest/force_sensitive/exit:final_complete") --	Congratulations, you have completed the Force sensitive quests! You are now qualified to begin the Jedi Padawan Trials.
	VillageJediManagerCommon.setJediProgressionScreenPlayState(pOwner, VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE) -- Killed him.
	FsOutro:setCurrentStep(pOwner, 4)
	PadawanTrials:doPadawanTrialsSetup(pOwner)

	local pActiveArea = spawnActiveArea(CreatureObject(pOwner):getZoneName(), "object/active_area.iff", SceneObject(pTheater):getWorldPositionX(), 0, SceneObject(pTheater):getWorldPositionY(), 150, 0)

	if (pActiveArea ~= nil) then
		writeData(SceneObject(pActiveArea):getObjectID() .. ":ownerID", ownerID)
		createObserver(EXITEDAREA, "MellichaeOutroTheater", "handleExitedMissionAreaEvent", pActiveArea)
	end

	createEvent(600 * 1000, "MellichaeOutroTheater", "finish", pOwner, "")

	return 1
end

function MellichaeOutroTheater:handleExitedMissionAreaEvent(pActiveArea, pPlayer, nothing)
	if not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local areaID = SceneObject(pActiveArea):getObjectID()

	if (readData(areaID .. ":ownerID") ~= SceneObject(pPlayer):getObjectID()) then
		return 0
	end

	deleteData(areaID .. ":ownerID")
	self:finish(pPlayer)

	return 1
end

-- Handle the event PLAYERKILLED, 0 keeps, 1 does not keep observer.
function MellichaeOutroTheater:onPlayerKilled(pPlayer, pKiller, nothing)
	if (pPlayer == nil or QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_THEATER_FINAL)) then
		return 1
	end

	Logger:log("Player was killed.", LT_INFO)
	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/exit:final_fail") -- You have failed the Mellichae encounter, you will be given the oppertunity to attempt it again in the near future.
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_THEATER_FINAL)

	createEvent(10 * 1000, "MellichaeOutroTheater", "finish", pPlayer, "")

	return 1
end

function MellichaeOutroTheater:setupPowerShrines(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	for i = 1, #self.theater, 1 do
		local objectID = readData(playerID .. self.taskName .. "theaterObject" .. i)
		local pObject = getSceneObject(objectID)
		if (pObject ~= nil) then
			local color = nil
			local crystalCount = 0
			if (SceneObject(pObject):getTemplateObjectPath() == "object/tangible/jedi/power_shrine_red.iff") then
				color = "red"
				crystalCount = readData(playerID .. "redShrines")
			elseif (SceneObject(pObject):getTemplateObjectPath() == "object/tangible/jedi/power_shrine.iff") then
				color = "green"
				crystalCount = readData(playerID .. "greenShrines")
			end

			if (color ~= nil) then
				crystalCount = crystalCount + 1
				TangibleObject(pObject):setMaxCondition(40000)
				createObserver(OBJECTDESTRUCTION, self.taskName, "onPowerShrineDestroyed", pObject)
				writeData(objectID .. "questOwner", playerID)
				writeData(playerID .. color .. "Shrines", crystalCount)
				writeData(playerID .. ":powershrines:" .. color .. ":" .. crystalCount, objectID)
			end
		end
	end
end

-- Handle the event object destruction for the red shrines in the camp.
function MellichaeOutroTheater:onPowerShrineDestroyed(pSceneObject, pKiller, nothing)
	if (pSceneObject == nil or pKiller == nil) then
		return 1
	end

	local ownerID = readData(SceneObject(pSceneObject):getObjectID() .. "questOwner")

	if (SceneObject(pSceneObject):getTemplateObjectPath() == "object/tangible/jedi/power_shrine_red.iff") then
		Logger:log("1 Red Shrine was destroyed.", LT_INFO)
		local numOfShrines = readData(ownerID .. "redShrines")
		numOfShrines = numOfShrines - 1

		writeData(ownerID .. "redShrines", numOfShrines)

		deleteData(SceneObject(pSceneObject):getObjectID() .. "questOwner")
		SceneObject(pSceneObject):destroyObjectFromWorld()

		if (numOfShrines == 0) then
			self:helpCrystal(pKiller, "red", ownerID)
		end
	elseif (SceneObject(pSceneObject):getTemplateObjectPath() == "object/tangible/jedi/power_shrine.iff") then
		Logger:log("1 Green Shrine was destroyed.", LT_INFO)
		local numOfShrines = readData(ownerID .. "greenShrines")
		numOfShrines = numOfShrines - 1

		writeData(ownerID .. "greenShrines", numOfShrines)

		if (numOfShrines == 0) then
			for i = 1, 2, 1 do
				local redID = readData(ownerID .. ":powershrines:red:" .. i)

				local pRed = getSceneObject(redID)

				if (pRed ~= nil) then
					SceneObject(pRed):playEffect("clienteffect/combat_lightning_rifle_hit.cef", "")
				end
			end

			self:helpCrystal(pKiller, "green", ownerID)
		end

		deleteData(SceneObject(pSceneObject):getObjectID() .. "questOwner")
		SceneObject(pSceneObject):destroyObjectFromWorld()
	end

	return 1
end

function MellichaeOutroTheater:helpCrystal(pKiller, color, ownerID)
	local pOwner = getSceneObject(ownerID)

	if (pOwner == nil) then
		return
	end

	local pTheater = self:getTheaterObject(pOwner)

	if (pTheater == nil) then
		return
	end

	local daktarID = readData(ownerID .. ":daktar")
	local pDaktar = getSceneObject(daktarID)

	if (pDaktar ~= nil and not CreatureObject(pDaktar):isDead()) then
		local greetingString

		if (color == "green") then
			greetingString = LuaStringIdChatParameter("@quest/force_sensitive/exit:taunt1")
		else
			greetingString = LuaStringIdChatParameter("@quest/force_sensitive/exit:taunt2")
		end

		local firstName = CreatureObject(pOwner):getFirstName()
		greetingString:setTT(firstName)
		spatialChat(pDaktar, greetingString:_getObject())
		AiAgent(pDaktar):setDefender(pKiller)
	end

	if (color == "red") then
		local mellichaeID = readData(ownerID .. ":mellichae")
		local pMellichae = getSceneObject(mellichaeID)

		if (pMellichae ~= nil and not CreatureObject(pMellichae):isDead()) then
			local greetingString = LuaStringIdChatParameter("@quest/force_sensitive/exit:taunt3")
			local firstName = CreatureObject(pOwner):getFirstName()
			greetingString:setTT(firstName)
			spatialChat(pMellichae, greetingString:_getObject())
			AiAgent(pMellichae):setDefender(pKiller)
		end
	end

	local mobTemplate

	if (color == "green") then
		mobTemplate = "sith_shadow_thug"
	else
		mobTemplate = "sith_shadow_mercenary"
	end

	for i = 1, 4, 1 do
		local zoneName = CreatureObject(pKiller):getZoneName()
		local xLoc = SceneObject(pTheater):getWorldPositionX() + (-10 + getRandomNumber(20))
		local yLoc = SceneObject(pTheater):getWorldPositionY() + (-10 + getRandomNumber(20))
		local zLoc = getTerrainHeight(pKiller, xLoc, yLoc)

		local pMobile = spawnMobile(zoneName, mobTemplate, 0, xLoc, zLoc, yLoc, 0, 0)

		if (pMobile ~= nil) then
			AiAgent(pMobile):setDefender(pKiller)
		end
	end
end

function MellichaeOutroTheater:doHealingPulse(pPlayer, arg)
	if (pPlayer == nil) then
		return
	end

	local theaterID = tonumber(arg)

	local pTheater = self:getTheaterObject(pPlayer)

	if (pTheater == nil or SceneObject(pTheater):getObjectID() ~= theaterID) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local numGreen = readData(playerID .. "greenShrines")
	local numRed = readData(playerID .. "redShrines")
	local healedSomething = false

	local daktarID = readData(playerID .. ":daktar")
	local pDaktar = getSceneObject(daktarID)

	if (pDaktar ~= nil and not CreatureObject(pDaktar):isDead() and numRed > 0) then
		self:healToFull(pDaktar)
		healedSomething = true
	end

	local mellichaeID = readData(playerID .. ":mellichae")
	local pMellichae = getSceneObject(mellichaeID)

	if (pMellichae ~= nil and not CreatureObject(pMellichae):isDead() and numRed > 0) then
		self:healToFull(pMellichae)
		healedSomething = true
	end

	for i = 1, 2, 1 do
		local redID = readData(playerID .. ":powershrines:red:" .. i)

		local pRed = getSceneObject(redID)

		if (pRed ~= nil and numGreen > 0) then
			self:healToFull(pRed)
			healedSomething = true
		end
	end

	if (healedSomething) then
		createEvent(10 * 1000, "MellichaeOutroTheater", "doHealingPulse", pPlayer, tostring(theaterID))
	end
end

function MellichaeOutroTheater:healToFull(pObj)
	if (pObj == nil) then
		return
	end

	SceneObject(pObj):playEffect("clienteffect/healing_healdamage.cef", "")

	if (SceneObject(pObj):isCreatureObject()) then
		for i = 0, 6, 3 do
			local maxHam = CreatureObject(pObj):getMaxHAM(i)
			CreatureObject(pObj):setHAM(i, maxHam)
		end
	else
		TangibleObject(pObj):setConditionDamage(0)
	end
end

function MellichaeOutroTheater:onTheaterDespawn(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	for i = 1, 2, 1 do
		local shrineID = readData(playerID .. ":powershrines:red:" .. i)

		local pShrine = getSceneObject(shrineID)

		if (pShrine ~= nil) then
			SceneObject(pShrine):destroyObjectFromWorld()
		end

		deleteData(shrineID .. "questOwner")
		deleteData(playerID .. ":powershrines:red:" .. i)

		shrineID = readData(playerID .. ":powershrines:green:" .. i)

		pShrine = getSceneObject(shrineID)

		if (pShrine ~= nil) then
			SceneObject(pShrine):destroyObjectFromWorld()
		end

		deleteData(shrineID .. "questOwner")
		deleteData(playerID .. ":powershrines:green:" .. i)
	end

	deleteData(playerID .. "redShrines")
	deleteData(playerID .. "greenShrines")

	local daktarID = readData(playerID .. ":daktar")
	deleteData(daktarID .. "questOwner")
	deleteData(playerID .. ":daktar")

	local mellichaeID = readData(playerID .. ":mellichae")
	deleteData(mellichaeID .. "questOwner")
	deleteData(playerID .. ":mellichae")
end

return MellichaeOutroTheater
