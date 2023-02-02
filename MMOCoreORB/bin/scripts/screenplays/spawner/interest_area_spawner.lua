InterestAreaSpawner = ScreenPlay:new {
	screenplayName = "",
	debug = true,
	planet = "",

	maxSpawns = 1,
	delayChance = 10, -- % chance for spawner to go on delay out of 100
	delayTimer = 180, -- time in seconds the spawner will not delayed

	-- {respawn, x, z, y, direction}
	spawnerLocations = {},
	-- {"spawn_template", # permitted active spawner of this type, respawnTimer}
	-- Collective total permitted must be greater than the maxSpawns
	-- Type is stored by first spawn listed
	spawns = {},
}

--[[ Interest Area Spawner
	Parent class functions to manage spawns for an interest area (POI, city etc)
	This will handle whichs spawners are active, how often and what they spawn
]]

function InterestAreaSpawner:createSpawners()
	local name = self.screenplayName
	local locationTable = self.spawnerLocations
	local count = 0

	if (self.debug) then
		print(name .. ":createSpawners() called table size " .. #locationTable)
	end

	if (self.maxSpawns > 0 and self.maxSpawns > #locationTable) then
		Logger:log(name .. " maxSpawns is greater than available spawn points", LT_ERROR)
		return
	end

	if (self.debug) then
		print(name .. " createSpawners with total of " .. #locationTable .. " spawners")
	end

	for i = 1, #locationTable, 1 do
		local spawn = locationTable[i]

		local pSpawner = spawnSceneObject(self.planet, "object/tangible/spawning/spawn_egg.iff", spawn[1], spawn[2], spawn[3], 0, math.rad(spawn[4]))

		if (pSpawner ~= nil and SceneObject(pSpawner):isSpawnEggObject()) then
			if (not self.debug) then
				TangibleObject(pSpawner):setInvisible(true)
			end

			local spawnEgg = LuaSpawnEggObject(pSpawner)

			if (spawnEgg ~= nil) then
				spawnEgg:setActiveStatus(false)
				spawnEgg:setAreaName(name)
			end

			count = count + 1

			local spawnerID = SceneObject(pSpawner):getObjectID()

			writeData(name .. ":Spawner:" .. i .. ":", spawnerID)
			writeData(spawnerID .. ":" .. name .. ":", i)
		end
	end

	if (self.debug) then
		print(self.screenplayName .. " -- Spawned " .. tostring(count) .. " Interest Area Spawners.")
	end

	writeData(name .. ":TotalSpawners:", count)
end

function InterestAreaSpawner:populateSpawners()
	local name = self.screenplayName
	local totalSpawners = readData(name .. ":TotalSpawners:")
	local activeSpawners = readData(name .. ":ActiveSpawners:")

	if (self.debug) then
		print(name .. ":populateSpawners - called: " .. name .. " Total Spawners: " ..  totalSpawners .. " Active Spawners: " .. activeSpawners)
	end

	for i = 1, totalSpawners, 1 do
		local spawnerID = readData(name .. ":Spawner:" .. i .. ":")
		local pSpawner = getSceneObject(spawnerID)

		if (pSpawner ~= nil) then
			local spawnEgg = LuaSpawnEggObject(pSpawner)

			if ((getRandomNumber(100) <= self.delayChance)) then
				local timer = self.delayTimer * 1000

				createEvent(timer, name, "repopulateSpawner", pSpawner, "")
				goto skip
			end

			local spawnTables = self.spawns
			local randomMob = spawnTables[getRandomNumber(#spawnTables)]
			local typeCount = readData(name .. ":" .. randomMob[1] .. ":Count:")

			if (typeCount >= randomMob[2]) then
				local timer = self.delayTimer * 1000

				createEvent(timer, name, "repopulateSpawner", pSpawner, "")
				goto skip
			end

			local x = SceneObject(pSpawner):getPositionX() + getRandomNumber(20)
			local y = SceneObject(pSpawner):getPositionY() + getRandomNumber(20)
			local z = getWorldFloor(x, y, self.planet)

			local pMobile = spawnMobile(self.planet, randomMob[1], 0, x, z, y, SceneObject(pSpawner):getDirectionAngle(), 0)

			if (pMobile ~= nil) then
				activeSpawners = activeSpawners + 1

				if (spawnEgg ~= nil) then
					spawnEgg:setActiveStatus(true)
					spawnEgg:setSpawn(randomMob[1])
					spawnEgg:setRespawnTime(randomMob[3])
				end

				CreatureObject(pMobile):setSpawnerID(spawnerID)
				createObserver(OBJECTDESTRUCTION, name, "notifyCreatureKilled", pMobile)

				typeCount = typeCount + 1
				writeData(name .. ":" .. randomMob[1] .. ":Count:", typeCount)
			end
		end
		::skip::
	end

	writeData(name .. ":ActiveSpawners:", activeSpawners)
end

function InterestAreaSpawner:repopulateSpawner(pSpawner)
	if (pSpawner == nil) then
		Logger:log("InterestAreaSpawner:respawnCreature -- pSpawner is nil.", LT_ERROR)
		return
	end

	local spawnEgg = LuaSpawnEggObject(pSpawner)
	local name = spawnEgg:getAreaName()
	local isActive = spawnEgg:isActive()
	local activeSpawners = readData(name .. ":ActiveSpawners:")

	if (self.debug) then
		print(name .. ":respawnCreature with " ..activeSpawners .. " active spawners.")
	end

	if ((not isActive and activeSpawners >= self.maxSpawns) or (getRandomNumber(100) < self.delayChance)) then
		if (isActive) then
			spawnEgg:setActiveStatus(false)
			activeSpawners = activeSpawners - 1
		end

		local timer = self.delayTimer * 1000

		if (self.debug) then
			print("Spawner Delayed - timer = " .. timer)
		end

		createEvent(timer, name, "repopulateSpawner", pSpawner, "")
		writeData(name .. ":ActiveSpawners:", activeSpawners)
		return
	end

	local spawnTable = self.spawns
	local randomMob = spawnTable[getRandomNumber(#spawnTable)]
	local typeCount = readData(name .. ":" .. randomMob[1] .. ":Count:")

	if (randomMob ~= nil) then
		local x = SceneObject(pSpawner):getPositionX() + getRandomNumber(20)
		local y = SceneObject(pSpawner):getPositionY() + getRandomNumber(20)
		local z = getWorldFloor(x, y, self.planet)

		local pMobile = spawnMobile(self.planet, randomMob[1], 0, x, z, y, SceneObject(pSpawner):getDirectionAngle(), 0)

		if (pMobile ~= nil) then
			if (self.debug) then
				print(name .. ":respawnCreature mobile spawned")
			end

			if (not isActive) then
				activeSpawners = activeSpawners + 1

				spawnEgg:setActiveStatus(true)
				spawnEgg:setSpawn(randomMob[1])
			end

			createObserver(OBJECTDESTRUCTION, name, "notifyCreatureKilled", pMobile)
			CreatureObject(pMobile):setSpawnerID(SceneObject(pSpawner):getObjectID())

			typeCount = typeCount + 1
			writeData(name .. ":" .. randomMob[1] .. ":Count:", typeCount)
		end
	end

	writeData(name .. ":ActiveSpawners:", activeSpawners)
end


function InterestAreaSpawner:notifyCreatureKilled(pCreature, pKiller)
	if (pCreature == nil or not SceneObject(pCreature):isCreatureObject()) then
		return 1
	end

	local spawnerID = CreatureObject(pCreature):getSpawnerID()
	local pSpawner = getSceneObject(spawnerID)

	if (pSpawner ~= nil) then
		local spawnEgg = LuaSpawnEggObject(pSpawner)
		local spawnType = SceneObject(pCreature):getObjectName()

		if (spawnEgg ~= nil) then
			local name = spawnEgg:getAreaName()
			local timer = spawnEgg:getRespawnTime() * 1000

			createEvent(timer, name, "repopulateSpawner", pSpawner, "")

			local typeCount = readData(name .. ":" .. spawnType .. ":Count:")

			if (typeCount > 0) then
				typeCount = typeCount - 1
			end

			if (self.debug) then
				print(name .. ":notifyCreatureKilled -- repopulateSpawner scheduled for " .. spawnType .. " with a type count of " .. typeCount)
			end

			writeData(name .. ":" .. spawnType .. ":Count:", typeCount)
		end
	end

	return 1
end