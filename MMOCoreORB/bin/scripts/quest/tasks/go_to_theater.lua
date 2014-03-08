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
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil
}

-- Start the GoToTheater.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToTheater:taskStart(pCreatureObject)
	Logger:log("Spawning " .. self.taskName .. " theater.", LT_INFO)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		local spawnPoint = getSpawnArea(pCreatureObject, creatureObject:getWorldPositionX(), creatureObject:getWorldPositionY(), self.minimumDistance, self.maximumDistance, 10, 5)

		if spawnPoint ~= nil then
			Logger:log("Spawn point for theater " .. self.taskName .. ": " .. spawnPoint[1] .. ", " .. spawnPoint[2] .. ", " .. spawnPoint[3] .. ".", LT_INFO)
			local pTheater = spawnSceneObject(creatureObject:getZoneName(), self.theater, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, math.random(0, 359))

			if ObjectManager.withSceneObject(pTheater, function(theater)
				writeData(creatureObject:getObjectID() .. self.taskName .. THEATER_ID_STRING, theater:getObjectID())
				return pTheater
			end) ~= nil then
				local spawnedMobilesList = SpawnMobiles.spawnMobiles(pTheater, self.taskName, self.mobileList)

				if spawnedMobilesList ~= nil then
					local pActiveArea = spawnSceneObject(creatureObject:getZoneName(), ACTIVE_AREA_IFF, spawnPoint[1], 0, spawnPoint[3], 0, 0)

					if pActiveArea ~= nil then
						ObjectManager.withSceneObject(pActiveArea, function(activeArea)
							writeData(creatureObject:getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING, activeArea:getObjectID())
						end)

						local waypointId = ObjectManager.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
							return playerObject:addWaypoint(creatureObject:getZoneName(), self.waypointDescription, "", spawnPoint[1], spawnPoint[3], WAYPOINTWHITE, true, true)
						end)

						if waypointId ~= nil then
							writeData(creatureObject:getObjectID() .. self.taskName .. WAYPOINT_ID_STRING, waypointId)
							createEvent(self.despawnTime, "handleDespawnTheater", self.taskName, pCreatureObject)
							self:callFunctionIfNotNil(self.onSuccessfulSpawn, pCreatureObject)
							return
						end
					end
				end
			end
		end

		-- Something failed above, clean up and end the task.
		Logger:log("Failed to spawn " .. self.taskName .. " theater.", LT_ERROR)
		self:callFunctionIfNotNil(self.onFailedSpawn, pCreatureObject)
		self:finish(pCreatureObject)
	end)
end

-- Handle the task finish event.
-- @param pCreatureObject pointer to the creature object of the player that the event was triggered for.
function GoToTheater:taskFinish(pCreatureObject)
	Logger:log("Despawning " .. self.taskName .. " theater.", LT_INFO)
	ObjectManager.withCreatureAndPlayerObject(pCreatureObject, function(creatureObject, playerObject)
		local waypointId = readData(creatureObject:getObjectID() .. self.taskName .. WAYPOINT_ID_STRING)
		playerObject:removeWaypoint(waypointId, true)

		local activeAreaId = readData(creatureObject:getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING)
		local pActiveArea = getSceneObject(activeAreaId)
		ObjectManager.withSceneObject(pActiveArea, function(activeArea)
			activeArea:destroyObjectFromWorld()
		end)

		local theaterId = readData(creatureObject:getObjectID() .. self.taskName .. THEATER_ID_STRING)
		local pTheater = getSceneObject(theaterId)

		SpawnMobiles.despawnMobiles(pTheater, self.taskName)

		ObjectManager.withSceneObject(pTheater, function(theater)
			theater:destroyObjectFromWorld()
		end)
	end)
end

-- Handle the despawn event.
-- @param pCreatureObject pointer to the creature object of the player that the event was triggered for.
function GoToTheater:handleDespawnEvent(pCreatureObject)
	self:finish(pCreatureObject)
end

return GoToTheater
