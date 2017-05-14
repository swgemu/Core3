local ObjectManager = require("managers.object.object_manager")

VillageRaids = ScreenPlay:new {
	turretSpawnLocs = {
		-- { x, z, y, yaw },
		{ 5309, 78.5, -4002, 0 },
		{ 5294, 78.5, -4006, 0 },
		{ 5282, 78.5, -4008, 0 },
		{ 5348, 78.5, -4012, 0 },
		{ 5364, 78.5, -4022, 0 },
		{ 5378, 78.5, -4029, 0 },
		{ 5293, 78.5, -4253, 174 },
		{ 5309, 78.5, -4252, 174 },
		{ 5326, 78.5, -4249, 174 },
		{ 5257, 78.5, -4250, 174 },
		{ 5242, 78.5, -4251, 174 },
		{ 5216, 78.5, -4239, 174 },
		{ 5294, 78.5, -4203, 156 },
		{ 5328, 78.5, -4047, 34 },
	},

	-- Number of players needed near village to move up a wave size
	playerWaveSizeThresholds = {
		medium = 10,
		large = 20,
		mega = 35
	},

	enemyData = {
		minSpawnPulse = 5000 * 1000,
		maxSpawnPulse = 7000 * 1000,
		minDistance = 25, -- Min distance from center of spawn loc
		maxDistance = 50 -- Max distance from center of spawn loc
	},

	-- Locations to spawn enemy spawners
	enemySpawnLocs = {
		{ 5240, -4335 },
		{ 5374, -3947 },
		{ 5415, -3959 },
		{ 5331, -4361 },
		{ 5187, -4369 }
	},

	-- Locations to spawn victim spawners
	victimSpawnLocs = {
		{ 5245, 78.5, -4199 },
		{ 5304, 78.5, -4218 },
		{ 5319, 78.5, -4213 },
		{ 5194, 78.5, -4146 },
		{ 5181, 78.5, -4137 },
		{ 5306, 78.5, -4155 },
		{ 5397, 78.5, -4114 },
		{ 5231, 78.5, -4138 },
		{ 5243, 78.5, -4122 },
		{ 5288, 78.5, -4046 },
	},
	-- Victim wave data
	victimWaveDataTable = {
		spawnerPulse = 180 * 1000, -- Time between spawn pulses
		maxSpawn = 100, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 2, -- Max mobs to have up at any one time
		mobileLifespan = 20 * 60 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 2500 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "" -- Name of function that should setup a defender after it's spawned
	},

	victimWaveSpawnList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "fs_villager_male", 2, 3, 1 },
		{ "fs_villager_female", 2, 3, 1 },
	},

	victimWave = { "victimWaveDataTable", "victimWaveSpawnList" },

	-- These are wave stages, each wave listed will spawn in order after the wave before it is complete
	enemyWaveData = {
		small = { "enemySmall", "enemySmall", "enemySmall" },
		medium = { "enemyMedium", "enemyMedium", "enemyMedium", "uberEnemyMedium" },
		large = { "enemyLarge", "enemyLarge", "uberEnemyLarge", "uberEnemyLarge" },
		mega = { "enemyLarge", "enemyLarge", "uberEnemyLarge", "uberEnemyLarge", "uberEnemyLarge" }
	},

	enemySmallList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "sith_shadow_thug_nonaggro", 5, 10, 1 },
		{ "sith_shadow_pirate_nonaggro", 5, 10, 2 },
		{ "sith_shadow_outlaw_nonaggro", 5, 10, 4 }
	},

	enemySmallData = {
		spawnerPulse = 20 * 1000, -- Time between spawn pulses
		maxSpawn = 100, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 5, -- Max mobs to have up at any one time
		mobileLifespan = 20 * 60 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 2500 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "setupSpawnedRaider", -- Name of function that should setup a defender after it's spawned
		spawnVerifyFunc = "verifyCurrentPhase" -- Function to verify if a spawner should continue creating waves
	},

	enemySmall = { "enemySmallData", "enemySmallList" },

	enemyMediumList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "sith_shadow_thug_nonaggro", 10, 15, 1 },
		{ "sith_shadow_pirate_nonaggro", 10, 15, 2 },
		{ "sith_shadow_outlaw_nonaggro", 10, 15, 4 }
	},

	enemyMediumData = {
		spawnerPulse = 20 * 1000, -- Time between spawn pulses
		maxSpawn = 100, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 10, -- Max mobs to have up at any one time
		mobileLifespan = 20 * 60 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 2500 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "setupSpawnedRaider", -- Name of function that should setup a defender after it's spawned
		spawnVerifyFunc = "verifyCurrentPhase" -- Function to verify if a spawner should continue creating waves
	},

	enemyMedium = { "enemyMediumData", "enemyMediumList" },

	uberEnemyMediumList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "sith_shadow_thug_nonaggro", 10, 15, 1 },
		{ "sith_shadow_pirate_nonaggro", 10, 15, 3 },
		{ "sith_shadow_outlaw_nonaggro", 10, 15, 5 },
		{ "sith_shadow_mercenary_nonaggro", 3, 5, 3 }
	},

	uberEnemyMediumData = {
		spawnerPulse = 20 * 1000, -- Time between spawn pulses
		maxSpawn = 100, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 10, -- Max mobs to have up at any one time
		mobileLifespan = 20 * 60 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 2500 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "setupSpawnedRaider", -- Name of function that should setup a defender after it's spawned
		spawnVerifyFunc = "verifyCurrentPhase" -- Function to verify if a spawner should continue creating waves
	},

	uberEnemyMedium = { "uberEnemyMediumData", "uberEnemyMediumList" },

	enemyLargeList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "sith_shadow_thug_nonaggro", 15, 20, 1 },
		{ "sith_shadow_pirate_nonaggro", 15, 20, 2 },
		{ "sith_shadow_outlaw_nonaggro", 15, 20, 4 }
	},

	enemyLargeData = {
		spawnerPulse = 20 * 1000, -- Time between spawn pulses
		maxSpawn = 100, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 10, -- Max mobs to have up at any one time
		mobileLifespan = 20 * 60 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 2500 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "setupSpawnedRaider", -- Name of function that should setup a defender after it's spawned
		spawnVerifyFunc = "verifyCurrentPhase" -- Function to verify if a spawner should continue creating waves
	},

	enemyLarge = { "enemyLargeData", "enemyLargeList" },

	uberEnemyLargeList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "sith_shadow_thug_nonaggro", 15, 20, 1 },
		{ "sith_shadow_pirate_nonaggro", 15, 20, 2 },
		{ "sith_shadow_outlaw_nonaggro", 15, 20, 4 },
		{ "sith_shadow_mercenary_nonaggro", 5, 10, 3 }
	},

	uberEnemyLargeData = {
		spawnerPulse = 20 * 1000, -- Time between spawn pulses
		maxSpawn = 100, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 10, -- Max mobs to have up at any one time
		mobileLifespan = 20 * 60 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 2500 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "setupSpawnedRaider", -- Name of function that should setup a defender after it's spawned
		spawnVerifyFunc = "verifyCurrentPhase" -- Function to verify if a spawner should continue creating waves
	},

	uberEnemyLarge = { "uberEnemyLargeData", "uberEnemyLargeList" },
}

