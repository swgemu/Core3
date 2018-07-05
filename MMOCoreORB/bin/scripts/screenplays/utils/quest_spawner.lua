local ObjectManager = require("managers.object.object_manager")

--[[
Required table structures:

dataTable = {
	spawnerPulse = 30, -- Time between spawn pulses
	maxSpawn = 10, -- Max mobiles to spawn over the entire lifetime of the spawner
	maxPopulation = 5, -- Max mobs to have up at any one time
	expireTime = 20 * 60 * 1000, -- Time until spawner should expire
}

spawnList = {
	-- { "template", minToSpawn, maxSpawn, weight }
	-- Number to spawn per pulse will be random between minToSpawn and maxSpawn, unless the number would exceed maxPopulation or maxSpawn in the dataTable
	{ "mobile1", 1, 2, 1 },
	{ "mobile2", 2, 3, 2 } 
}
]]

QuestSpawner = {}

function QuestSpawner:createQuestSpawner(screenplayName, dataTableName, spawnListName, xLoc, zLoc, yLoc, cellID, planet, pTheater)
	local sPlay = _G[screenplayName]

	if (sPlay == nil) then
		printLuaError("QuestSpawner:createQuestSpawner, invalid screenplay name.")
		return
	end

	local dataTable = sPlay[dataTableName]

	if (dataTable == nil) then
		printLuaError("QuestSpawner:createQuestSpawner, unable to find data table " .. dataTableName .. " in screenplay " .. screenplayName)
		return
	end

	local spawnList = sPlay[spawnListName]

	if (spawnList == nil) then
		printLuaError("QuestSpawner:createQuestSpawner, unable to find spawn list table " .. spawnList .. " in screenplay " .. screenplayName)
		return
	end

	local pSpawner = spawnSceneObject(planet, "object/tangible/spawning/quest_spawner.iff", xLoc, zLoc, yLoc, cellID, 0)

	if (pSpawner == nil) then
		printLuaError("QuestSpawner:createQuestSpawner, unable to create spawner object.")
		return
	end

	local spawnerID = SceneObject(pSpawner):getObjectID()

	writeStringSharedMemory(spawnerID .. ":screenplayName", screenplayName)
	writeStringSharedMemory(spawnerID .. ":dataTableName", dataTableName)
	writeStringSharedMemory(spawnerID .. ":spawnListName", spawnListName)

	if (pTheater ~= nil) then
		writeData(spawnerID .. ":parentID", SceneObject(pTheater):getObjectID())
	end

	if (dataTable.expireTime > 0) then
		writeData(spawnerID .. ":expireTime", (os.time() * 1000) + dataTable.expireTime)
	else
		deleteData(spawnerID .. ":expireTime")
	end

	createEvent(5 * 1000, "QuestSpawner", "doQuestSpawnerPulse", pSpawner, "")
end

function QuestSpawner:doQuestSpawnerPulse(pSpawner)
	if (pSpawner == nil) then
		return
	end

	local spawnerID = SceneObject(pSpawner):getObjectID()

	local screenplayName = readStringSharedMemory(spawnerID .. ":screenplayName")
	local dataTableName = readStringSharedMemory(spawnerID .. ":dataTableName")

	local sPlay = _G[screenplayName]

	if (sPlay == nil) then
		printLuaError("QuestSpawner:doQuestSpawnerPulse, invalid screenplay name.")
		return
	end

	local dataTable = sPlay[dataTableName]

	if (dataTable == nil) then
		printLuaError("QuestSpawner:doQuestSpawnerPulse, unable to find data table " .. dataTableName .. " in screenplay " .. screenplayName)
		return
	end

	local spawnVerifyFunc = sPlay[dataTable.spawnVerifyFunc]

	if (spawnVerifyFunc ~= nil) then
		local shouldCreateSpawn = spawnVerifyFunc()

		if (not shouldCreateSpawn) then
			createEvent(10 * 1000, "QuestSpawner", "destroyQuestSpawner", pSpawner, "")
			return
		end
	end

	self:createSpawn(pSpawner)

	local expireTime = readData(spawnerID .. ":expireTime")
	if (expireTime > 0 and (os.time() * 1000) >= expireTime) then
		createEvent(10 * 1000, "QuestSpawner", "destroyQuestSpawner", pSpawner, "")
		return
	end

	local curSpawn = readData(spawnerID .. ":curSpawn")

	if (curSpawn >= dataTable.maxSpawn) then
		createEvent(10 * 1000, "QuestSpawner", "destroyQuestSpawner", pSpawner, "")
		return
	end

	local pulse = dataTable.spawnerPulse

	if (pulse == 0) then
		pulse = 30 * 1000 -- Default value
	end

	createEvent(pulse, "QuestSpawner", "doQuestSpawnerPulse", pSpawner, "")
end

