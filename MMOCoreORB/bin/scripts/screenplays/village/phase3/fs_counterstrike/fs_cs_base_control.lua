local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

FsCsBaseControl = {
	shieldRebootTime = 2 * 60 * 60 * 1000, -- 2 hours, shield will respawn after being dropped
	shieldRadius = 50, -- Radius of shield
	shieldExpelDistance = 10, -- How far back to push creatures from where they reached the shield
	shieldRemoteRange = 75, -- Range player must be in to use remote on shield

	reinforcementWaveMin = 90 * 1000, -- Min time before spawning a reinforcement wave
	reinforcementWaveMax = 180 * 1000, -- Max time before spawning a reinforcement wave

	-- Defense wave data
	lootMobDataTable = {
		spawnerPulse = 120 * 1000, -- Time between spawn pulses
		maxSpawn = 5, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 5, -- Max mobs to have up at any one time
		mobileLifespan = 1200 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 1200 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "setupLootMob" -- Name of function that should setup a defender after it's spawned
	},

	lootMobSpawnList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "sith_shadow_thug_nonaggro", 1, 1, 1 },
		{ "sith_shadow_pirate_nonaggro", 2, 3, 2 },
		{ "sith_shadow_outlaw_nonaggro", 2, 3, 2 },
	},

	maxLootMobGroups = 2, -- Max loot mob groups to have spawned at one time
	lootMobGroupMinDist = 200, -- Min distance to spawn from camp
	lootMobGroupMaxDist = 300, -- Max distance to spawn from camp
	lootMobSpawnerInterval = 1200 * 1000, -- Time until a new set of spawners are created

	droidTemplate = "fs_mouse_droid",
	maxDroids = 5,
	droidMinDist = 75,
	droidMaxDist = 100,

	-- Defense wave data
	smallWaveDataTable = {
		spawnerPulse = 10 * 1000, -- Time between spawn pulses
		maxSpawn = 10, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 10, -- Max mobs to have up at any one time
		mobileLifespan = 30 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 30 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "setupSpawnedDefender" -- Name of function that should setup a defender after it's spawned
	},

	smallWaveSpawnList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "sith_shadow_thug_nonaggro", 3, 5, 2 },
		{ "sith_shadow_thug_nonaggro", 3, 5, 2 },
		{ "sith_shadow_thug_nonaggro", 0, 1, 1 },
	},

	mediumWaveDataTable = {
		spawnerPulse = 10 * 1000, -- Time between spawn pulses
		maxSpawn = 15, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 15, -- Max mobs to have up at any one time
		mobileLifespan = 30 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 30 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "setupSpawnedDefender" -- Name of function that should setup a defender after it's spawned
	},

	mediumWaveSpawnList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "sith_shadow_thug_nonaggro", 5, 7, 2 },
		{ "sith_shadow_thug_nonaggro", 5, 7, 2 },
		{ "sith_shadow_thug_nonaggro", 0, 2, 1 },
	},

	defenseWaves = {
		small = { "smallWaveDataTable", "smallWaveSpawnList" },
		medium = { "mediumWaveDataTable", "mediumWaveSpawnList" }
	}
}

function FsCsBaseControl:notifyEnteredCampShieldArea(pArea, pObj)
	if (pArea == nil or pObj == nil or not SceneObject(pObj):isCreatureObject()) then
		return 0
	end

	local playerX = SceneObject(pObj):getWorldPositionX()
	local playerY = SceneObject(pObj):getWorldPositionY()

	local campX = SceneObject(pArea):getWorldPositionX()
	local campY = SceneObject(pArea):getWorldPositionY()

	local diffY = playerY - campY;
	local diffX = playerX - campX;

	local angle = math.atan2(diffY, diffX);
	local rad = self.shieldRadius + self.shieldExpelDistance

	local newX = campX + (math.cos(angle) * rad);
	local newY = campY + (math.sin(angle) * rad);
	local newZ = getTerrainHeight(pObj, newX, newY)

	CreatureObject(pObj):teleport(newX, newZ, newY, 0)

	if (SceneObject(pObj):isPlayerCreature()) then
		CreatureObject(pObj):sendSystemMessage("@fs_quest_village:expel_shield")
	end
	return 0
end

