local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

FsCounterStrike = {
	shieldRebootTime = 2 * 60 * 1000, -- 2 hours, shield will respawn after being dropped
	shieldRadius = 50, -- Radius of shield
	shieldExpelDistance = 10, -- How far back to push creatures from where they reached the shield
	shieldRemoteRange = 75, -- Range player must be in to use remote on shield
	maxCampsToSpawn = 20, -- Number of camps to spawn from campSpawns on phase change

	reinforcementWaveMin = 90 * 1000, -- Min time before spawning a reinforcement wave
	reinforcementWaveMax = 180 * 1000, -- Max time before spawning a reinforcement wave

	commanderDespawnTime = 60 * 60 * 1000, -- Time after spawning before commander automatically despawns

	-- Spawn locations for camps, names found in string file string/en/fs_quest_village.stf
	campSpawns = {
		{ "alpha", 5939, 122, -2030 },
		{ "beta", 5313, 135, -1145 },
		{ "gamma", 4072, 127, -1402 },
		{ "delta", 3456, 150, -1258 },
		{ "epsilon", 2960, 150, 45 },
		{ "zeta", 3041, 138, 787 },
		{ "eta", 1073, 121, 1860 },
		{ "theta", 642, 136, 732 },
		{ "iota", -53, 119, -165 },
		{ "kappa", -376, 128, -1856 },
		{ "lamda", -1022, 125, -2932 },
		{ "mu", -392, 40, -6004 },
		{ "nu", -737, 105, -5158 },
		{ "xi", -1663, 92, -4690 },
		{ "omikron", -2850, 94, -2366 },
		{ "pi", -3824, 94, -3011 },
		{ "rho", -3961, 89, -2606 },
		{ "sigma", -2932, 129, 738 },
		{ "tau", -3113, 124, 1171 },
		{ "ypsylon", -1676, 140, 1651 },
		{ "phy", -1977, 127, 2234 },
		{ "chi", -1092, 119, 2343 },
		{ "psi", -410, 120, 2506 },
		{ "omega", 1369, 134, 1217 },
		{ "zed", 3076, 126, 2174 }
	},

	campLayout = {
		{ "object/installation/battlefield/destructible/bfield_base_gate_impl.iff", 0.522045, 0, 18.2801, -0.572958 },
		{ "object/installation/battlefield/destructible/bfield_base_gate_impl.iff", 1.77535, 0, -15.1494, 174.362 },
		{ "object/installation/battlefield/destructible/antenna_tatt_style_1.iff", 0.835004, 0, 0.202488, 0 },
		{ "object/static/structure/military/military_wall_strong_imperial_16_style_01.iff", 18.345, 0, 4.03223, 40.9893 },
		{ "object/static/structure/general/poi_all_construction_metal_pile.iff", 8.90947, 0, 15.836, -89.3814 },
		{ "object/static/structure/military/military_wall_strong_imperial_16_style_01.iff", 6.67129, 0, -1.93569, 40.9893 },
		{ "object/static/structure/military/military_wall_strong_imperial_style_01.iff", 11.9582, 0, 14.0823, 90.0002 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 24.6294, 0, -1.59597, 90 },
		{ "object/static/structure/military/military_wall_strong_imperial_style_01.iff", 24.5319, 0, -6.05201, 90.0002 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 4.18254, 0, 17.2465, 180 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 0.823005, 0, 3.1446, 0 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 11.9202, 0, 9.636, 90 },
		{ "object/static/structure/military/military_wall_strong_imperial_style_01.iff", 7.52737, 0, 18.4214, 0.000229183 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 4.18149, 0, 19.4444, 0 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 11.9418, 0, 18.3991, 0 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 12.9969, 0, -7.39329, 87.1346 },
		{ "object/static/structure/corellia/corl_tent_hut_s01.iff", 1.51926, 0, -5.7829, 52.7122 },
		{ "object/static/structure/military/military_wall_strong_imperial_16_style_01.iff", -16.3125, 0, 3.03114, -48.4377 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", -10.6532, 0, 9.3154, -90 },
		{ "object/static/structure/military/military_wall_strong_imperial_style_01.iff", -6.17186, 0, 18.0959, 0.000229183 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", -2.88365, 0, 17.0552, 180 },
		{ "object/static/structure/military/military_wall_strong_imperial_16_style_01.iff", -4.33674, 0, -2.69771, -49.0107 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", -9.82547, 0, -9.04249, -92.8648 },
		{ "object/static/structure/corellia/corl_tent_small.iff", -18.4757, 0, -8.0064, -0.57296 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", -2.8847, 0, 19.2532, 0 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", -10.6163, 0, 18.1009, 0 },
		{ "object/static/structure/military/military_wall_strong_imperial_style_01.iff", -10.6387, 0, 13.6865, -89.9988 },
		{ "object/static/structure/corellia/corl_power_box_node.iff", -6.86604, 0, 14.5385, 0 },
		{ "object/static/structure/general/camp_lawn_chair_s01.iff", -18.9841, 0, -9.30699, 59.5876 },
		{ "object/static/structure/general/camp_lawn_chair_s01.iff", -19.1337, 0, -6.66489, 119.748 },
		{ "object/static/structure/military/military_wall_strong_imperial_32_style_01.iff", -9.90447, 0, -23.2876, -137.028 },
		{ "object/static/structure/military/military_wall_strong_imperial_style_01.iff", -21.9327, 0, -7.75796, -89.999 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", -21.8947, 0, -3.31164, -45 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 6.97002, 0, -14.0415, 177.135 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", -3.22971, 0, -15.0271, 177.135 },
		{ "object/static/structure/corellia/corl_tent_small.iff", 12.9296, 0, -12.3799, 41.2529 },
		{ "object/static/structure/military/military_wall_strong_imperial_32_style_01.iff", 13.3876, 0, -22.4914, 132.972 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 2.10616, 0, -34.4694, 180 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", -21.9377, 0, -12.2024, -90 },
		{ "object/static/structure/military/military_column_strong_imperial_style_01.iff", 24.5863, 0, -10.4868, 89.9992 },
		{ "object/static/structure/military/military_wall_strong_imperial_style_01.iff", -6.55375, 0, -12.0536, -137.864 },
		{ "object/static/structure/military/military_wall_strong_imperial_style_01.iff", 9.98578, 0, -10.665, -47.8645 },
		{ "object/installation/turret/turret_fs_cs.iff", -0.26149, 0, 5.8774, 0 },
		{ "object/installation/turret/turret_fs_cs.iff", 10.7884, 0, 26.21477, 0 },
		{ "object/installation/turret/turret_fs_cs.iff", -12.5269, 0, 25.66261, 0 },
	},

	lootMobGroupList = {
		{ template = "sith_shadow_thug_cs_nonaggro", minimumDistance = 5, maximumDistance = 16, referencePoint = 0 },
		{ template = "sith_shadow_pirate_cs_nonaggro", minimumDistance = 4, maximumDistance = 14, referencePoint = 0 },
		{ template = "sith_shadow_pirate_cs_nonaggro", minimumDistance = 4, maximumDistance = 14, referencePoint = 0 },
		{ template = "sith_shadow_outlaw_cs_nonaggro", minimumDistance = 6, maximumDistance = 12, referencePoint = 0 },
		{ template = "sith_shadow_outlaw_cs_nonaggro", minimumDistance = 6, maximumDistance = 12, referencePoint = 0 }
	},
	maxLootMobGroups = 2, -- Max loot mob groups to have spawned at one time
	lootMobGroupMinDist = 200, -- Min distance to spawn from camp
	lootMobGroupMaxDist = 300, -- Max distance to spawn from camp

	droidTemplate = "fs_mouse_droid",
	maxDroids = 5,
	droidMinDist = 75,
	droidMaxDist = 100,

	-- Defense wave data
	smallWaveDataTable = {
		spawnerPulse = 10 * 1000, -- Time between spawn pulses
		maxSpawn = 10, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 10, -- Max mobs to have up at any one time
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

function FsCounterStrike:pickPhaseCamps()
	local chosenCamps = { }
	local allCamps = { }

	for i = 1, #self.campSpawns, 1 do
		table.insert(allCamps, i)
	end

	for i = 1, self.maxCampsToSpawn, 1 do
		local randCamp = getRandomNumber(1, #allCamps)
		table.insert(chosenCamps, allCamps[randCamp])
		table.remove(allCamps, randCamp)
	end

	table.sort(chosenCamps)
	local campList = table.concat(chosenCamps, ",")

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	setQuestStatus("VillageCounterStrikeCampList:" .. phaseID, campList)
	self:spawnCamps()
end

function FsCounterStrike:getCampNumFromName(campName)
	if (campName == "" or campName == nil) then
		return nil
	end

	for i = 1, #self.campSpawns, 1 do
		if (self.campSpawns[i][1] == campName) then
			return i
		end
	end

	return nil
end

function FsCounterStrike:getPhaseCampList()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	return getQuestStatus("VillageCounterStrikeCampList:" .. phaseID)
end

function FsCounterStrike:notifyEnteredCampShieldArea(pArea, pObj)
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

function FsCounterStrike:spawnSurveillanceDroids(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local campNum = readData(theaterID .. ":campNum")
	local campName = self.campSpawns[campNum][1]

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
			createObserver(OBJECTDESTRUCTION, "FsCounterStrike", "notifyKilledDroid", pMobile)
			SceneObject(pMobile):setCustomObjectName(getStringId("@fs_quest_village:name_mdroid_" .. campName))
		end
	end

end

function FsCounterStrike:notifyKilledDroid(pVictim, pAttacker)
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
	local campName = self.campSpawns[campNum][1]

	local spawnPoint = getSpawnPoint("dathomir", theaterX, theaterY, self.droidMinDist, self.droidMaxDist, true)
	local pMobile = spawnMobile("dathomir", self.droidTemplate, 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0)

	if (pMobile ~= nil) then
		local mobileID = SceneObject(pMobile):getObjectID()
		writeData(mobileID .. ":theaterID", theaterID)
		writeData(mobileID .. ":surveillanceDroidNum", droidNum)
		writeData(theaterID .. ":surveillanceDroid" .. droidNum, mobileID)
		createObserver(OBJECTDESTRUCTION, "FsCounterStrike", "notifyKilledDroid", pMobile)
		SceneObject(pMobile):setCustomObjectName(getStringId("@fs_quest_village:name_mdroid_" .. campName))
	end

	deleteData(victimID .. ":theaterID")
	deleteData(victimID .. ":surveillanceDroidNum")
	return 1
end

function FsCounterStrike:notifyDestructibleKilled(pVictim, pAttacker)
	if (pVictim == nil) then
		return 1
	end

	playClientEffectLoc(SceneObject(pVictim):getObjectID(), "clienteffect/combat_explosion_lair_large.cef", "dathomir", SceneObject(pVictim):getPositionX(), SceneObject(pVictim):getPositionZ(), SceneObject(pVictim):getPositionY(), 0)

	SceneObject(pVictim):destroyObjectFromWorld()

	return 1
end

function FsCounterStrike:spawnLootMobGroup(pTheater, id)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	local spawnPoint = getSpawnPoint("dathomir", theaterX, theaterY, self.lootMobGroupMinDist, self.lootMobGroupMaxDist, true)
	local pSpawnLoc = spawnSceneObject("dathomir", "object/static/structure/nobuild/nobuild_32.iff", spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0)

	if (pSpawnLoc == nil) then
		return
	end

	local spawnLocID = SceneObject(pSpawnLoc):getObjectID()
	writeData(theaterID .. ":lootSpawnGroup" .. id, spawnLocID)
	writeData(spawnLocID .. ":theaterID", theaterID)
	writeData(spawnLocID .. ":spawnGroupNum", id)

	local spawnedMobileList = SpawnMobiles.spawnMobiles(pSpawnLoc, "FsCounterStrike", self.lootMobGroupList, true)
	writeData(theaterID .. ":lootSpawnGroup" .. id .. ":killableCount", #spawnedMobileList)

	for i = 1, #spawnedMobileList, 1 do
		if (spawnedMobileList[i] ~= nil) then
			writeData(SceneObject(spawnedMobileList[i]):getObjectID() .. ":spawnGroupID", spawnLocID)
			createObserver(OBJECTDESTRUCTION, "FsCounterStrike", "notifyKilledLootMobile", spawnedMobileList[i])
		end
	end
end

function FsCounterStrike:destroyLootMobGroup(pTheater, id)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local spawnGroupID = readData(theaterID .. ":lootSpawnGroup" .. id)

	local pSpawnGroup = getSceneObject(spawnGroupID)

	if (pSpawnGroup == nil) then
		return
	end

	local mobileList = SpawnMobiles.getSpawnedMobiles(pSpawnGroup, "FsCounterStrike")

	for i = 1, #mobileList, 1 do
		if (mobileList[i] ~= nil and not CreatureObject(mobileList[i]):isDead()) then
			deleteData(SceneObject(mobileList[i]):getObjectID() .. ":spawnGroupID")
			dropObserver(OBJECTDESTRUCTION, mobileList[i])
			SceneObject(mobileList[i]):destroyObjectFromWorld()
		end
	end

	SceneObject(pSpawnGroup):destroyObjectFromWorld()

	deleteData(theaterID .. ":lootSpawnGroup" .. id)
	deleteData(spawnGroupID .. ":theaterID")
	deleteData(spawnGroupID .. ":spawnGroupNum")
	deleteData(theaterID .. ":lootSpawnGroup" .. id .. ":killableCount")
end

function FsCounterStrike:notifyKilledLootMobile(pVictim, pAttacker)
	if (pVictim == nil) then
		return 1
	end

	local spawnGroupID = readData(SceneObject(pVictim):getObjectID() .. ":spawnGroupID")
	local spawnGroupNum = readData(spawnGroupID .. ":spawnGroupNum")
	local theaterID = readData(spawnGroupID .. ":theaterID")

	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		return 1
	end

	local numEnemies = readData(theaterID .. ":lootSpawnGroup" .. spawnGroupNum .. ":killableCount")
	numEnemies = numEnemies - 1
	writeData(theaterID .. ":lootSpawnGroup" .. spawnGroupNum .. ":killableCount", numEnemies)

	deleteData(SceneObject(pVictim):getObjectID() .. ":spawnGroupID")

	if (numEnemies <= 0) then
		self:destroyLootMobGroup(pTheater, spawnGroupNum)
		self:spawnLootMobGroup(pTheater, spawnGroupNum)
	end

	local pInventory = CreatureObject(pVictim):getSlottedObject("inventory")

	if pInventory == nil then
		return 1
	end

	for i = 1, SceneObject(pInventory):getContainerObjectsSize(), 1 do
		local pItem = SceneObject(pInventory):getContainerObject(i)

		if pItem ~= nil then
			local csItem = LuaFsCsObject(pItem)
			csItem:setPhaseDuration(VillageJediManagerTownship.getVillagePhaseChangeTime())
		end
	end

	return 1
end

function FsCounterStrike:spawnLootMobGroups(pTheater)
	if (pTheater == nil) then
		return
	end

	for i = 1, self.maxLootMobGroups, 1 do
		self:spawnLootMobGroup(pTheater, i)
	end
end

function FsCounterStrike:spawnCamps()
	local campList = self:getPhaseCampList()
	local campTable = HelperFuncs:splitString(campList, ",")

	for i = 1, #campTable, 1 do
		local campNum = tonumber(campTable[i])
		local campLoc = self.campSpawns[campNum]
		local campName = campLoc[1]

		local pTheater = spawnSceneObject("dathomir", "object/static/structure/nobuild/nobuild_32.iff", campLoc[2], campLoc[3], campLoc[4], 0, 0)

		if (pTheater == nil) then
			printf("Error creating theater in FsCounterStrike:spawnCamps()\n")
			return
		end

		local theaterID = SceneObject(pTheater):getObjectID()
		writeData("VillageCounterStrikeCampID:" .. campName, theaterID)
		writeData(theaterID .. ":campNum", campNum)

		self:erectShield(pTheater)

		local spawnedFirstDoor = false
		local spawnedFirstTurret = false
		local spawnedSecondTurret = false

		for i = 1, #self.campLayout, 1 do
			local objectData = self.campLayout[i]
			local pObject = spawnSceneObject("dathomir", objectData[1], campLoc[2] + objectData[2], campLoc[3]  + objectData[3], campLoc[4] + objectData[4], 0, math.rad(objectData[5]))

			if (pObject ~= nil) then
				writeData(theaterID .. "theaterObject" .. i, SceneObject(pObject):getObjectID())

				local objectTemplate = SceneObject(pObject):getTemplateObjectPath()

				if (objectTemplate == "object/installation/battlefield/destructible/bfield_base_gate_impl.iff") then
					if (spawnedFirstDoor) then
						writeData(theaterID .. "campDoor2", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":campDoor2Index", i)
					else
						writeData(theaterID .. "campDoor1", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":campDoor1Index", i)
						spawnedFirstDoor = true
					end
					createObserver(OBJECTDESTRUCTION, "FsCounterStrike", "notifyDestructibleKilled", pObject)
					TangibleObject(pObject):setOptionBit(INVULNERABLE)
				elseif (objectTemplate == "object/installation/turret/turret_fs_cs.iff") then
					if (spawnedFirstTurret and spawnedSecondTurret) then
						writeData(theaterID .. "turret3", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":turret3Index", i)
					elseif (spawnedFirstTurret) then
						writeData(theaterID .. "turret2", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":turret2Index", i)
						spawnedSecondTurret = true
					else
						writeData(theaterID .. "turret1", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":turret1Index", i)
						spawnedFirstTurret = true
					end
				elseif (objectTemplate == "object/installation/battlefield/destructible/antenna_tatt_style_1.iff") then
					writeData(theaterID .. "antenna", SceneObject(pObject):getObjectID())
					createObserver(OBJECTDESTRUCTION, "FsCounterStrike", "notifyDestructibleKilled", pObject)
					TangibleObject(pObject):setOptionBit(INVULNERABLE)
				elseif (objectTemplate == "object/static/structure/corellia/corl_tent_hut_s01.iff") then
					writeData(theaterID .. ":tentIndex", i)
				end
			end
		end

		createNavMesh("dathomir", campLoc[2], campLoc[4], 60, true, "fs_counterstrike_" .. campLoc[1])

		self:spawnLootMobGroups(pTheater)
		self:spawnSurveillanceDroids(pTheater)
	end
end

function FsCounterStrike:erectShield(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local shieldID = readData(theaterID .. ":shieldID")

	local pActiveArea = getSceneObject(shieldID)

	if (pActiveArea ~= nil) then
		printf("Error generating shield in FsCounterStrike:erectShield, existing shield found.\n")
		return
	end

	pActiveArea = spawnActiveArea("dathomir", "object/active_area.iff", SceneObject(pTheater):getWorldPositionX(), SceneObject(pTheater):getWorldPositionZ(), SceneObject(pTheater):getWorldPositionY(), self.shieldRadius, 0)

	if pActiveArea ~= nil then
		createObserver(ENTEREDAREA, "FsCounterStrike", "notifyEnteredCampShieldArea", pActiveArea)
		writeData(theaterID .. ":shieldID", SceneObject(pActiveArea):getObjectID())
	end
end

function FsCounterStrike:despawnAllCamps()
	local campList = self:getPhaseCampList()

	if (campList == "" or campList == nil) then
		return
	end

	local campTable = HelperFuncs:splitString(campList, ",")

	for i = 1, #campTable, 1 do
		self:despawnCamp(tonumber(campTable[i]))
	end
end

function FsCounterStrike:despawnCamp(campNum)
	local campLoc = self.campSpawns[campNum]
	local campName = campLoc[1]
	local theaterID = readData("VillageCounterStrikeCampID:" .. campName)

	local pTheater = getSceneObject(theaterID)

	if (pTheater ~= nil) then
		for i = 1, self.maxLootMobGroups, 1 do
			self:destroyLootMobGroup(pTheater, i)
		end

		SceneObject(pTheater):destroyObjectFromWorld()
	end

	for i = 1, self.maxDroids, 1 do
		local droidID = readData(theaterID .. ":surveillanceDroid" .. i)
		local pDroid = getSceneObject(droidID)

		if (pDroid ~= nil) then
			dropObserver(OBJECTDESTRUCTION, pDroid)
			SceneObject(pDroid):destroyObjectFromWorld()
		end

		deleteData(droidID .. ":surveillanceDroidNum")
		deleteData(theaterID .. ":surveillanceDroid" .. i)
		deleteData(droidID .. ":theaterID")
	end

	for i = 1, #self.campLayout, 1 do
		local objID = readData(theaterID .. "theaterObject" .. i)
		local pObject = getSceneObject(objID)

		if (pObject ~= nil) then
			dropObserver(OBJECTDESTRUCTION, pObject)
			SceneObject(pObject):destroyObjectFromWorld()
		end

		deleteData(theaterID .. "theaterObject" .. i)
	end

	local shieldID = readData(theaterID .. ":shieldID")

	local pActiveArea = getSceneObject(shieldID)

	if (pActiveArea ~= nil) then
		SceneObject(pActiveArea):destroyObjectFromWorld()
	end

	deleteData(theaterID .. "campDoor1")
	deleteData(theaterID .. "campDoor1Index")
	deleteData(theaterID .. "campDoor2")
	deleteData(theaterID .. "campDoor2Index")
	deleteData(theaterID .. "turret1")
	deleteData(theaterID .. "turret1Index")
	deleteData(theaterID .. "turret2")
	deleteData(theaterID .. "turret2Index")
	deleteData(theaterID .. "turret3")
	deleteData(theaterID .. "turret3Index")
	deleteData(theaterID .. "tentIndex")
	deleteData(theaterID .. "antenna")
	deleteData(theaterID .. ":campNum")
	deleteData(theaterID .. ":shieldID")
	deleteData("VillageCounterStrikeCampID:" .. campName)
end

function FsCounterStrike:doPhaseChangeFail(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:combat_quest_failed_timeout")
	self:resetPlayer(pPlayer)
end

function FsCounterStrike:startQuest(pPlayer)
	if (pPlayer == nil) then
		return
	end

	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)
	createObserver(OBJECTDESTRUCTION, "FsCounterStrike", "onPlayerKilled", pPlayer)

	local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()

	if (pPlayerObj ~= nil) then
		PlayerObject(pPlayerObj):setFactionStanding("sith_shadow_nonaggro", -5000)
	end
end

function FsCounterStrike:onPlayerKilled(pPlayer, pKiller)
	if (pPlayer == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS)) then
		QuestManager.failQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE)
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_cs_last_chance_detail")

		local theaterID = readData(playerID .. ":csTheater")
		local pTheater = getSceneObject(theaterID)

		self:createCommander(pTheater)
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI)) then

	elseif (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_INTRO) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)) then
		return 1
	end

	return 0
end

function FsCounterStrike:resetPlayer(pPlayer)
	if (pPlayer == nil) then
		return
	end

	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_QUEST_DONE)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_QUEST_FAILED_ESCORT)

	local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()

	if (pPlayerObj ~= nil) then
		PlayerObject(pPlayerObj):setFactionStanding("sith_shadow_nonaggro", 0)
	end

	--self:destroyCommanderWaypoint(pPlayer)
end

function FsCounterStrike:resetPlayerToStart(pPlayer)
	if (pPlayer == nil) then
		return
	end

	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_QUEST_DONE)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CS_QUEST_FAILED_ESCORT)

	--self:destroyCommanderWaypoint(pPlayer)
