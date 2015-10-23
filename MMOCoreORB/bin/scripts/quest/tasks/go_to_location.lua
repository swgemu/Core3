-- This module handles the go_to_location script for the quests.
-- It spawns an active area in the world where the player must go.
-- Parameters:
--  - waypointDescription 	- description for the waypoint that is shown for the player.

local Task = require("quest.tasks.task")
local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

local ACTIVE_AREA_IFF = "object/active_area.iff"

local ACTIVE_AREA_ID_STRING = "activeAreaId"
local WAYPOINT_ID_STRING = "waypointId"

GoToLocation = Task:new {
	-- Task properties
	taskName = "",
	-- GoToLocation properties
	waypointDescription = "",
	spawnPoint = {},

	randomLocation = false,
	randomMinDistance = 0,
	randomMaxDistance = 0,

	spawnPlanet = "",
	spawnRadius = nil,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil
}


-- Setup the active area around.
-- @param pCreatureObject pointer to the creature object for whom the area is created for.
-- @param spawnPointCoordinates where to spawn the active area.
-- @param spawnPointPlanet planet to spawn it on.
-- @return true if setup was successful, false otherwise.
function GoToLocation:setupActiveArea(pCreatureObject, spawnPoint, spawnPlanet, spawnRadius)
	local pActiveArea = spawnActiveArea(spawnPlanet, ACTIVE_AREA_IFF, spawnPoint.x, 0, spawnPoint.y, spawnRadius, 0)

	if (pActiveArea ~= nil) then
		writeData(SceneObject(pCreatureObject):getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING, SceneObject(pActiveArea):getObjectID())
		createObserver(ENTEREDAREA, self.taskName, "handleEnteredAreaEvent", pActiveArea)
	end

	return pActiveArea
end

-- Handle the entered active area event.
-- @param pActiveArea pointer to the active area that is entered.
-- @param pCreatureObject pointer to the creature who is entering the active area.
-- @param nothing not used.
function GoToLocation:handleEnteredAreaEvent(pActiveArea, pCreatureObject, nothing)
	if not SceneObject(pCreatureObject):isCreatureObject() then
		return 0
	end

	local storedActiveAreaId = readData(SceneObject(pCreatureObject):getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING)

	if storedActiveAreaId == SceneObject(pActiveArea):getObjectID() then
		self:onEnteredActiveArea(pCreatureObject)
		return 1
	end

	return 0
end

-- Start the GoToLocation.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToLocation:taskStart(pCreatureObject)
	Logger:log("Spawning " .. self.taskName .. " active area location.", LT_INFO)

	local point = self.spawnPoint

	if (self.randomLocation) then
		local tempPoint = getSpawnPoint(pCreatureObject, SceneObject(pCreatureObject):getWorldPositionX(), SceneObject(pCreatureObject):getWorldPositionY(), self.randomMinDistance, self.randomMaxDistance, true)
		point.x = tempPoint[1]
		point.y = tempPoint[3]
	end

	local pActiveArea = self:setupActiveArea(pCreatureObject, point, self.spawnPlanet, self.spawnRadius)
	if pActiveArea ~= nil then
		local waypointId = ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
			return playerObject:addWaypoint(self.spawnPlanet, self.waypointDescription, "", point.x, point.y, WAYPOINTORANGE, true, true, 0)
		end)

		if waypointId ~= nil then
			writeData(SceneObject(pCreatureObject):getObjectID() .. self.taskName .. WAYPOINT_ID_STRING, waypointId)
			self:onSuccessfulSpawn(pCreatureObject, pActiveArea)
			return true
		end
	end

	-- Something failed above, clean up and end the task.
	Logger:log("Failed to spawn " .. self.taskName .. " location.", LT_ERROR)
	self:finish(pCreatureObject)

	return false
end

-- Handle the task finish event.
-- @param pCreatureObject pointer to the creature object of the player that the event was triggered for.
function GoToLocation:taskFinish(pCreatureObject)
	Logger:log("Despawning " .. self.taskName .. " location.", LT_INFO)
	local playerID = SceneObject(pCreatureObject):getObjectID()
	local waypointId = readData(playerID .. self.taskName .. WAYPOINT_ID_STRING)

	ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		playerObject:removeWaypoint(waypointId, true)
	end)

	local areaID = readData(playerID .. self.taskName .. ACTIVE_AREA_ID_STRING)
	local pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	return true
end

return GoToLocation
