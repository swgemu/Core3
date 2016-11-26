-- This module handles the go_to_theater script for the quests.
-- It spawns a theater and a set of mobiles in the world and keeps track of them.
-- Parameters:
--  - minimumDistance  		- the minimum distance from the player that the theater should be spawned.
--  - maximumDistance  		- the maximum distance from the player that the theater should be spawned.
--  - theater  	 			- the script to use for the theater.
--  - waypointDescription 	- description for the waypoint that is shown for the player.
--  - mobileList 			- a list of mobiles to spawn around the theater. The list follows the format of the spawn_mobiles module.
--  - despawnTime 			- the time in milliseconds that the theater will remain in the world before being despawned.
--  - onFailedSpawn 		- function that is called if the spawn of the theater or any element creation fails.
--  - onSuccessfulSpawn 	- function that is called if the spawning was successful.

local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
local Logger = require("utils.logger")

local ACTIVE_AREA_IFF = "object/active_area.iff"
local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"
local THEATER_SUM_STRING = "@quest/force_sensitive/intro:theater_sum"

local ACTIVE_AREA_ID_STRING = "activeAreaId"
local THEATER_ID_STRING = "theaterId"

GoToTheater = Task:new {
	-- Task properties
	taskName = "",
	-- GoToTheater properties
	minimumDistance = 0,
	maximumDistance = 0,
	theater = {},
	waypointDescription = "",
	createWaypoint = true,
	mobileList = {},
	mobileListWithLoc = {},
	despawnTime = 0,
	activeAreaRadius = 0,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil,
	onTheaterDespawn = nil
}

-- Get the spawned mobile list for the theater.
-- @param pPlayer pointer to the creature object of the player.
-- @return the spawned mobile list for the theater.
function GoToTheater:getSpawnedMobileList(pPlayer)
	Logger:log("Getting the spawned mobile list for " .. self.taskName .. " theater.", LT_INFO)
	local theaterId = readData(SceneObject(pPlayer):getObjectID() .. self.taskName .. THEATER_ID_STRING)
	local pTheater = getSceneObject(theaterId)

	if pTheater == nil then
		return nil
	end

	return SpawnMobiles.getSpawnedMobiles(pTheater, self.taskName)
end

-- Setup the active area around the theater.
-- @param pPlayer pointer to the creature object for whom the theater is created for.
-- @param spawnPoint the coordinates to spawn the active area at.
-- @return true if setup was successful, false otherwise.
function GoToTheater:setupActiveArea(pPlayer, spawnPoint)
	Logger:log("Setting up active area for " .. self.taskName .. " theater.", LT_INFO)
	local pActiveArea = spawnActiveArea(CreatureObject(pPlayer):getZoneName(), ACTIVE_AREA_IFF, spawnPoint[1], 0, spawnPoint[3], self.activeAreaRadius, 0)

	if (pActiveArea ~= nil) then
		writeData(SceneObject(pPlayer):getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING, SceneObject(pActiveArea):getObjectID())
		createObserver(ENTEREDAREA, self.taskName, "handleEnteredAreaEvent", pActiveArea)
		return true
	end

	return false
end

-- Handle the entered active area event.
-- @param pActiveArea pointer to the active area that is entered.
-- @param pPlayer pointer to the creature who is entering the active area.
-- @param nothing not used.
function GoToTheater:handleEnteredAreaEvent(pActiveArea, pPlayer, nothing)
	if not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local storedActiveAreaId = readData(SceneObject(pPlayer):getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING)
	if storedActiveAreaId == SceneObject(pActiveArea):getObjectID() then
		Logger:log("Player entered active area of " .. self.taskName .. " theater.", LT_INFO)
		local spawnedObjects = self:getSpawnedMobileList(pPlayer)
		self:callFunctionIfNotNil(self.onEnteredActiveArea, nil, pPlayer, spawnedObjects)

		return 1
	end

	return 0
end