function VillageRaids:doPhaseInit()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()

	if (currentPhase ~= 3 and currentPhase ~= 4) then
		return
	end

	self:despawnTurrets()
	self:spawnTurrets()

	if (currentPhase == 4) then
		self:doEnemySpawnPulse()
	end
end

function VillageRaids:spawnTurrets()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	for i = 1, #self.turretSpawnLocs, 1 do
		local loc = self.turretSpawnLocs[i]
		local pTurret = spawnSceneObject("dathomir", "object/installation/turret/turret_fs_village.iff", loc[1], loc[2], loc[3], 0, math.rad(loc[4]))

		if (pTurret ~= nil) then
			writeData("Village:Turret:" .. phaseID .. ":" .. i, SceneObject(pTurret):getObjectID())
		end
	end
end

-- Verify phase prior to spawning spawner waves
function VillageRaids:verifyCurrentPhase()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()

	return currentPhase == 4
end

function VillageRaids:setupSpawnedRaider(pMobile)
	if (pMobile == nil) then
		return
	end

	AiAgent(pMobile):setAiTemplate("villageraider")
	AiAgent(pMobile):setFollowState(4)

	createObserver(OBJECTDESTRUCTION, "FsVillageDefense", "notifyKilledRaider", pMobile)

	VillageRaids:startAttackerPatrolPath(pMobile)
end

