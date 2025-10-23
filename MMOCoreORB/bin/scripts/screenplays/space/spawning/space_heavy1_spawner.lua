SpaceHeavy1Spawner = SpaceSpawnerScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceHeavy1Spawner",

	spaceZone = "space_heavy1",

	shipSpawns = {
		{spawnName = "imperialTest1", spawnType = SHIP_SPAWN_SQUADRON, x = 4927, z = 0, y = -7105, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 600, minSpawnDistance = 250, maxSpawnDistance = 500, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperialTest1_00", "imperialTest1_01", "imperialTest1_02", "imperialTest1_03", "imperialTest1_04", "imperialTest1_05"},
			shipSpawns = {"squad_stardestroyer_1"}
		},
		{spawnName = "imperialTest2", spawnType = SHIP_SPAWN_SQUADRON, x = -1472, z = 0, y = 5406, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 600, minSpawnDistance = 400, maxSpawnDistance = 500, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperialTest2_00", "imperialTest2_01", "imperialTest2_02", "imperialTest2_03", "imperialTest2_04", "imperialTest2_05"},
			shipSpawns = {"squad_stardestroyer_2"}
		},
		{spawnName = "imperialTest3", spawnType = SHIP_SPAWN_SQUADRON, x = -1968, z = 0, y = -4993, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 600, minSpawnDistance = 400, maxSpawnDistance = 500, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperialTest3_00", "imperialTest3_01", "imperialTest3_02", "imperialTest3_03", "imperialTest3_04", "imperialTest3_05"},
			shipSpawns = {"squad_stardestroyer_3"}
		},
		{spawnName = "imperialTest4", spawnType = SHIP_SPAWN_SQUADRON, x = 6495, z = 0, y = -5985, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 600, minSpawnDistance = 400, maxSpawnDistance = 500, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperialTest4_00", "imperialTest4_01", "imperialTest4_02", "imperialTest4_03", "imperialTest4_04", "imperialTest4_05"},
			shipSpawns = {"squad_stardestroyer_4"}
		},
		{spawnName = "imperialTest5", spawnType = SHIP_SPAWN_SQUADRON, x = 4463, z = 0, y = 6750, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 600, minSpawnDistance = 400, maxSpawnDistance = 500, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"imperialTest5_00", "imperialTest5_01", "imperialTest5_02", "imperialTest5_03", "imperialTest5_04", "imperialTest5_05"},
			shipSpawns = {"squad_stardestroyer_5"}
		},
		{spawnName = "rebelTest1", spawnType = SHIP_SPAWN_SQUADRON, x = -4240, z = 0, y = 6014, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 600, minSpawnDistance = 400, maxSpawnDistance = 500, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebelTest1_00", "rebelTest1_01", "rebelTest1_02", "rebelTest1_03", "rebelTest1_04", "rebelTest1_05"},
			shipSpawns = {"squad_rebel_station_1"}
		},
		{spawnName = "rebelTest2", spawnType = SHIP_SPAWN_SQUADRON, x = -2464, z = 0, y = -2513, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 600, minSpawnDistance = 400, maxSpawnDistance = 500, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebelTest2_00", "rebelTest2_01", "rebelTest2_02", "rebelTest2_03", "rebelTest2_04", "rebelTest2_05"},
			shipSpawns = {"squad_rebel_station_2"}
		},
		{spawnName = "rebelTest3", spawnType = SHIP_SPAWN_SQUADRON, x = -4448, z = 0, y = 3726, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 500, minSpawnDistance = 400, maxSpawnDistance = 600, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebelTest3_00", "rebelTest3_01", "rebelTest3_02", "rebelTest3_03", "rebelTest3_04", "rebelTest3_05"},
			shipSpawns = {"squad_rebel_station_3"}
		},
		{spawnName = "rebelTest4", spawnType = SHIP_SPAWN_SQUADRON, x = 2287, z = 0, y = 5486, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 500, minSpawnDistance = 400, maxSpawnDistance = 600, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebelTest4_00", "rebelTest4_01", "rebelTest4_02", "rebelTest4_03", "rebelTest4_04", "rebelTest4_05"},
			shipSpawns = {"squad_rebel_station_4"}
		},
		{spawnName = "rebelTest5", spawnType = SHIP_SPAWN_SQUADRON, x = 831, z = 0, y = -6561, patrolType = SHIP_AI_FIXED_PATROL, minRespawn = 180, maxRespawn = 500, minSpawnDistance = 400, maxSpawnDistance = 600, totalSpawns = 5,
			patrolsToAssign = 5, fixedPatrolPoints = {"rebelTest5_00", "rebelTest5_01", "rebelTest5_02", "rebelTest5_03", "rebelTest5_04", "rebelTest5_05"},
			shipSpawns = {"squad_rebel_station_5"}
		},
	},
}

registerScreenPlay("SpaceHeavy1Spawner", true)

function SpaceHeavy1Spawner:start()
	if (not isZoneEnabled(self.spaceZone)) then
		return
	end

	-- Temporary Spawning Until Deep Space Spawning Logic is added here
	local randomDelay = getRandomNumber(self.SERVER_STARTUP_MIN, self.SERVER_STARTUP_MAX)

	if (self.SPAWN_NO_DELAY) then
		randomDelay = 20
	end

	createEvent(randomDelay * 1000, self.screenplayName, "populateSpawns", nil, "")

	self:spawnPrimaryTargets()
end

function SpaceHeavy1Spawner:spawnPrimaryTargets()
	local pFreedomStation = spawnShipAgent("spacestation_freedom", self.spaceZone, -6000, 0, 0, false)

	if (pFreedomStation ~= nil) then
		ShipAiAgent(pFreedomStation):setDespawnOnNoPlayerInRange(false)
	end

	local pStarDestroyer = spawnShipAgent("star_destroyer", self.spaceZone, 6000, 0, 0, false, pFreedomStation)

	if (pStarDestroyer ~= nil) then
		ShipAiAgent(pStarDestroyer):setDespawnOnNoPlayerInRange(false)
	end
end