function FsCsBaseControl:spawnSurveillanceDroids(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local campNum = readData(theaterID .. ":campNum")
	local campName = FsCounterStrike.campSpawns[campNum][1]

	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	for i = 1, self.maxDroids, 1 do
		local spawnPoint = getSpawnPoint("dathomir", theaterX, theaterY, self.droidMinDist, self.droidMaxDist, true)
		local pMobile = spawnMobile("dathomir", self.droidTemplate, 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0)

		if (pMobile ~= nil) then
			local mobileID = SceneObject(pMobile):getObjectID()
			writeData(mobileID .. ":surveillanceDroidNum", i)
			writeData(theaterID .. ":surveillanceDroid" .. i, mobileID)
			writeData(mobileID .. ":theaterID", theaterID)
			createObserver(OBJECTDESTRUCTION, "FsCsBaseControl", "notifyKilledDroid", pMobile)
			SceneObject(pMobile):setCustomObjectName(getStringId("@fs_quest_village:name_mdroid_" .. campName))
		end
	end
end

function FsCsBaseControl:notifyKilledDroid(pVictim, pAttacker)
	if (pVictim == nil) then
		return 1
	end

	playClientEffectLoc(SceneObject(pVictim):getObjectID(), "clienteffect/combat_explosion_lair_large.cef", "dathomir", SceneObject(pVictim):getPositionX(), SceneObject(pVictim):getPositionZ(), SceneObject(pVictim):getPositionY(), 0)

	local victimID = SceneObject(pVictim):getObjectID()
	local theaterID = readData(victimID .. ":theaterID")
	local droidNum = readData(victimID .. ":surveillanceDroidNum")

	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		return 1
	end

	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	local campNum = readData(theaterID .. ":campNum")
	local campName = FsCounterStrike.campSpawns[campNum][1]

	local spawnPoint = getSpawnPoint("dathomir", theaterX, theaterY, self.droidMinDist, self.droidMaxDist, true)
	local pMobile = spawnMobile("dathomir", self.droidTemplate, 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0)

	if (pMobile ~= nil) then
		local mobileID = SceneObject(pMobile):getObjectID()
		writeData(mobileID .. ":theaterID", theaterID)
		writeData(mobileID .. ":surveillanceDroidNum", droidNum)
		writeData(theaterID .. ":surveillanceDroid" .. droidNum, mobileID)
		createObserver(OBJECTDESTRUCTION, "FsCsBaseControl", "notifyKilledDroid", pMobile)
		SceneObject(pMobile):setCustomObjectName(getStringId("@fs_quest_village:name_mdroid_" .. campName))
	end

	deleteData(victimID .. ":theaterID")
	deleteData(victimID .. ":surveillanceDroidNum")
	return 1
end

function FsCsBaseControl:notifyDestructibleDisabled(pVictim, pAttacker)
	if (pVictim == nil) then
		return 1
	end

	if (pAttacker ~= nil) then
		playClientEffectLoc(SceneObject(pAttacker):getObjectID(), "clienteffect/combat_explosion_lair_large.cef", "dathomir", SceneObject(pVictim):getPositionX(), SceneObject(pVictim):getPositionZ(), SceneObject(pVictim):getPositionY(), 0)
	end

	createEvent(2000, "FsCsBaseControl", "destroyDestructible", pVictim, "")

	return 1
end

function FsCsBaseControl:destroyDestructible(pDestructible)
	if (pDestructible == nil) then
		return
	end

	SceneObject(pDestructible):destroyObjectFromWorld()
end


function FsCsBaseControl:spawnLootMobGroup(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	local spawnPoint = getSpawnPoint("dathomir", theaterX, theaterY, self.lootMobGroupMinDist, self.lootMobGroupMaxDist, true)
	QuestSpawner:createQuestSpawner("FsCsBaseControl", "lootMobDataTable", "lootMobSpawnList", spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, "dathomir", pTheater)
end

function FsCsBaseControl:setupLootMob(pMobile)
	if (pMobile == nil) then
		return
	end

	createObserver(OBJECTDESTRUCTION, "FsCsBaseControl", "notifyKilledLootMobile", pMobile)
end

function FsCsBaseControl:notifyKilledLootMobile(pVictim, pAttacker)
	if (pVictim == nil or getRandomNumber(1,100) < 80) then
		return 1
	end

	local pInventory = CreatureObject(pVictim):getSlottedObject("inventory")

	if pInventory == nil then
		return 1
	end

	createLoot(pInventory, "cs_datapad", 0, true)

	for i = 0, SceneObject(pInventory):getContainerObjectsSize() - 1, 1 do
		local pItem = SceneObject(pInventory):getContainerObject(i)

		if pItem ~= nil and SceneObject(pItem):getTemplateObjectPath() == "object/tangible/loot/quest/force_sensitive/camp_frequency_datapad.iff" or SceneObject(pItem):getTemplateObjectPath() == "object/tangible/loot/quest/force_sensitive/camp_waypoint_datapad.iff" then
			local csItem = LuaFsCsObject(pItem)
			csItem:setPhaseDuration(VillageJediManagerTownship.getVillagePhaseDuration())
		end
	end

	return 1
end


function FsCsBaseControl:spawnLootMobGroups(pTheater)
	if (pTheater == nil) then
		return
	end

	for i = 1, self.maxLootMobGroups, 1 do
		self:spawnLootMobGroup(pTheater)
	end

	createEvent(self.lootMobSpawnerInterval, "FsCsBaseControl", "spawnLootMobGroups", pTheater, "")
end

function FsCsBaseControl:erectShield(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	if (not self:isShieldPoweredDown(pTheater)) then
		printLuaError("Error generating shield in FsCsBaseControl:erectShield, existing shield found.")
		return
	end

	local pActiveArea = spawnActiveArea("dathomir", "object/active_area.iff", SceneObject(pTheater):getWorldPositionX(), SceneObject(pTheater):getWorldPositionZ(), SceneObject(pTheater):getWorldPositionY(), self.shieldRadius, 0)

	if pActiveArea ~= nil then
		writeData(theaterID .. ":shieldID", SceneObject(pActiveArea):getObjectID())
		createEvent(10000, "FsCsBaseControl", "createShieldObserver", pActiveArea, "")
		deleteData(theaterID .. ":shieldPowerDownTime")
		deleteData(theaterID .. ":shieldPoweredDown")

		local playerTable = SceneObject(pActiveArea):getPlayersInRange(self.shieldRadius)

		for i = 1, #playerTable, 1 do
			local pPlayer = playerTable[i]

			if (pPlayer ~= nil) then
				self:notifyEnteredCampShieldArea(pActiveArea, pPlayer)
			end
		end
	end
end

function FsCsBaseControl:createShieldObserver(pActiveArea)
	if (pActiveArea == nil) then
		return
	end

	createObserver(ENTEREDAREA, "FsCsBaseControl", "notifyEnteredCampShieldArea", pActiveArea)
end

function FsCsBaseControl:isShieldPoweredDown(pTheater)
	local theaterID = SceneObject(pTheater):getObjectID()
	local shieldID = readData(theaterID .. ":shieldID")

	local pShield = getSceneObject(shieldID)

	return pShield == nil or readData(theaterID .. ":shieldPoweredDown") == 1
end

function FsCsBaseControl:attemptPowerDownShield(pPlayer, campName)
	if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:shield_remote_cant_use")
		return false
	end

	local zoneName = SceneObject(pPlayer):getZoneName()

	if (zoneName ~= "dathomir") then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:remote_nothing_happens")
		return false
	end

	local pCityRegion = getCityRegionAt(SceneObject(pPlayer):getZoneName(), SceneObject(pPlayer):getWorldPositionX(), SceneObject(pPlayer):getWorldPositionY())

	if (pCityRegion ~= nil and CityRegion(pCityRegion):isClientRegion()) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:shield_remote_interference")
		return false
	end

	for i = 1, #FsCounterStrike.campSpawns, 1 do
		local tempCampName = FsCounterStrike.campSpawns[i][1]
		local theaterID = readData("VillageCounterStrikeCampID:" .. tempCampName)
		local pTheater = getSceneObject(theaterID)

		if (pTheater ~= nil and SceneObject(pPlayer):isInRangeWithObject(pTheater, self.shieldRemoteRange)) then
			if (tempCampName == campName) then
				if (self:isShieldPoweredDown(pTheater)) then
					CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:remote_shield_down_already")
					return false
				end

				if (CreatureObject(pPlayer):isGrouped()) then
					local groupSize = CreatureObject(pPlayer):getGroupSize()

					for i = 0, groupSize - 1, 1 do
						local pMember = CreatureObject(pPlayer):getGroupMember(i)
						if pMember ~= nil and SceneObject(pMember):isInRangeWithObject(pPlayer, 100) then
							CreatureObject(pMember):sendSystemMessage("@fs_quest_village:remote_powering_down")
						end
					end
				else
					CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:remote_powering_down")
				end

				writeData(theaterID .. ":attackerID", SceneObject(pPlayer):getObjectID())
				writeData(SceneObject(pPlayer):getObjectID() .. ":csTheater", theaterID)

				self:powerDownShield(pTheater)
				QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)
				QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS)
				createObserver(KILLEDCREATURE, "FsCsBaseControl", "notifyKilledGuard", pPlayer)

				CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_cs_step_intro_complete")

				return true
			else
				CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:shield_remote_wrong_camp")
				return false
			end
		end
	end

	CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:remote_nothing_happens")
	return false
end

function FsCsBaseControl:notifyKilledGuard(pPlayer, pVictim)
	if pVictim == nil or pPlayer == nil then
		return 0
	end

	if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS) or QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS)) then
		return 1
	end

	local pQuest = getQuestInfo("fs_cs_kill5_guards")

	if (pQuest == nil) then
		return 0
	end

	local quest = LuaQuestInfo(pQuest)
	local killsRequired = quest:getQuestParameter()
	local killTarget = quest:getQuestTarget()

	if (SceneObject(pVictim):getObjectName() ~= killTarget) then
		return 0
	end

	local victimID = SceneObject(pVictim):getObjectID()
	local theaterID = readData(victimID .. ":theaterID")
	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local killedGuardCount = readData(playerID .. ":FsCsBaseControl:guardsKilled")
	killedGuardCount = killedGuardCount + 1

	if (killedGuardCount == 5) then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)
		FsCsCommander:createCommander(pTheater)
		deleteData(playerID .. ":FsCsBaseControl:guardsKilled")

		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_cs_ensure_detail")

		if (CreatureObject(pPlayer):isGrouped()) then
			local groupSize = CreatureObject(pPlayer):getGroupSize()

			for i = 0, groupSize - 1, 1 do
				local pMember = CreatureObject(pPlayer):getGroupMember(i)
				if pMember ~= nil and pMember ~= pPlayer and SceneObject(pMember):isInRangeWithObject(pPlayer, 100) and QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_INTRO) then
					CreatureObject(pMember):sendSystemMessage("@fs_quest_village:groupmate_powered_down")
				end
			end
		end
		return 1
	else
		local messageString = LuaStringIdChatParameter("@quest/quests:kill_credit")
		messageString:setTO(getStringId(quest:getJournalSummary()))
		messageString:setDI(killsRequired - killedGuardCount)
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
		writeData(playerID .. ":FsCsBaseControl:guardsKilled", killedGuardCount)
		deleteData(victimID .. ":theaterID")
	end

	return 0