function QuestSpawner:createSpawn(pSpawner)
	if (pSpawner == nil) then
		return
	end

	local spawnerID = SceneObject(pSpawner):getObjectID()

	local screenplayName = readStringSharedMemory(spawnerID .. ":screenplayName")
	local spawnListName = readStringSharedMemory(spawnerID .. ":spawnListName")
	local dataTableName = readStringSharedMemory(spawnerID .. ":dataTableName")

	local sPlay = _G[screenplayName]

	if (sPlay == nil) then
		printLuaError("QuestSpawner:createSpawn, invalid screenplay name.")
		return
	end

	local spawnList = sPlay[spawnListName]

	if (spawnList == nil) then
		printLuaError("QuestSpawner:createSpawn, unable to find spawn list table " .. spawnListName .. " in screenplay " .. screenplayName)
		return
	end

	local dataTable = sPlay[dataTableName]

	if (dataTable == nil) then
		printLuaError("QuestSpawner:createSpawn, unable to find data table " .. dataTableName .. " in screenplay " .. screenplayName)
		return
	end

	local maxSpawn = dataTable.maxSpawn
	local maxPop = dataTable.maxPopulation
	local curPop = readData(spawnerID .. ":curPopulation")
	local curSpawn = readData(spawnerID .. ":curSpawn")

	if (curPop >= maxPop or curSpawn >= maxSpawn) then
		return
	end

	local weightedSpawnList = { }
	local totalWeight = 0

	for i = 1, #spawnList, 1 do
		local spawn = spawnList[i]
		local tempTable = { spawn[1], spawn[2], spawn[3] }
		totalWeight = totalWeight + spawn[4]

		for j = 1, spawn[4], 1 do
			table.insert(weightedSpawnList, tempTable)
		end
	end

	local randWeight = getRandomNumber(1, totalWeight)
	local randSpawn = weightedSpawnList[randWeight]

	local numToSpawn = getRandomNumber(randSpawn[2], randSpawn[3])

	local spawnerX = SceneObject(pSpawner):getPositionX()
	local spawnerY = SceneObject(pSpawner):getPositionY()

	local zoneName = SceneObject(pSpawner):getZoneName()
	local inNavMesh = SceneObject(pSpawner):isInNavMesh()

	while (numToSpawn > 0) do
		if (maxPop > curPop) then
			local spawnPoint

			if (inNavMesh) then
				spawnPoint = getSpawnPointInArea(zoneName, spawnerX, spawnerY, 10)
			else
				spawnPoint = getSpawnPoint(zoneName, spawnerX, spawnerY, 5, 10, true)
			end

			if (spawnPoint == nil) then
				spawnPoint = { spawnerX, getTerrainHeight(pSpawner, spawnerX, spawnerY), spawnerY }
			end

			local pNpc = spawnMobile(zoneName, randSpawn[1], 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], getRandomNumber(360) - 180, 0)

			if (pNpc ~= nil) then
				writeData(SceneObject(pNpc):getObjectID() .. ":spawnerID", spawnerID)
				createObserver(OBJECTDESTRUCTION, "QuestSpawner", "notifyMobileKilled", pNpc)
				createEvent(dataTable.mobileLifespan, "QuestSpawner", "destroySpawnerMobile", pNpc, "")
				curPop = curPop + 1

				local setupFunc = sPlay[dataTable.aiHandlerFunc]

				if (setupFunc ~= nil) then
					createEvent(10, screenplayName, dataTable.aiHandlerFunc, pNpc, "")
				end
			end
		end

		numToSpawn = numToSpawn - 1
	end

	writeData(spawnerID .. ":curPopulation", curPop)
	writeData(spawnerID .. ":curSpawn", curSpawn + 1)
end


function QuestSpawner:notifyMobileKilled(pVictim, pAttacker)
	if (pVictim == nil) then
		return 1
	end

	local mobileID = SceneObject(pVictim):getObjectID()
	local spawnerID = readData(mobileID .. ":spawnerID")

	local curPop = readData(spawnerID .. ":curPopulation")
	writeData(spawnerID .. ":curPopulation", curPop - 1)

	deleteData(mobileID .. ":spawnerID")

	return 1
end

function QuestSpawner:destroySpawnerMobile(pMobile)
	if (pMobile == nil) then
		return
	end

	if (AiAgent(pMobile):isInCombat()) then
		createEvent(10 * 1000, "QuestSpawner", "destroySpawnerMobile", pMobile, "")
		return
	end

	deleteData(SceneObject(pMobile):getObjectID() .. ":spawnerID")

	SceneObject(pMobile):destroyObjectFromWorld()
end

function QuestSpawner:destroyQuestSpawner(pSpawner)
	if (pSpawner == nil) then
		return
	end

	local spawnerID = SceneObject(pSpawner):getObjectID()

	deleteStringSharedMemory(spawnerID .. ":screenplayName")
	deleteStringSharedMemory(spawnerID .. ":dataTableName")
	deleteStringSharedMemory(spawnerID .. ":spawnListName")
	deleteData(spawnerID .. ":curPopulation")
	deleteData(spawnerID .. ":curSpawn")
	deleteData(spawnerID .. ":expireTime")

	SceneObject(pSpawner):destroyObjectFromWorld()
end
