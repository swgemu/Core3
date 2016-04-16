local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

FsCounterStrike = {
	shieldRebootTime = 2 * 60 * 1000, -- 2 hours, shield will respawn after being dropped
	shieldRadius = 50, -- Radius of shield
	shieldExpelDistance = 10, -- How far back to push creatures from where they reached the shield
	maxCampsToSpawn = 20, -- Number of camps to spawn from campSpawns on phase change

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
	--{ "object/installation/turret/generic_turret_block_sm.iff", -0.26149, 0, 5.8774, 0 },
	--{ "object/installation/turret/generic_turret_block_sm.iff", 10.7884, 0, 26.21477, 0 },
	--{ "object/installation/turret/generic_turret_block_sm.iff", -12.5269, 0, 25.66261, 0 },
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

	droidTemplate = "mouse_droid",
	maxDroids = 5,
	droidMinDist = 75,
	droidMaxDist = 100,
}

function FsCounterStrike:pickPhaseCamps()
	local chosenCamps = { }

	while #chosenCamps < self.maxCampsToSpawn do
		local randCamp = getRandomNumber(#self.campSpawns)

		local containsCamp = false

		for i = 1, #chosenCamps, 1 do
			if (chosenCamps[i] == randCamp) then
				containsCamp = true
			end
		end

		if (not containsCamp) then
			table.insert(chosenCamps, randCamp)
		end
	end

	table.sort(chosenCamps)
	local campList = table.concat(chosenCamps, ",")
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	setQuestStatus("VillageCounterStrikeCampList:" .. phaseID, campList)
	self:spawnCamps()
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
			writeData(SceneObject(pMobile):getObjectID() .. ":theaterID", theaterID)
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

	local theaterID = readData(SceneObject(pVictim):getObjectID() .. ":theaterID")

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
		writeData(SceneObject(pMobile):getObjectID() .. ":theaterID", theaterID)
		createObserver(OBJECTDESTRUCTION, "FsCounterStrike", "notifyKilledDroid", pMobile)
		SceneObject(pMobile):setCustomObjectName(getStringId("@fs_quest_village:name_mdroid_" .. campName))
	end

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
			SceneObject(mobileList[i]):destroyObjectFromWorld()
		end
	end

	SceneObject(pSpawnGroup):destroyObjectFromWorld()

	deleteData(theaterID .. ":lootSpawnGroup" .. id)
	deleteData(spawnGroupID .. ":theaterID")
	deleteData(spawnGroupID .. ":spawnGroupNum")
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


--[[ -- TODO: Set decay data for datapad items
	local pInventory = CreatureObject(pVictim):getSlottedObject("inventory")

	if pInventory == nil then
		return 1
	end

	for i = 1, SceneObject(pInventory):getContainerObjectsSize(), 1 do
		local pItem = SceneObject(pInventory):getContainerObject(i)

		if pItem ~= nil then
		end
	end
]]
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

		local pActiveArea = spawnActiveArea("dathomir", "object/active_area.iff", campLoc[2], campLoc[3], campLoc[4], self.shieldRadius, 0)
		if pActiveArea ~= nil then
			createObserver(ENTEREDAREA, "FsCounterStrike", "notifyEnteredCampShieldArea", pActiveArea)
		end

		for i = 1, #self.campLayout, 1 do
			local objectData = self.campLayout[i]
			local pObject = spawnSceneObject("dathomir", objectData[1], campLoc[2] + objectData[2], campLoc[3]  + objectData[3], campLoc[4] + objectData[4], 0, math.rad(objectData[5]))

			if (pObject ~= nil) then
				writeData(theaterID .. "theaterObject" .. i, SceneObject(pObject):getObjectID())
			end
		end

		self:spawnLootMobGroups(pTheater)
		self:spawnSurveillanceDroids(pTheater)
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
		SceneObject(pTheater):destroyObjectFromWorld()
	end

	for i = 1, #self.campLayout, 1 do
		local objID = readData(theaterID .. "theaterObject" .. i)
		local pObject = getSceneObject(objID)

		if (pObject ~= nil) then
			SceneObject(pObject):destroyObjectFromWorld()
		end
	end
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