end

function FsCsBaseControl:powerDownShield(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local shieldID = readData(theaterID .. ":shieldID")

	local pShield = getSceneObject(shieldID)

	if (self:isShieldPoweredDown(pTheater)) then
		return
	end

	if (pShield ~= nil) then
		SceneObject(pShield):destroyObjectFromWorld()
	end

	local door1ID = readData(theaterID .. "campDoor1")
	local pDoor1 = getSceneObject(door1ID)

	if (pDoor1 ~= nil) then
		TangibleObject(pDoor1):clearOptionBit(INVULNERABLE)
	end

	local door2ID = readData(theaterID .. "campDoor2")
	local pDoor2 = getSceneObject(door2ID)

	if (pDoor2 ~= nil) then
		TangibleObject(pDoor2):clearOptionBit(INVULNERABLE)
	end

	local antennaID = readData(theaterID .. "antenna")
	local pAntenna = getSceneObject(antennaID)

	if (pAntenna ~= nil) then
		TangibleObject(pAntenna):clearOptionBit(INVULNERABLE)
	end
	local attackerID = readData(theaterID .. ":attackerID")
	writeData(theaterID .. ":shieldPowerDownTime", os.time())
	writeData(theaterID .. ":shieldPoweredDown", 1)
	createEvent(self.shieldRebootTime, "FsCsBaseControl", "resetCamp", pTheater, attackerID)

	deleteData(theaterID .. ":shouldStopSpawn")
	self:spawnDefenseWaves(pTheater)
end

function FsCsBaseControl:spawnDefenseWaves(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	-- This is set when the player begins the escort portion
	local shouldStopSpawn = readData(theaterID .. ":shouldStopSpawn")

	if (shouldStopSpawn == 1) then
		deleteData(theaterID .. ":shouldStopSpawn")
		return
	end

	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	local nearbyPlayers = SceneObject(pTheater):getPlayersInRange(100)

	if (nearbyPlayers ~= nil) then
		local waveData = { self.defenseWaves.small }
		local antennaExists = self:ifAntennaExists(pTheater)

		if (#nearbyPlayers > 30) then
			if (antennaExists) then
				waveData = { self.defenseWaves.small, self.defenseWaves.small, self.defenseWaves.medium, self.defenseWaves.medium }
			else
				waveData = { self.defenseWaves.small, self.defenseWaves.small, self.defenseWaves.medium }
			end
		elseif (#nearbyPlayers > 20) then
			if (antennaExists) then
				waveData = { self.defenseWaves.small, self.defenseWaves.small, self.defenseWaves.medium }
			else
				waveData = { self.defenseWaves.small, self.defenseWaves.medium }
			end
		elseif (#nearbyPlayers > 10) then
			if (antennaExists) then
				waveData = { self.defenseWaves.small, self.defenseWaves.medium }
			else
				waveData = { self.defenseWaves.medium }
			end
		end

		for i = 1, #waveData, 1 do
			local spawnPoint = getSpawnPoint("dathomir", theaterX, theaterY, 75, 110, true)
			QuestSpawner:createQuestSpawner("FsCsBaseControl", waveData[i][1], waveData[i][2], spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, "dathomir", pTheater)
		end
	end

	createEvent(getRandomNumber(self.reinforcementWaveMin, self.reinforcementWaveMax), "FsCsBaseControl", "spawnDefenseWaves", pTheater, "")
end

function FsCsBaseControl:resetCamp(pTheater, attackerID, override)
	if (pTheater == nil) then
		return
	end

	attackerID = tonumber(attackerID)
	local theaterID = SceneObject(pTheater):getObjectID()
	local storedAttackerID = readData(theaterID .. ":attackerID")

	if (storedAttackerID ~= attackerID and not override) then
		return
	end

	-- In case the defense waves are still spawning
	writeData(theaterID .. ":shouldStopSpawn", 1)

	deleteData(theaterID .. ":attackerID")
	deleteData(attackerID .. ":csTheater")

	local turret1ID = readData(theaterID .. "turret1")
	local pTurret1 = getSceneObject(turret1ID)

	if (pTurret1 ~= nil) then
		SceneObject(pTurret1):destroyObjectFromWorld()
	end

	local turret2ID = readData(theaterID .. "turret2")
	local pTurret2 = getSceneObject(turret2ID)

	if (pTurret2 ~= nil) then
		SceneObject(pTurret2):destroyObjectFromWorld()
	end

	local turret3ID = readData(theaterID .. "turret3")
	local pTurret3 = getSceneObject(turret3ID)

	if (pTurret3 ~= nil) then
		SceneObject(pTurret3):destroyObjectFromWorld()
	end

	local door1ID = readData(theaterID .. "campDoor1")
	local pDoor1 = getSceneObject(door1ID)

	if (pDoor1 ~= nil) then
		SceneObject(pDoor1):destroyObjectFromWorld()
	end

	local door2ID = readData(theaterID .. "campDoor2")
	local pDoor2 = getSceneObject(door2ID)

	if (pDoor2 ~= nil) then
		SceneObject(pDoor2):destroyObjectFromWorld()
	end

	local antennaID = readData(theaterID .. "antenna")
	local pAntenna = getSceneObject(antennaID)

	if (pAntenna ~= nil) then
		SceneObject(pAntenna):destroyObjectFromWorld()
	end

	self:erectShield(pTheater)

	local campNum = readData(theaterID .. ":campNum")
	local campLoc = FsCounterStrike.campSpawns[campNum]
	local campName = campLoc[1]

	local spawnedFirstDoor = false
	local spawnedFirstTurret = false
	local spawnedSecondTurret = false

	for i = 1, #FsCounterStrike.campLayout, 1 do
		local objectData = FsCounterStrike.campLayout[i]

		if (objectData[1] == "object/installation/battlefield/destructible/bfield_base_gate_impl.iff" or objectData[1] == "object/installation/battlefield/destructible/antenna_tatt_style_1.iff" or objectData[1] == "object/installation/turret/turret_fs_cs.iff") then
			local pObject = spawnSceneObject("dathomir", objectData[1], campLoc[2] + objectData[2], campLoc[3]  + objectData[3], campLoc[4] + objectData[4], 0, math.rad(objectData[5]))

			if (pObject ~= nil) then
				writeData(theaterID .. "theaterObject" .. i, SceneObject(pObject):getObjectID())

				if (objectData[1] == "object/installation/battlefield/destructible/bfield_base_gate_impl.iff") then
					if (spawnedFirstDoor) then
						writeData(theaterID .. "campDoor2", SceneObject(pObject):getObjectID())
					else
						writeData(theaterID .. "campDoor1", SceneObject(pObject):getObjectID())
						spawnedFirstDoor = true
					end
					createObserver(OBJECTDISABLED, "FsCsBaseControl", "notifyDestructibleDisabled", pObject)
					TangibleObject(pObject):setOptionBit(INVULNERABLE)
				elseif (objectData[1] == "object/installation/turret/turret_fs_cs.iff") then
					if (spawnedFirstTurret and spawnedSecondTurret) then
						writeData(theaterID .. "turret3", SceneObject(pObject):getObjectID())
					elseif (spawnedFirstTurret) then
						writeData(theaterID .. "turret2", SceneObject(pObject):getObjectID())
						spawnedSecondTurret = true
					else
						writeData(theaterID .. "turret1", SceneObject(pObject):getObjectID())
						spawnedFirstTurret = true
					end
				elseif (objectData[1] == "object/installation/battlefield/destructible/antenna_tatt_style_1.iff") then
					writeData(theaterID .. "antenna", SceneObject(pObject):getObjectID())
					createObserver(OBJECTDISABLED, "FsCsBaseControl", "notifyDestructibleDisabled", pObject)
					TangibleObject(pObject):setOptionBit(INVULNERABLE)
				end
			end
		end
	end
end

function FsCsBaseControl:setupSpawnedDefender(pMobile)
	if (pMobile == nil) then
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	local spawnerID = readData(mobileID .. ":spawnerID")

	local pSpawner = getSceneObject(spawnerID)

	if pSpawner == nil then
		return
	end

	local theaterID = readData(spawnerID .. ":parentID")

	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		return
	end

	writeData(mobileID .. ":theaterID", theaterID)

	createEvent(getRandomNumber(10, 30) * 1000, "FsCsBaseControl", "doMobileSpatial", pMobile, "")

	AiAgent(pMobile):setAiTemplate("villageraider")
	AiAgent(pMobile):setFollowState(4)

	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterZ = SceneObject(pTheater):getWorldPositionZ()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	local door1Index = readData(theaterID .. ":campDoor1Index")
	local door1Data = FsCounterStrike.campLayout[door1Index]

	local door1X = theaterX + door1Data[2]
	local door1Z = theaterZ + door1Data[3]
	local door1Y = theaterY + door1Data[4] + 4 -- Adjust to be slightly outside gate

	local distToDoor1 = SceneObject(pMobile):getDistanceToPosition(door1X, door1Z, door1Y)

	local door2Index = readData(theaterID .. ":campDoor2Index")
	local door2Data = FsCounterStrike.campLayout[door2Index]

	local door2X = theaterX + door2Data[2]
	local door2Z = theaterZ + door2Data[3]
	local door2Y = theaterY + door2Data[4] - 4 -- Adjust to be slightly outside gate

	local distToDoor2 = SceneObject(pMobile):getDistanceToPosition(door2X, door2Z, door2Y)

	local door1ID = readData(theaterID .. "campDoor1")
	local pDoor1 = getSceneObject(door1ID)
	local door1Destroyed = false

	if (pDoor1 == nil) then
		door1Destroyed = true
	end

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)

	if (distToDoor1 < distToDoor2 or not door1Destroyed) then
		AiAgent(pMobile):setNextPosition(door1X, door1Z, door1Y, 0)
		AiAgent(pMobile):setHomeLocation(door1X, door1Z, door1Y, 0)
	else
		AiAgent(pMobile):setNextPosition(door2X, door2Z, door2Y, 0)
		AiAgent(pMobile):setHomeLocation(door2X, door2Z, door2Y, 0)
	end

	AiAgent(pMobile):executeBehavior()
end

function FsCsBaseControl:doMobileSpatial(pMobile)
	if (pMobile == nil or getRandomNumber(100) <= 75) then
		return
	end

	spatialChat(pMobile, "@fs_quest_village:camp_defender_" .. getRandomNumber(1,10))
end

function FsCsBaseControl:ifAntennaExists(pTheater)
	if (pTheater == nil) then
		return false
	end

	local antennaID = readData(SceneObject(pTheater):getObjectID() .. "antenna")

	local pAntenna = getSceneObject(antennaID)

	return pAntenna ~= nil
end
