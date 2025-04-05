InterestAreaSpawner = ScreenPlay:new {
	debug = false,
	debugMin = 1,
	debugMax = 2,

	screenplayName = "",
	zoneName = "",

	startDelay = 10, -- Minutes

	-- Chance out of 100 that a spawner has to be activate upon server start. 100 is always activated
	activationChance = 100,

	-- Timer to use for mobile respawn
	respawnTimer = 300,

	-- Force Despawn in minutes (used on mobiles still in combat during spawner removal)
	forceDespawn = 3,

	--[[ Spawn Data Table
		{x, z, y, direction, activeMin, activeMax, inactiveMin, inactiveMax}

		x, z, y = Location of spawn
		direction = direction for spawns to face
		activeMin = Minimum amount of time in minutes for spawner to be active
		activeMax = Maximum amount of time in minutes for spawner to be active
		inactiveMin = Minimum amount of time in minutes for spawner to be inactive
		inactiveMax = Maximum amount of time in minutes for spawner to be inactive
		{{"spawnsTable1", numToSpawn}, "spawnsTable2"} = Table of possible spawns from spawnGroups and amount to spawn
	]]

	spawnerData = {
		-- {x, z, y, direction, activeMin, activeMax, inactiveMin, inactiveMax, {{"spawnsTable1", numToSpawn}, {"spawnsTable2", numToSpawn}},
	},

	-- A table of different groups of spawns availabe to be assigned to a spawner
	spawnGroups = {
		--meatlump1 = {"meatlump_buffoon", "meatlump_fool", "meatlump_loon"},
		--wompRatEasy = {"lesser_desert_womp_rat"},
		--rill = {"rill"},
		--minorWorrt = {"minor_worrt"},
	},
}

--[[ Interest Area Spawner
	Parent class functions to manage spawns for an interest area (POI, city etc)
	This will handle whichs spawners are active, how often and what they spawn
]]

function InterestAreaSpawner:createSpawners()
	local name = self.screenplayName
	local spawnerData = self.spawnerData
	local count = 0

	if (self.debug) then
		print(name .. ":createSpawners() - with total of " .. #spawnerData .. " spawners" .. "\n")
	end

	for i = 1, #spawnerData, 1 do
		local spawn = spawnerData[i]

		if (self.debug) then
			print(name .. " creating Interest Spawner at X: " .. spawn[1] .. " Y: " .. spawn[3])
		end

		local pSpawner = spawnSceneObject(self.zoneName, "object/tangible/spawning/spawn_egg.iff", spawn[1], spawn[2], spawn[3], 0, math.rad(spawn[4]))

		if (pSpawner == nil or not SceneObject(pSpawner):isSpawnEggObject()) then
			goto skip
		end

		local pSpawnEgg = LuaSpawnEggObject(pSpawner)

		if (pSpawnEgg == nil) then
			goto skip
		end

		-- Set the spawner name
		local newName = SceneObject(pSpawner):getDisplayedName() .. ":" .. name .. "-" .. i

		if (self.debug) then
			print(newName .. " -- created in zone")
		end

		-- Set the Egg Object Name
		SceneObject(pSpawner):setCustomObjectName(newName)

		pSpawnEgg:setSpawnerName(newName)

		count = count + 1

		local spawnerID = SceneObject(pSpawner):getObjectID()

		-- Write Spawner Data
		writeData(name .. ":Spawner:" .. i .. ":", spawnerID)
		writeData(spawnerID .. ":" .. name .. ":", i)

		-- Write Spawner Timers
		writeData(spawnerID .. ":" .. name .. ":" .. "activeMin:", spawn[5])
		writeData(spawnerID .. ":" .. name .. ":" .. "activeMax:", spawn[6])
		writeData(spawnerID .. ":" .. name .. ":" .. "inactiveMin:", spawn[7])
		writeData(spawnerID .. ":" .. name .. ":" .. "inactiveMax:", spawn[8])

		::skip::
	end

	if (self.debug) then
		print(name .. " -- Spawned " .. tostring(count) .. " Interest Area Spawners." .. "\n")
	end

	writeData(name .. ":TotalSpawners:", count)
end

function InterestAreaSpawner:activateSpawners()
	local name = self.screenplayName
	local totalSpawners = readData(name .. ":TotalSpawners:")

	if (self.debug) then
		print(name .. ":activateSpawners - called: " .. name .. " Total Spawners: " ..  totalSpawners .. "\n")
	end

	for i = 1, totalSpawners, 1 do
		local spawnerID = readData(name .. ":Spawner:" .. i .. ":")
		local pSpawner = getSceneObject(spawnerID)

		if (pSpawner == nil) then
			goto skip
		end

		local pSpawnEgg = LuaSpawnEggObject(pSpawner)

		if (pSpawnEgg == nil) then
			goto skip
		end

		self:activateSpawner(pSpawner)

		::skip::
	end
end

function InterestAreaSpawner:activateSpawner(pSpawner)
	local name = self.screenplayName

	if (pSpawner == nil) then
		Logger:log(name .. " InterestArea Spawn Egg is null", LT_ERROR)
		return
	end

	local pSpawnEgg = LuaSpawnEggObject(pSpawner)

	if (pSpawnEgg == nil) then
		return
	end

	local spawnerName = SceneObject(pSpawner):getDisplayedName()
	local spawnerID = SceneObject(pSpawner):getObjectID()
	local spawnerNumber = readData(spawnerID .. ":" .. name .. ":", i)

	-- Check for chance to activate
	if ((getRandomNumber(100) > self.activationChance)) then
		local inactiveMin = readData(spawnerID .. ":" .. name .. ":" .. "inactiveMin:")
		local inactiveMax = readData(spawnerID .. ":" .. name .. ":" .. "inactiveMax:")

		local randomActiveMili = getRandomNumber(inactiveMin, inactiveMax) * 60 * 1000

		if (self.debug) then
			randomActiveMili = getRandomNumber(self.debugMin, self.debugMax) * 60 * 1000

			print(spawnerName .. " set inactive for " .. randomActiveMili .. " miliseconds.")
		end

		createEvent(randomActiveMili, name, "activateSpawner", pSpawner, "")
		return
	end

	-- Get active times
	local activeMin = readData(spawnerID .. ":" .. name .. ":" .. "activeMin:")
	local activeMax = readData(spawnerID .. ":" .. name .. ":" .. "activeMax:")
	local randomActiveMili = getRandomNumber(activeMin, activeMax) * 60 * 1000

	if (self.debug) then
		randomActiveMili = getRandomNumber(self.debugMin, self.debugMax) * 60 * 1000
	end

	-- Set Spawn Egg Active timer
	pSpawnEgg:setActive(randomActiveMili)

	-- Schedule spawner deactivation
	createEvent(randomActiveMili, name, "deactivateSpawner", pSpawner, "")

	if (self.debug) then
		print(name .. ":activateSpawner for " .. spawnerName .. " #" .. spawnerNumber .. "\n")
	end

	local spawnTables = self.spawnerData[spawnerNumber][9]
	local randomTable = spawnTables[getRandomNumber(#spawnTables)]
	local tableName = randomTable[1]
	local spawnCount = randomTable[2]

	-- Write the current spawn table to data
	pSpawnEgg:setSpawnListName(tableName)

	if (self.debug) then
		print("Spawn Table: " .. tableName .. " Spawn Count: " .. spawnCount)
	end

	local spawnMobiles = self.spawnGroups[tableName]
	local zoneName = self.zoneName
	local x = SceneObject(pSpawner):getPositionX()
	local y = SceneObject(pSpawner):getPositionY()

	-- Store the spawn count
	writeData(spawnerID .. ":" .. name .. ":SpawnCount:", spawnCount)

	-- Spawn Agents
	for i = 1, spawnCount, 1 do
		local randomMob = spawnMobiles[getRandomNumber(#spawnMobiles)]
		local randomX = x + (getRandomNumber(5, 15) - getRandomNumber(5, 15))
		local randomY = y + (getRandomNumber(5, 15) - getRandomNumber(5, 15))

		local pMobile = spawnMobile(zoneName, randomMob, -1, randomX, getWorldFloor(randomX, randomY, zoneName), randomY, 0, 0)

		if (pMobile ~= nil) then
			-- Set the agents spawnerID
			CreatureObject(pMobile):setSpawnerID(spawnerID)

			-- Add observer for agents being killed
			createObserver(OBJECTDESTRUCTION, name, "notifyMobileKilled", pMobile)

			-- Store Mobiles Data
			local mobileID = SceneObject(pMobile):getObjectID()

			writeData(i .. ":" .. spawnerName .. ":", mobileID)
			writeData(mobileID .. ":" .. spawnerName .. ":", i)
		end
	end
end

function InterestAreaSpawner:deactivateSpawner(pSpawner)
	local name = self.screenplayName

	if (pSpawner == nil) then
		Logger:log(name .. " - InterestArea Spawner is null in deactivateSpawner", LT_ERROR)
	end

	local spawnerName = SceneObject(pSpawner):getDisplayedName()
	local spawnerID = SceneObject(pSpawner):getObjectID()
	local pSpawnEgg = LuaSpawnEggObject(pSpawner)

	if (pSpawnEgg == nil) then
		Logger:log(name .. " - InterestArea Spawn Egg is null in deactivateSpawner", LT_ERROR)
		return
	end

	local tableName = pSpawnEgg:getSpawnListName()

	if (self.debug) then
		print(name .. ":deactivateSpawner for " .. spawnerName .. " Spawn Table: " .. tableName)
	end

	-- Clear the Spawn table name
	pSpawnEgg:setSpawnListName("")

	-- Handle Despawning mobiles
	local spawnCount = readData(spawnerID .. ":" .. name .. ":SpawnCount:")

	for i = 1, spawnCount, 1 do
		local mobileID = readData(i .. ":" .. spawnerName .. ":")

		-- Remove the mobiles stored data
		deleteData(i .. ":" .. spawnerName .. ":")
		deleteData(mobileID .. ":" .. spawnerName .. ":")

		local pMobile = getSceneObject(mobileID)

		if (pMobile ~= nil) then
			-- Remove observer for object destruction
			dropObserver(OBJECTDESTRUCTION, name, "notifyMobileKilled", pMobile)

			if (CreatureObject(pMobile):isInCombat()) then
				-- 3 minute timer to forcefully despawn the mobile
				createEvent(self.forceDespawn * 60 * 1000, name, "removeMobile", pMobile, "")
			-- Remove any other creatures besides those tha are already dead
			elseif (not CreatureObject(pMobile):isDead()) then
				SceneObject(pMobile):destroyObjectFromWorld()
			end
		end
	end

	-- Remove the spawn count
	deleteData(spawnerID .. ":" .. name .. ":SpawnCount:")

	local inactiveMin = readData(spawnerID .. ":" .. name .. ":" .. "inactiveMin:")
	local inactiveMax = readData(spawnerID .. ":" .. name .. ":" .. "inactiveMax:")

	local randomInactiveMili = getRandomNumber(inactiveMin, inactiveMax) * 60 * 1000

	if (self.debug) then
		randomInactiveMili = 30 * 1000
	end

	-- Set Spawn Egg Active timer
	pSpawnEgg:setInactive(randomInactiveMili)

	-- Schedule spawner deactivation
	createEvent(randomInactiveMili, name, "activateSpawner", pSpawner, "")

end

function InterestAreaSpawner:respawnMobile(pSpawner, spawnString)
	if (pSpawner == nil) then
		return
	end

	local spawnerName = SceneObject(pSpawner):getDisplayedName()
	local spawnerID = SceneObject(pSpawner):getObjectID()
	local name = self.screenplayName

	local pSpawnEgg = LuaSpawnEggObject(pSpawner)

	if (pSpawnEgg == nil or not pSpawnEgg:isActive()) then
		return
	end

	local tableName = pSpawnEgg:getSpawnListName()
	local spawnNumber = tonumber(spawnString)

	if (self.debug) then
		print(name .. ":respawnMobile for " .. spawnerName .. " Spawn Table: " .. tableName .. " Spawn Number: " .. spawnNumber)
	end

	local spawnMobiles = self.spawnGroups[tableName]
	local zoneName = self.zoneName
	local x = SceneObject(pSpawner):getPositionX()
	local y = SceneObject(pSpawner):getPositionY()

	-- Spawn Agent
	local randomMob = spawnMobiles[getRandomNumber(#spawnMobiles)]
	local randomX = x + (getRandomNumber(5, 15) - getRandomNumber(5, 15))
	local randomY = y + (getRandomNumber(5, 15) - getRandomNumber(5, 15))

	-- Spawn a new mobile
	local pMobile = spawnMobile(zoneName, randomMob, -1, randomX, getWorldFloor(randomX, randomY, zoneName), randomY, 0, 0)

	if (pMobile ~= nil) then
		-- Set the agents spawnerID
		CreatureObject(pMobile):setSpawnerID(spawnerID)

		-- Add observer for agents being killed
		createObserver(OBJECTDESTRUCTION, name, "notifyMobileKilled", pMobile)

		-- Store Mobiles Data
		local mobileID = SceneObject(pMobile):getObjectID()

		writeData(spawnNumber .. ":" .. spawnerName .. ":", mobileID)
		writeData(mobileID .. ":" .. spawnerName .. ":", spawnNumber)
	end
end

function InterestAreaSpawner:removeMobile(pMobile)
	if (pMobile == nil or not SceneObject(pMobile):isCreatureObject()) then
		return
	end

	-- Creature is dead already, will automatically be despawned
	if (CreatureObject(pMobile):isDead()) then
		return
	end

	-- Timer has been waited out, despawn the creature
	SceneObject(pMobile):destroyObjectFromWorld()
end

--[[

		Observers

]]


function InterestAreaSpawner:notifyMobileKilled(pCreature, pKiller)
	if (pCreature == nil) then
		return 1
	end

	local name = self.screenplayName

	if (self.debug) then
		print(name .. ":notifyMobileKilled -- Creature: " .. SceneObject(pCreature):getDisplayedName())
	end

	-- Drop the Observer
	dropObserver(OBJECTDESTRUCTION, name, "notifyMobileKilled", pMobile)

	local spawnerID = CreatureObject(pCreature):getSpawnerID()
	local pSpawner = getSceneObject(spawnerID)
	local mobileID = SceneObject(pCreature):getObjectID()

	if (pSpawner == nil) then
		return 1
	end

	local spawnerName = SceneObject(pSpawner):getDisplayedName()
	local spawnNumber = readData(mobileID .. ":" .. spawnerName .. ":")

	deleteData(spawnNumber .. ":" .. spawnerName .. ":")
	deleteData(mobileID .. ":" .. spawnerName .. ":")

	local pSpawnEgg = LuaSpawnEggObject(pSpawner)

	if (pSpawnEgg == nil) then
		return 1
	end

	local respawnTime = self.respawnTimer

	if (not pSpawnEgg:isActive() or respawnTime < 1) then
		return 1
	end

	if (self.debug) then
		createEvent(5 * 1000, name, "respawnMobile", pSpawner, tostring(spawnNumber))
	else
		createEvent(self.respawnTimer * 1000, name, "respawnMobile", pSpawner, tostring(spawnNumber))
	end

	return 1
end
