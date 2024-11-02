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
		{"spawn_name_", x, z, y, SHIP_AI_GUARD_PATROL, 60, 120, 10, 23, 100, 500, 6,
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

	for i = 1, #shipSpawns, 1 do
		local spawnTable = shipSpawns[i]

		local totalSpawns = 0
		local spawnType = spawnTable[5]

		if (spawnType == SHIP_AI_FIXED_PATROL) then
			totalSpawns = spawnTable[10]
		else
			totalSpawns = spawnTable[12]
		end

		for j = 1, totalSpawns, 1 do
			createEvent((getRandomNumber(5) + 1) * 100, self.screenplayName, "spawnShipAgent", nil, tostring(i))
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
	local shipType = spawnTable[5]

	if (shipType == SHIP_AI_SQUADRON_PATROL) then
		return
	end

	local minDistance = spawnTable[8]
	local maxDistance = spawnTable[9]

	--TODO: Randomize location

	local screenplayName = self.screenplayName

	--print(screenplayName .. " -- attempting to spawn ship from Spawn Table #" .. tableNum)
	--print("Ship Template: " .. shipName .. " X: " .. x .. " Z: " .. z .. " Y: " .. y .. " minDistance: " .. minDistance .. " maxDistance: " .. maxDistance)

	local pShipAgent = spawnShipAgent(shipName, self.spaceZone, x, z, y)

	if pShipAgent ~= nil then
		LuaShipAiAgent(pShipAgent):setDespawnOnNoPlayerInRange(false)

		createObserver(SHIPAGENTDESPAWNED, self.screenplayName, "onDespawn", pShipAgent)

		if (shipType == SHIP_AI_FIXED_PATROL) then
			--LuaShipAiAgent(pShipAgent):setFixedPatrol()
		elseif (shipType == SHIP_AI_GUARD_PATROL) then
			--LuaShipAiAgent(pShipAgent):setGuardPatrol()
		else
			--LuaShipAiAgent(pShipAgent):setRandomPatrol()
		end

		writeData(SceneObject(pShipAgent):getObjectID() .. ":Spawner:", tableNum)
	end
end

function SpaceSpawnerScreenPlay:onDespawn(pShipAiAgent)
	if pShipAiAgent == nil or not SceneObject(pShipAiAgent):isShipAiAgent() then
		printf("pShipAiAgent is nil or not an ShipAiAgent" .. "\n")
		return
	end

	--local screenplayName = self.screenplayName
	--print(screenplayName .. " -- onDespawn triggered for Ship: " .. SceneObject(pShipAiAgent):getDisplayedName())

	local tableNum = readData(SceneObject(pShipAiAgent):getObjectID() .. ":Spawner:")
	deleteData(SceneObject(pShipAiAgent):getObjectID() .. ":Spawner:")

	local spawnTable = self.shipSpawns[tableNum]
	local minRespawn = spawnTable[6]
	local maxRespawn = spawnTable[7]

	createEvent((getRandomNumber(maxRespawn) + minRespawn) * 1000, self.screenplayName, "respawn", nil, tostring(tableNum))

	return 1
end

function SpaceSpawnerScreenPlay:respawn(pNil, args)
	--local screenplayName = self.screenplayName
	--print(screenplayName .. " -- respawn called with Info: " .. args)

	createEvent((getRandomNumber(5) + 1) * 100, self.screenplayName, "spawnShipAgent", nil, args)
end
