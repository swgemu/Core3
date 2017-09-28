local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

FsCounterStrike = {
	testMode = false, -- For testing only, sets turnin for commander to close by the base
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
		{ "object/installation/turret/turret_fs_cs.iff", -0.26149, 0, 5.8774, 0 },
		{ "object/installation/turret/turret_fs_cs.iff", 10.7884, 0, 26.21477, 0 },
		{ "object/installation/turret/turret_fs_cs.iff", -12.5269, 0, 25.66261, 0 },
	},
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

function FsCounterStrike:spawnCamps()
	local campList = self:getPhaseCampList()
	local campTable = HelperFuncs:splitString(campList, ",")

	for i = 1, #campTable, 1 do
		local campNum = tonumber(campTable[i])
		local campLoc = self.campSpawns[campNum]
		local campName = campLoc[1]

		local pTheater = spawnSceneObject("dathomir", "object/static/structure/nobuild/nobuild_32.iff", campLoc[2], campLoc[3], campLoc[4], 0, 0)

		if (pTheater == nil) then
			printLuaError("Error creating theater in FsCounterStrike:spawnCamps().")
			return
		end

		local theaterID = SceneObject(pTheater):getObjectID()
		writeData("VillageCounterStrikeCampID:" .. campName, theaterID)
		writeData(theaterID .. ":campNum", campNum)

		local spawnedFirstDoor = false
		local spawnedFirstTurret = false
		local spawnedSecondTurret = false

		for j = 1, #self.campLayout, 1 do
			local objectData = self.campLayout[j]
			local pObject = spawnSceneObject("dathomir", objectData[1], campLoc[2] + objectData[2], campLoc[3]  + objectData[3], campLoc[4] + objectData[4], 0, math.rad(objectData[5]))

			if (pObject ~= nil) then
				writeData(theaterID .. "theaterObject" .. j, SceneObject(pObject):getObjectID())

				local objectTemplate = SceneObject(pObject):getTemplateObjectPath()

				if (objectTemplate == "object/installation/battlefield/destructible/bfield_base_gate_impl.iff") then
					if (spawnedFirstDoor) then
						writeData(theaterID .. "campDoor2", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":campDoor2Index", j)
					else
						writeData(theaterID .. "campDoor1", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":campDoor1Index", j)
						spawnedFirstDoor = true
					end
					createObserver(OBJECTDISABLED, "FsCsBaseControl", "notifyDestructibleDisabled", pObject)
					TangibleObject(pObject):setOptionBit(INVULNERABLE)
				elseif (objectTemplate == "object/installation/turret/turret_fs_cs.iff") then
					if (spawnedFirstTurret and spawnedSecondTurret) then
						writeData(theaterID .. "turret3", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":turret3Index", j)
					elseif (spawnedFirstTurret) then
						writeData(theaterID .. "turret2", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":turret2Index", j)
						spawnedSecondTurret = true
					else
						writeData(theaterID .. "turret1", SceneObject(pObject):getObjectID())
						writeData(theaterID .. ":turret1Index", j)
						spawnedFirstTurret = true
					end
				elseif (objectTemplate == "object/installation/battlefield/destructible/antenna_tatt_style_1.iff") then
					writeData(theaterID .. "antenna", SceneObject(pObject):getObjectID())
					createObserver(OBJECTDISABLED, "FsCsBaseControl", "notifyDestructibleDisabled", pObject)
					TangibleObject(pObject):setOptionBit(INVULNERABLE)
				elseif (objectTemplate == "object/static/structure/corellia/corl_tent_hut_s01.iff") then
					writeData(theaterID .. ":tentIndex", j)
				end
			end
		end

		local pMesh = createNavMesh("dathomir", campLoc[2], campLoc[4], 60, true, "fs_counterstrike_" .. campLoc[1])

		if (pMesh == nil) then
			printLuaError("FsCounterStrike:spawnCamps() failed to create navmesh for camp " .. campLoc[1] .. ".")
		else
			writeData("FsCounterstrikeMesh:" .. i, SceneObject(pMesh):getObjectID())
			FsCsBaseControl:erectShield(pTheater)

			FsCsBaseControl:spawnLootMobGroups(pTheater)
			FsCsBaseControl:spawnSurveillanceDroids(pTheater)
		end
	end