function VillageRaids:startAttackerPatrolPath(pMobile)
	if (pMobile == nil) then
		return
	end

	if (AiAgent(pMobile):isInCombat()) then
		createEvent(30 * 1000, "VillageRaids", "startAttackerPatrolPath", pMobile, "")
		return
	end

	local closestVictimLoc = -1
	local closestVictimDist = -1

	for i = 1, #self.victimSpawnLocs, 1 do
		local loc = self.victimSpawnLocs[i]
		local dist = SceneObject(pMobile):getDistanceToPosition(loc[1], loc[2], loc[3])

		if (closestVictimDist == -1 or closestVictimDist > dist) then
			closestVictimLoc = i
			closestVictimDist = dist
		end
	end

	if (closestVictimLoc == -1) then
		printLuaError("VillageRaids:startPatrolPath, unable to get closest victim loc.")
		return
	end

	local locInfo = self.victimSpawnLocs[closestVictimLoc]
	AiAgent(pMobile):setHomeLocation(locInfo[1], locInfo[2], locInfo[3], 0)
	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):setNextPosition(locInfo[1], locInfo[2], locInfo[3], 0)
	AiAgent(pMobile):executeBehavior()
end

function VillageRaids:despawnTurrets()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	for i = 1, #self.turretSpawnLocs, 1 do
		local turretID = readData("Village:Turret:" .. phaseID .. ":" .. i)

		local pTurret = getSceneObject(turretID)

		if (pTurret ~= nil) then
			SceneObject(pTurret):destroyObjectFromWorld()
			deleteData("Village:Turret:" .. phaseID .. ":" .. i)
		end
	end
end

function VillageRaids:doEnemySpawnPulse()
	local pMaster = VillageJediManagerTownship:getMasterObject()

	if (pMaster == nil) then
		printLuaError("VillageRaids:doEnemySpawnPulse(), unable to get master village object.")
		return
	end

	local currentPhase = VillageJediManagerTownship.getCurrentPhase()

	if (currentPhase ~= 4) then
		return
	end

	self:despawnTurrets()
	self:spawnTurrets()

	self:spawnVictims(pMaster)

	local numPlayers = self:getPlayersInVillage(pMaster)
	local spawnWaveData

	if (numPlayers >= self.playerWaveSizeThresholds.mega) then
		spawnWaveData = self.enemyWaveData.mega
	elseif (numPlayers >= self.playerWaveSizeThresholds.large) then
		spawnWaveData = self.enemyWaveData.large
	elseif (numPlayers >= self.playerWaveSizeThresholds.medium) then
		spawnWaveData = self.enemyWaveData.medium
	else
		spawnWaveData = self.enemyWaveData.small
	end

	local usedLocs = { }

	for i = 1,  #self.enemySpawnLocs, 1 do
		table.insert(usedLocs, false)
	end

	for i = 1, #spawnWaveData, 1 do
		local randomLoc = getRandomNumber(1, #self.enemySpawnLocs)

		while usedLocs[randomLoc] == true do
			randomLoc = getRandomNumber(1, #self.enemySpawnLocs)
		end

		usedLocs[randomLoc] = true
		local waveInfo = self[spawnWaveData[i]]
		local loc = getSpawnPoint("dathomir", self.enemySpawnLocs[randomLoc][1], self.enemySpawnLocs[randomLoc][2], self.enemyData.minDistance, self.enemyData.maxDistance, true)
		QuestSpawner:createQuestSpawner("VillageRaids", waveInfo[1], waveInfo[2], loc[1], loc[2], loc[3], 0, "dathomir", pMaster)
	end

	local spawnPulse = getRandomNumber(self.enemyData.minSpawnPulse, self.enemyData.maxSpawnPulse)

	createEvent(spawnPulse, "VillageRaids", "doEnemySpawnPulse", pMaster, "")
end

function VillageRaids:getPlayersInVillage(pMaster)
	if (pMaster == nil) then
		printLuaError("VillageRaids:getPlayersInVillage(), unable to get master village object.")
		return
	end

	local playerTable = SceneObject(pMaster):getPlayersInRange(192)

	return #playerTable
end

function VillageRaids:spawnVictims(pMaster)
	for i = 1, #self.victimSpawnLocs, 1 do
		local loc = self.victimSpawnLocs[i]
		QuestSpawner:createQuestSpawner("VillageRaids", self.victimWave[1], self.victimWave[2], loc[1], loc[2], loc[3], 0, "dathomir", pMaster)
	end
end