end

function FsCounterStrike:destroyCommanderWaypoint(pPlayer)
	local waypointID = readData(SceneObject(pPlayer):getObjectID() .. ":village:csCommanderWaypoint")
	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		SceneObject(pWaypoint):destroyObjectFromWorld()
	end

	deleteData(SceneObject(pPlayer):getObjectID() .. ":village:csCommanderWaypoint")
end

function FsCounterStrike:giveCampRemote(pPlayer)
	local pInventory =  CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pDatapad = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/force_sensitive/camp_frequency_datapad.iff", true)

	if (pDatapad == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_remote_dont_have")
		return
	end

	local csItem = LuaFsCsObject(pDatapad)

	if (csItem:getDecayPercent() >= 100) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_remote_dont_have")
		return
	end

	SceneObject(pDatapad):destroyObjectFromWorld()
	SceneObject(pDatapad):destroyObjectFromDatabase()

	local campList = self:getPhaseCampList()
	local campTable = HelperFuncs:splitString(campList, ",")

	local randCamp = tonumber(campTable[getRandomNumber(#campTable)])
	local campName = self.campSpawns[randCamp][1]

	local pRemote = giveItem(pInventory, "object/tangible/loot/quest/force_sensitive/camp_remote.iff", -1, true)

	if (pRemote == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
		return
	end

	SceneObject(pRemote):setCustomObjectName(getStringId("@fs_quest_village:name_rem_" .. campName))
	TangibleObject(pRemote):setLuaStringData("campName", campName)
end

function FsCounterStrike:giveCampWaypoint(pPlayer)
	local pInventory =  CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pDatapad = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/force_sensitive/camp_waypoint_datapad.iff", true)

	if (pDatapad == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_remote_dont_have")
		return
	end

	local csItem = LuaFsCsObject(pDatapad)

	if (csItem:getDecayPercent() >= 100) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_remote_dont_have")
		return
	end

	SceneObject(pDatapad):destroyObjectFromWorld()
	SceneObject(pDatapad):destroyObjectFromDatabase()

	local campList = self:getPhaseCampList()
	local campTable = HelperFuncs:splitString(campList, ",")

	local randCamp = tonumber(campTable[getRandomNumber(#campTable)])
	local campData = self.campSpawns[randCamp]

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):addWaypoint("dathomir", "Aurilian Enemy", "", campData[2], campData[4], WAYPOINTYELLOW, true, true, 0)
	end
end

function FsCounterStrike:attemptPowerDownShield(pPlayer, campName)
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

	for i = 1, #self.campSpawns, 1 do
		local tempCampName = self.campSpawns[i][1]
		local theaterID = readData("VillageCounterStrikeCampID:" .. tempCampName)
		local pTheater = getSceneObject(theaterID)

		if (pTheater ~= nil and SceneObject(pPlayer):isInRangeWithObject(pTheater, self.shieldRemoteRange)) then
			if (tempCampName == campName) then
				local shieldID = readData(theaterID .. ":shieldID")

				local pShield = getSceneObject(shieldID)

				if (pShield == nil) then
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

				self:powerDownShield(pTheater)
				QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)
				QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS)
				createObserver(KILLEDCREATURE, "FsCounterStrike", "notifyKilledGuard", pPlayer)

				CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_cs_step_intro_complete")

				writeData(theaterID .. ":attackerID", SceneObject(pPlayer):getObjectID())
				writeData(SceneObject(pPlayer):getObjectID() .. ":csTheater", theaterID)
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

function FsCounterStrike:notifyKilledGuard(pPlayer, pVictim)
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

	local killedGuardCount = readData(playerID .. ":fsCounterStrike:guardsKilled")
	killedGuardCount = killedGuardCount + 1

	if (killedGuardCount == 5) then
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

		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)
		self:createCommander(pTheater)
		deleteData(playerID .. ":fsCounterStrike:guardsKilled")
		return 1
	else
		local messageString = LuaStringIdChatParameter("@quest/quests:kill_credit")
		messageString:setTO(getStringId(quest:getJournalSummary()))
		messageString:setDI(killsRequired - killedGuardCount)
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
		writeData(playerID .. ":fsCounterStrike:guardsKilled", killedGuardCount)
		deleteData(victimID .. ":theaterID")
	end

	return 0
end

function FsCounterStrike:createCommander(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	local commanderID = readData(theaterID .. ":commanderID")
	local pCommander = getSceneObject(commanderID)

	if (pCommander ~= nil) then
		self:killCommander(pCommander)
	end

	local shieldKillerID = readData(theaterID .. ":attackerID")
	local tentIndex = readData(theaterID .. ":tentIndex")

	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterZ = SceneObject(pTheater):getWorldPositionZ()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	local tentData = FsCounterStrike.campLayout[tentIndex]

	local tentX = theaterX + tentData[2]
	local tentZ = theaterZ + tentData[3]
	local tentY = theaterY + tentData[4]

	pCommander = spawnMobile("dathomir", "sith_shadow_mercenary_nofaction", 0, tentX, tentZ, tentY, 0, 0)

	if (pCommander == nil) then
		printf("Error in FsCounterStrike:createCommander, unable to create commander.")
		return
	end

	commanderID = SceneObject(pCommander):getObjectID()
	writeData(theaterID .. ":commanderID", commanderID)

	TangibleObject(pCommander):setOptionBit(INVULNERABLE)

	writeData(commanderID .. ":shieldKillerID", shieldKillerID)
	writeData(commanderID .. ":theaterID", theaterID)

	createEvent(self.commanderDespawnTime, "FsCounterStrike", "killCommander", pTheater, "")
end

function FsCounterStrike:killCommander(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	local commanderID = readData(theaterID .. ":commanderID")
	local pCommander = getSceneObject(commanderID)

	if (pCommander == nil) then
		return
	end

	writeData(commanderID .. ":deathSequence", 1)
	createEvent(5000, "FsCounterStrike", "doCommanderDeathSequence", pTheater, "")
end

function FsCounterStrike:doCommanderDeathSequence(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	local commanderID = readData(theaterID .. ":commanderID")
	local pCommander = getSceneObject(commanderID)

	if (pCommander == nil) then
		return
	end

	local deathSequence = readData(commanderID .. ":deathSequence")

	if (deathSequence == 0) then
		return
	end

	local spatialString

	if (deathSequence == 1) then
		spatialString = "commander_pain"
	elseif (deathSequence == 2) then
		spatialString = "commander_pain2"
	elseif (deathSequence == 3) then
		spatialString = "commander_pain3"
	else
		local escorterID = readData(commanderID .. ":escorterID")
		local pEscorter = getSceneObject(escorterID)

		if (pEscorter ~= nil) then
			self:notifyCommanderDied(pTheater, pEscorter, commanderID)
		end

		local shieldKillerID = readData(commanderID .. ":shieldKillerID")
		local pShieldKiller = getSceneObject(shieldKillerID)

		if (pShieldKiller ~= nil and pShieldKiller ~= pEscorter) then
			self:notifyCommanderDied(pTheater, pShieldKiller, commanderID)
		end

		SceneObject(pCommander):destroyObjectFromWorld()

		deleteData(commanderID .. ":shieldKillerID")
		deleteData(commanderID .. ":theaterID")
		deleteData(commanderID .. ":deathSequence")
		deleteData(commanderID .. ":escorterID")
		deleteData(theaterID .. ":commanderID")

		return
	end

	spatialChat(pCommander, "@fs_quest_village:" .. spatialString)
	writeData(commanderID .. ":deathSequence", deathSequence + 1)
	createEvent(getRandomNumber(5, 10) * 1000, "FsCounterStrike", "doCommanderDeathSequence", pTheater, "")
end

function FsCounterStrike:notifyCommanderDied(pTheater, pPlayer, commanderID)
	if (pTheater == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local playerOwnedCommander = readData(playerID .. ":fsCounterStrike:commanderID")

	if (commanderID ~= 0 and playerOwnedCommander ~= 0 and commanderID ~= playerOwnedCommander) then
		return
	end

	deleteData(playerID .. ":fsCounterStrike:commanderID")
	self:resetPlayerToStart(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:commander_died_toxins")
end

function FsCounterStrike:powerDownShield(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local shieldID = readData(theaterID .. ":shieldID")

	local pShield = getSceneObject(shieldID)

	if (pShield == nil) then
		return
	end

	SceneObject(pShield):destroyObjectFromWorld()

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

	createEvent(self.shieldRebootTime, "FsCounterStrike", "resetCamp", pTheater, attackerID)

	deleteData(theaterID .. ":shouldStopSpawn")
	self:spawnDefenseWaves(pTheater)
end

function FsCounterStrike:spawnDefenseWaves(pTheater)
	if (pTheater == nil) then
		return
	end

	-- This is set when the player begins the escort portion
	local shouldStopSpawn = readData(SceneObject(pTheater):getObjectID() .. ":shouldStopSpawn")

	if (shouldStopSpawn == 1) then
		deleteData(theaterID .. ":shouldStopSpawn")
		return
	end

	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	local nearbyPlayers = SceneObject(pTheater):getPlayersInRange(100)

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
		local spawnPoint = getSpawnPoint("dathomir", theaterX, theaterY, 50, 100, true)
		QuestSpawner:createQuestSpawner("FsCounterStrike", waveData[i][1], waveData[i][2], spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, "dathomir", pTheater)
	end

	createEvent(getRandomNumber(self.reinforcementWaveMin, self.reinforcementWaveMax), "FsCounterStrike", "spawnDefenseWaves", pTheater, "")
end

function FsCounterStrike:resetCamp(pTheater, attackerID)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local storedAttackerID = readData(theaterID .. ":attackerID")

	if (storedAttackerID ~= attackerID) then
		return
	end

	-- In case the defense waves are still spawning
	writeData(theaterID .. ":shouldStopSpawn", 1)

	deleteData(theaterID .. ":attackerID")
	deleteData(attackerID .. ":csTheater", theaterID)

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
	local campLoc = self.campSpawns[campNum]
	local campName = campLoc[1]

	local spawnedFirstDoor = false
	local spawnedFirstTurret = false
	local spawnedSecondTurret = false

	for i = 1, #self.campLayout, 1 do
		local objectData = self.campLayout[i]

		if (objectData[1] == "object/installation/battlefield/destructible/bfield_base_gate_impl.iff" or objectData[1] == "object/installation/battlefield/destructible/antenna_tatt_style_1.iff") then
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
					TangibleObject(pObject):setOptionBit(INVULNERABLE)
				end
			end
		end
	end
end

function FsCounterStrike:setupSpawnedDefender(pMobile)
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

	createEvent(getRandomNumber(10, 30) * 1000, "FsCounterStrike", "doMobileSpatial", pMobile, "")

	AiAgent(pMobile):setAiTemplate("villageraider")
	AiAgent(pMobile):setFollowState(4)

	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterZ = SceneObject(pTheater):getWorldPositionZ()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	local door1Index = readData(theaterID .. ":campDoor1Index")
	local door1Data = FsCounterStrike.campLayout[door1Index]

	local door1X = theaterX + door1Data[2]
	local door1Z = theaterZ + door1Data[3]
	local door1Y = theaterY + door1Data[4]

	local distToDoor1 = SceneObject(pMobile):getDistanceToPosition(door1X, door1Z, door1Y)

	local door2Index = readData(theaterID .. ":campDoor2Index")
	local door2Data = FsCounterStrike.campLayout[door2Index]

	local door2X = theaterX + door2Data[2]
	local door2Z = theaterZ + door2Data[3]
	local door2Y = theaterY + door2Data[4]

	local distToDoor2 = SceneObject(pMobile):getDistanceToPosition(door2X, door2Z, door2Y)

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)

	if (distToDoor1 < distToDoor2) then
		AiAgent(pMobile):setNextPosition(door1X, door1Z, door1Y, 0)
		AiAgent(pMobile):setHomeLocation(door1X, door1Z, door1Y, 0)
	else
		AiAgent(pMobile):setNextPosition(door2X, door2Z, door2Y, 0)
		AiAgent(pMobile):setHomeLocation(door2X, door2Z, door2Y, 0)
	end

	AiAgent(pMobile):executeBehavior()
end

function FsCounterStrike:doMobileSpatial(pMobile)
	if (pMobile == nil or getRandomNumber(100) <= 75) then
		return
	end

	spatialChat(pMobile, "@fs_quest_village:camp_defender_" .. getRandomNumber(1,10))
end

function FsCounterStrike:ifAntennaExists(pTheater)
	if (pTheater == nil) then
		return false
	end

	local antennaID = readData(SceneObject(pTheater):getObjectID() .. ":antenna")
	local pAntenna = getSceneObject(antennaID)

	return pAntenna ~= nil
end

FsCampRemoteMenuComponent = {}

function FsCampRemoteMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3, "@fs_quest_village:fs_cs_remote_use")
end

function FsCampRemoteMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil) then
		return 0
	end

	local csItem = LuaFsCsObject(pSceneObject)

	if (csItem:getDecayPercent() >= 100) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:p3_item_decayed")
		return 0
	end

	local campName = TangibleObject(pSceneObject):getLuaStringData("campName")
	local campNum = FsCounterStrike:getCampNumFromName(campName)

	if (campNum == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_remote_fail")
		return 0
	end

	if (selectedID == 20) then
		local result = FsCounterStrike:attemptPowerDownShield(pPlayer, campName)

		if (result) then
			if (getRandomNumber(100) <= 90) then
				SceneObject(pSceneObject):destroyObjectFromWorld()
				SceneObject(pSceneObject):destroyObjectFromDatabase()

				CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:remote_break")
			end
		end
	end

	return 0
end