end

function FsCounterStrike:despawnAllCamps()
	local campList = self:getPhaseCampList()

	if (campList == "" or campList == nil) then
		return
	end

	local campTable = HelperFuncs:splitString(campList, ",")

	for i = 1, #campTable, 1 do
		local meshID = readData("FsCounterstrikeMesh:" .. i)

		local pMesh = getSceneObject(meshID)

		if (pMesh ~= nil) then
			SceneObject(pMesh):destroyObjectFromWorld()
		end
		
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

	for i = 1, FsCsBaseControl.maxDroids, 1 do
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
			dropObserver(OBJECTDISABLED, pObject)
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
	deleteData(theaterID .. ":shieldPowerDownTime")
	deleteData(theaterID .. ":shieldPoweredDown")
	deleteData("VillageCounterStrikeCampID:" .. campName)
end

function FsCounterStrike:doPhaseChangeFail(pPlayer)
	if (not self:isOnQuest(pPlayer)) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:combat_quest_failed_timeout")
	self:resetPlayer(pPlayer)
end

function FsCounterStrike:completeQuest(pPlayer, teamComplete)
	if (not self:isOnEscort(pPlayer)) then
		return
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)) then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI)) then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI)
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC)) then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC)
	end

	VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_combat_prowess_melee_accuracy")

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pCrystal = giveItem(pInventory, "object/tangible/component/weapon/lightsaber/lightsaber_module_force_crystal.iff", -1, true)

		if (pCrystal == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
		else
			local colorCrystal = LuaLightsaberCrystalComponent(pCrystal)
			colorCrystal:setColor(29)
			colorCrystal:updateCrystal(29)
		end
	end

	CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:quest_complete")

	if (teamComplete) then
		local pBuffItem = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_buff_item.iff", -1, true)

		if (pBuffItem == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
		else
			local buffItem = LuaFsBuffItem(pBuffItem)
			buffItem:setBuffAttribute(6)
			buffItem:setReuseTime(345600000)
			buffItem:setBuffValue(900)
			buffItem:setBuffDuration(5400)
		end

		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:teamwork_bonus")
	end

	FsCsCommander:destroyCommanderWaypoint(pPlayer)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_QUEST_DONE)
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

		FsCsCommander:createCommander(pTheater)
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI)) then
		local commanderID = readData(playerID .. ":fsCounterStrike:commanderID")
		local pCommander = getSceneObject(commanderID)

		if (pCommander ~= nil) then
			FsCsCommander:handleCommanderEscorterFailure(pPlayer, pCommander)
		else
			-- This shouldn't happen, but in case we lose the commander object
			FsCounterStrike:resetPlayerToStart(pPlayer)
			CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_primary_escort_fail")
		end
	elseif (not self:isOnQuest(pPlayer)) then
		-- Player doesn't have quest, remove observer
		return 1
	end

	return 0
end

function FsCounterStrike:isOnQuest(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_INTRO) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_KILL5_GUARDS) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC)
end

function FsCounterStrike:isOnEscort(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC)
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

	dropObserver(OBJECTDESTRUCTION, "FsCounterStrike", "onPlayerKilled", pPlayer)

	local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()

	if (pPlayerObj ~= nil) then
		PlayerObject(pPlayerObj):setFactionStanding("sith_shadow_nonaggro", 0)
	end

	FsCsCommander:destroyCommanderWaypoint(pPlayer)
end

function FsCounterStrike:resetPlayerToStart(pPlayer)
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

	FsCsCommander:destroyCommanderWaypoint(pPlayer)

	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)
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
