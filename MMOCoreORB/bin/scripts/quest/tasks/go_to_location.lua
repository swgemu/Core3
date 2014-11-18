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
	return ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		local pActiveArea = spawnSceneObject(spawnPlanet, ACTIVE_AREA_IFF, spawnPoint.x, 0, spawnPoint.y, 0, 0)

		return ObjectManager.withActiveArea(pActiveArea, function(activeArea)
			return ObjectManager.withSceneObject(pActiveArea, function(activeAreaSceneObject)
				writeData(creatureObject:getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING, activeAreaSceneObject:getObjectID())
				activeArea:setRadius(spawnRadius)
				createObserver(ENTEREDAREA, self.taskName, "handleEnteredAreaEvent", pActiveArea)
				return pActiveArea
			end)
		end)
	end)
end

-- Handle the entered active area event.
-- @param pActiveArea pointer to the active area that is entered.
-- @param pCreatureObject pointer to the creature who is entering the active area.
-- @param nothing not used.
function GoToLocation:handleEnteredAreaEvent(pActiveArea, pCreatureObject, nothing)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		local storedActiveAreaId = readData(creatureObject:getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING)
		ObjectManager.withSceneObject(pActiveArea, function(activeArea)
			if storedActiveAreaId == activeArea:getObjectID() then
				self:onEnteredActiveArea(pCreatureObject)
			end
		end)
	end)
end

-- Start the GoToLocation.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToLocation:taskStart(pCreatureObject)
	Logger:log("Spawning " .. self.taskName .. " active area location.", LT_INFO)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		local pActiveArea = self:setupActiveArea(pCreatureObject, self.spawnPoint, self.spawnPlanet, self.spawnRadius)
		if pActiveArea ~= nil then
			local waypointId = ObjectManager.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
				return playerObject:addWaypoint(self.spawnPlanet, self.waypointDescription, "", self.spawnPoint.x, self.spawnPoint.y, WAYPOINTORANGE, true, true, 0)
			end)

			if waypointId ~= nil then
				writeData(creatureObject:getObjectID() .. self.taskName .. WAYPOINT_ID_STRING, waypointId)
				self:onSuccessfulSpawn(pCreatureObject, pActiveArea)
				return true
			end
		end

		-- Something failed above, clean up and end the task.
		Logger:log("Failed to spawn " .. self.taskName .. " location.", LT_ERROR)
		self:finish(pCreatureObject)
	end)

	return false
end

-- Handle the task finish event.
-- @param pCreatureObject pointer to the creature object of the player that the event was triggered for.
function GoToLocation:taskFinish(pCreatureObject)
	Logger:log("Despawning " .. self.taskName .. " location.", LT_INFO)
	ObjectManager.withCreatureAndPlayerObject(pCreatureObject, function(creatureObject, playerObject)
		local waypointId = readData(creatureObject:getObjectID() .. self.taskName .. WAYPOINT_ID_STRING)
		playerObject:removeWaypoint(waypointId, true)

		local activeAreaId = readData(creatureObject:getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING)
		ObjectManager.withSceneObjectFromId(activeAreaId, function(activeArea)
			activeArea:destroyObjectFromWorld()
		end)

		self:finish(pCreatureObject)
	end)

	return true
end

return GoToLocation