-- Start the GoToTheater.
-- @param pPlayer pointer to the creature object of the player.
function GoToTheater:taskStart(pPlayer)
	Logger:log("Spawning " .. self.taskName .. " theater.", LT_INFO)

	local zoneName = SceneObject(pPlayer):getZoneName()
	local spawnPoint = getSpawnArea(zoneName, SceneObject(pPlayer):getWorldPositionX(), SceneObject(pPlayer):getWorldPositionY(), self.minimumDistance, self.maximumDistance, 20, 10, true)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (spawnPoint == nil) then
		printf("Error in GoToTheater:taskStart() for task " .. self.taskName .. ", spawnPoint is nil.\n")
	end

	if spawnPoint ~= nil then
		local pTheater = spawnSceneObject(zoneName, "object/static/structure/nobuild/nobuild_32.iff", spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0)

		if (pTheater ~= nil) then
			writeData(playerID .. self.taskName .. THEATER_ID_STRING, SceneObject(pTheater):getObjectID())

			for i = 1, #self.theater, 1 do
				local objectData = self.theater[i]
				local pObject = spawnSceneObject(zoneName, objectData.template, spawnPoint[1] + objectData.xDiff, spawnPoint[2]  + objectData.zDiff, spawnPoint[3] + objectData.yDiff, 0, objectData.heading)

				if (pObject ~= nil) then
					writeData(playerID .. self.taskName .. "theaterObject" .. i, SceneObject(pObject):getObjectID())
				end
			end

			Logger:log("Spawning mobiles for " .. self.taskName .. " theater.", LT_INFO)
			local spawnedMobilesList = SpawnMobiles.spawnMobiles(pTheater, self.taskName, self.mobileList, true)
			local spawnedMobilesWithLocList = SpawnMobiles.spawnMobilesWithLoc(pTheater, self.taskName, self.mobileListWithLoc)

			if (spawnedMobilesList == nil and spawnedMobilesWithLocList ~= nil) then
				spawnedMobilesList = spawnedMobilesWithLocList
			end

			if spawnedMobilesList ~= nil or #self.mobileList == 0 then
				if self:setupActiveArea(pPlayer, spawnPoint) then
					local waypointId

					if (self.createWaypoint) then
						local pGhost = CreatureObject(pPlayer):getPlayerObject()

						if (pGhost ~= nil) then
							waypointId = PlayerObject(pGhost):addWaypoint(zoneName, self.waypointDescription, "", spawnPoint[1], spawnPoint[3], WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
						end
					end

					if waypointId ~= nil or not self.createWaypoint then
						createEvent(self.despawnTime, self.taskName, "handleDespawnTheater", pPlayer, "")
						self:callFunctionIfNotNil(self.onSuccessfulSpawn, nil, pPlayer, spawnedMobilesList)
						return true
					end
				end
			end
		end
	end

	-- Something failed above, clean up and end the task.
	Logger:log("Failed to spawn " .. self.taskName .. " theater.", LT_ERROR)
	self:callFunctionIfNotNil(self.onFailedSpawn, nil, pPlayer)
	self:finish(pPlayer)

	return false
end

-- Handle the task finish event.
-- @param pPlayer pointer to the creature object of the player that the event was triggered for.
function GoToTheater:taskFinish(pPlayer)
	Logger:log("Despawning " .. self.taskName .. " theater.", LT_INFO)

	local playerID = SceneObject(pPlayer):getObjectID()

	self:removeTheaterWaypoint(pPlayer)

	local activeAreaId = readData(playerID .. self.taskName .. ACTIVE_AREA_ID_STRING)
	local pArea = getSceneObject(activeAreaId)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	for i = 1, #self.theater, 1 do
		local objectID = readData(playerID .. self.taskName .. "theaterObject" .. i)
		local pObject = getSceneObject(objectID)
		if (pObject ~= nil) then
			SceneObject(pObject):destroyObjectFromWorld()
			deleteData(playerID .. self.taskName .. "theaterObject" .. i)
		end
	end

	local theaterId = readData(playerID .. self.taskName .. THEATER_ID_STRING)
	local pTheater = getSceneObject(theaterId)

	if (pTheater ~= nil) then
		SpawnMobiles.despawnMobiles(pTheater, self.taskName)
		SceneObject(pTheater):destroyObjectFromWorld()
	end

	self:callFunctionIfNotNil(self.onTheaterDespawn, nil, pPlayer)

	return true
end

-- Handle the despawn event.
-- @param pPlayer pointer to the creature object of the player that the event was triggered for.
function GoToTheater:handleDespawnTheater(pPlayer)
	if (not self:hasTaskStarted(pPlayer)) then
		return
	end
	local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()

	if (pPlayerObj ~= nil and PlayerObject(pPlayerObj):isOnline()) then
		createEvent(self.despawnTime / 2, self.taskName, "handleDespawnTheater", pPlayer, "")
		return
	end

	self:finish(pPlayer)
end

function GoToTheater:removeTheaterWaypoint(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
end

return GoToTheater
