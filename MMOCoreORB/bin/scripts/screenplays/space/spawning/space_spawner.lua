SpaceSpawnerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceSpawnerScreenPlay",

	spaceZone = "",

	--[[ Spawn Types - from ShipFlag.h
		SHIP_AI_GUARD_PATROL - For ships that patrol a specific area in a spherical pattern where they will have a min range and max range to stay within
						used for ships in patrol around a point or object such as a space station.
		SHIP_AI_RANDOM_PATROL - Default method for patrolling. Randomly generates points around its home location.alignas
		SHIP_AI_FIXED_PATROL - For ships that have specific set of patrol points assigned to them and will only navigate to those points.alignas
		SHIP_AI_SQUADRON_PATROL - For ships that are in a squadron, this will be used to create and assign them to an observer as well as the behaviors needed to operate in the squadron.alignas
		SHIP_AI_SQUADRON_FOLLOW - Similar to above, but for ships that have to follow another ship while in a squadron.
	]]

	shipSpawns = {
	--[[
		{"spawn_name_", x, z, y, SHIP_AI_FIXED_PATROL, minRespawn, maxRespawn, minDistance, maxDistance, totalSpawns,
			totalPointsToAssign, {"patrol_point1", "patrol_point2", "patrol_point3"},
			{"ship_1", "ship2", "ship3"},
		},
		{"spawn_name_", x, z, y, SHIP_AI_GUARD_PATROL, minRespawn, maxRespawn, minDistance, maxDistance, minCircle, maxCircle, totalSpawns,
			{"ship_1", "ship2", "ship3"},
		},
		{"spawn_name_", x, z, y, SHIP_AI_RANDOM_PATROL, minRespawn, maxRespawn, minDistance, maxDistance, minPatrolDistance, maxPatrolDistance, totalSpawns,
			{"ship_1", "ship2", "ship3"},
		},
	]]
	},
}

