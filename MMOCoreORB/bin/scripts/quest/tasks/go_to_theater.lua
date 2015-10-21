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

local Task = require("quest.tasks.task")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
local Logger = require("utils.logger")

local ACTIVE_AREA_IFF = "object/active_area.iff"
local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"
local THEATER_SUM_STRING = "@quest/force_sensitive/intro:theater_sum"

local WAYPOINT_ID_STRING = "waypointId"
local ACTIVE_AREA_ID_STRING = "activeAreaId"
local THEATER_ID_STRING = "theaterId"

GoToTheater = Task:new {
	-- Task properties
	taskName = "",
	-- GoToTheater properties
	minimumDistance = 0,
	maximumDistance = 0,
	theater = "",
	waypointDescription = "",
	mobileList = {},
	despawnTime = 0,
	activeAreaRadius = 0,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil
}

-- Get the spawned mobile list for the theater.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return the spawned mobile list for the theater.
function GoToTheater:getSpawnedMobileList(pCreatureObject)
	Logger:log("Getting the spawned mobile list for " .. self.taskName .. " theater.", LT_INFO)
	local theaterId = readData(SceneObject(pCreatureObject):getObjectID() .. self.taskName .. THEATER_ID_STRING)
	local pTheater = getSceneObject(theaterId)
	return SpawnMobiles.getSpawnedMobiles(pTheater, self.taskName)
end

-- Setup the active area around the theater.
-- @param pCreatureObject pointer to the creature object for whom the theater is created for.
-- @param spawnPoint the coordinates to spawn the active area at.
-- @return true if setup was successful, false otherwise.
function GoToTheater:setupActiveArea(pCreatureObject, spawnPoint)
	Logger:log("Setting up active area for " .. self.taskName .. " theater.", LT_INFO)
	local pActiveArea = spawnActiveArea(CreatureObject(pCreatureObject):getZoneName(), ACTIVE_AREA_IFF, spawnPoint[1], 0, spawnPoint[3], self.activeAreaRadius, 0)

	if (pActiveArea ~= nil) then
		writeData(SceneObject(pCreatureObject):getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING, SceneObject(pActiveArea):getObjectID())
		createObserver(ENTEREDAREA, self.taskName, "handleEnteredAreaEvent", pActiveArea)
		return true
	end

	return false
end

-- Handle the entered active area event.
-- @param pActiveArea pointer to the active area that is entered.
-- @param pCreatureObject pointer to the creature who is entering the active area.
-- @param nothing not used.
function GoToTheater:handleEnteredAreaEvent(pActiveArea, pCreatureObject, nothing)
	if not SceneObject(pCreatureObject):isCreatureObject() then
		return 0
	end

	local storedActiveAreaId = readData(SceneObject(pCreatureObject):getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING)
	if storedActiveAreaId == SceneObject(pActiveArea):getObjectID() then
		Logger:log("Player entered active area of " .. self.taskName .. " theater.", LT_INFO)
		local spawnedObjects = self:getSpawnedMobileList(pCreatureObject)
		self:callFunctionIfNotNil(self.onEnteredActiveArea, nil, pCreatureObject, spawnedObjects)

		return 1
	end

	return 0
end

-- Start the GoToTheater.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToTheater:taskStart(pCreatureObject)
	Logger:log("Spawning " .. self.taskName .. " theater.", LT_INFO)
	local spawnPoint = getSpawnArea(pCreatureObject, SceneObject(pCreatureObject):getWorldPositionX(), SceneObject(pCreatureObject):getWorldPositionY(), self.minimumDistance, self.maximumDistance, 10, 5, true)
	local zoneName = SceneObject(pCreatureObject):getZoneName()
	local playerID = SceneObject(pCreatureObject):getObjectID()

	if spawnPoint ~= nil then
		local pTheater = spawnSceneObject(zoneName, self.theater, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, getRandomNumber(0, 359))

		if (pTheater ~= nil) then
			writeData(playerID .. self.taskName .. THEATER_ID_STRING, SceneObject(pTheater):getObjectID())

			Logger:log("Spawning mobiles for " .. self.taskName .. " theater.", LT_INFO)
			local spawnedMobilesList = SpawnMobiles.spawnMobiles(pTheater, self.taskName, self.mobileList, true)

			if spawnedMobilesList ~= nil then
				if self:setupActiveArea(pCreatureObject, spawnPoint) then
					Logger:log("Creating waypoint for " .. self.taskName .. " theater.", LT_INFO)
					local waypointId
					ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
						waypointId = playerObject:addWaypoint(zoneName, self.waypointDescription, "", spawnPoint[1], spawnPoint[3], WAYPOINTYELLOW, true, true, 0)
					end)

					if waypointId ~= nil then
						writeData(playerID .. self.taskName .. WAYPOINT_ID_STRING, waypointId)
						createEvent(self.despawnTime, self.taskName, "handleDespawnTheater", pCreatureObject)
						self:callFunctionIfNotNil(self.onSuccessfulSpawn, nil, pCreatureObject, spawnedMobilesList)
						return true
					end
				end
			end
		end
	end

	-- Something failed above, clean up and end the task.
	Logger:log("Failed to spawn " .. self.taskName .. " theater.", LT_ERROR)
	self:callFunctionIfNotNil(self.onFailedSpawn, nil, pCreatureObject)
	self:finish(pCreatureObject)

	return false
end

-- Handle the task finish event.
-- @param pCreatureObject pointer to the creature object of the player that the event was triggered for.
function GoToTheater:taskFinish(pCreatureObject)
	Logger:log("Despawning " .. self.taskName .. " theater.", LT_INFO)

	local playerID = SceneObject(pCreatureObject):getObjectID()

	self:removeTheaterWaypoint(pCreatureObject)

	local activeAreaId = readData(playerID .. self.taskName .. ACTIVE_AREA_ID_STRING)
	local pArea = getSceneObject(activeAreaId)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	local theaterId = readData(playerID .. self.taskName .. THEATER_ID_STRING)
	local pTheater = getSceneObject(theaterId)

	if (pTheater ~= nil) then
		SpawnMobiles.despawnMobiles(pTheater, self.taskName)
		SceneObject(pTheater):destroyObjectFromWorld()
	end

	return true
end

-- Handle the despawn event.
-- @param pCreatureObject pointer to the creature object of the player that the event was triggered for.
function GoToTheater:handleDespawnTheater(pCreatureObject)
	self:finish(pCreatureObject)
end

function GoToTheater:removeTheaterWaypoint(pCreatureObject)
	local playerID = SceneObject(pCreatureObject):getObjectID()
	local waypointId = readData(playerID .. self.taskName .. WAYPOINT_ID_STRING)

	ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		playerObject:removeWaypoint(waypointId, true)
	end)
end

return GoToTheater