function SpaceSpawnerScreenPlay:populateSpawns()
	local shipSpawns = self.shipSpawns

	if (#shipSpawns < 1) then
		local screenplayName = self.screenplayName
		print(screenplayName .. " - has no ship spawns to populate.")
		return
	end

	--print("Total spawns = " .. #shipSpawns .. " SHIP_AI_FIXED_PATROL = " .. SHIP_AI_FIXED_PATROL .. " SHIP_AI_RANDOM_PATROL = " .. SHIP_AI_RANDOM_PATROL)

	for i = 1, #shipSpawns, 1 do
		local spawnTable = shipSpawns[i]

		local totalSpawns = 0
		local spawnType = spawnTable[5]

		if (spawnType == SHIP_AI_FIXED_PATROL) then
			totalSpawns = spawnTable[10]
		else
			totalSpawns = spawnTable[12]
		end

		--print(self.screenplayName .. " -- Spawning a total of " ..totalSpawns .. " ships.")

		for j = 1, totalSpawns, 1 do
			-- Prevent stacking of spawns
			if (spawnType == SHIP_AI_GUARD_PATROL or spawnType == SHIP_AI_FIXED_PATROL) then
				createEvent((getRandomNumber(5, 90) + 1) * 1000, self.screenplayName, "spawnShipAgent", nil, tostring(i))
			else
				self:spawnShipAgent(nil, tostring(i))
			end
		end
	end
end

function SpaceSpawnerScreenPlay:spawnShipAgent(pNil, indexString)
	local tableNum = tonumber(indexString)

	local spawnTable = self.shipSpawns[tableNum]
	local shipsTable = spawnTable[13]
	local possibleShips = #shipsTable
	local randomNumber = getRandomNumber(possibleShips)

	local shipName = shipsTable[getRandomNumber(possibleShips)]

	if (string.find(shipName, "squad") ~= nil) then
		return
	end

	local x = spawnTable[2]
	local z = spawnTable[3]
	local y = spawnTable[4]
	local spawnType = spawnTable[5]

	-- TODO: Implement squadrons
	if (spawnType == SHIP_AI_SQUADRON_PATROL) then
		return
	end

	local minDistance = spawnTable[8]
	local maxDistance = spawnTable[9]
	local randomDist = getRandomNumber(minDistance, maxDistance)

    local theta = math.random() * 2 * math.pi  -- azimuthal angle
    local phi = math.acos(1 - 2 * math.random())  -- polar angle

    -- Convert spherical coordinates to Cartesian coordinates
    x = x + randomDist * math.sin(phi) * math.cos(theta)
    y = y + randomDist * math.sin(phi) * math.sin(theta)
    z = z + randomDist * math.cos(phi)

	--print(self.screenplayName .. " -- attempting to spawn ship from Spawn Table #" .. tableNum)
	--print("Ship Template: " .. shipName .. " X: " .. x .. " Z: " .. z .. " Y: " .. y .. " minDistance: " .. minDistance .. " maxDistance: " .. maxDistance)

	local pShipAgent = spawnShipAgent(shipName, self.spaceZone, x, z, y)

	if pShipAgent ~= nil then
		ShipAiAgent(pShipAgent):setDespawnOnNoPlayerInRange(false)

		createObserver(SHIPAGENTDESPAWNED, self.screenplayName, "onDespawn", pShipAgent)

		if (spawnType == SHIP_AI_FIXED_PATROL) then
			ShipAiAgent(pShipAgent):setFixedPatrol()

			local totalToAdd = spawnTable[11]
			local patrolPoints = spawnTable[12]
			local count = 1

			-- Get the max value we can start at in the table
			local startPoint = #patrolPoints - totalToAdd

			if (startPoint < 1) then
				startPoint = 1
			end

			startPoint = getRandomNumber(1, startPoint)

			--print(shipName .. " -- Fixed patrol spawn - Total Points to add: " .. totalToAdd .. " Table Size: " .. #patrolPoints .. " Start Point: " .. startPoint)

			while (totalToAdd >= count) do
				local patrolName = patrolPoints[startPoint]

				ShipAiAgent(pShipAgent):addFixedPatrolPoint(patrolName, false)

				--print(shipName .. " -- adding point #" .. startPoint .. " Point: " .. patrolName)

				-- Increase count
				count = count + 1
				-- Increase start point
				startPoint = startPoint + 1

				-- Some spawns have smaller set of patrol points, so start over at the first
				if (startPoint > #patrolPoints) then
					startPoint = 1
				end
			end
		elseif (spawnType == SHIP_AI_GUARD_PATROL) then
			ShipAiAgent(pShipAgent):setMinimumGuardPatrol(spawnTable[10])
			ShipAiAgent(pShipAgent):setMaximumGuardPatrol(spawnTable[11])

			ShipAiAgent(pShipAgent):setGuardPatrol()
		else
			ShipAiAgent(pShipAgent):setRandomPatrol()
		end

		writeData(SceneObject(pShipAgent):getObjectID() .. ":Spawner:", tableNum)
	end
end

function SpaceSpawnerScreenPlay:onDespawn(pShipAiAgent)
	if pShipAiAgent == nil or not SceneObject(pShipAiAgent):isShipAiAgent() then
		printf("pShipAiAgent is nil or not an ShipAiAgent" .. "\n")
		return
	end

	--print(self.screenplayName .. " -- onDespawn triggered for Ship: " .. SceneObject(pShipAiAgent):getDisplayedName())

	local tableNum = readData(SceneObject(pShipAiAgent):getObjectID() .. ":Spawner:")
	deleteData(SceneObject(pShipAiAgent):getObjectID() .. ":Spawner:")

	local spawnTable = self.shipSpawns[tableNum]
	local minRespawn = spawnTable[6]
	local maxRespawn = spawnTable[7]

	createEvent((getRandomNumber(maxRespawn) + minRespawn) * 1000, self.screenplayName, "respawn", nil, tostring(tableNum))

	return 1
end

function SpaceSpawnerScreenPlay:respawn(pNil, args)
	--print(self.screenplayName .. " -- respawn called with Info: " .. args)

	self:spawnShipAgent(nil, args)
end
