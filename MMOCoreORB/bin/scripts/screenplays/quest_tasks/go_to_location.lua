-- This module handles the go_to_location script for the quests.
-- It spawns an active area in the world where the player must go.
-- Parameters:
--  - waypointDescription 	- description for the waypoint that is shown for the player.

local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

local ACTIVE_AREA_IFF = "object/active_area.iff"

local ACTIVE_AREA_ID_STRING = "activeAreaId"

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
-- @param pPlayer pointer to the creature object for whom the area is created for.
-- @param spawnPointCoordinates where to spawn the active area.
-- @param spawnPointPlanet planet to spawn it on.
-- @return true if setup was successful, false otherwise.
function GoToLocation:setupActiveArea(pPlayer, spawnPoint, spawnPlanet, spawnRadius)
	local pActiveArea = spawnActiveArea(spawnPlanet, ACTIVE_AREA_IFF, spawnPoint.x, 0, spawnPoint.y, spawnRadius, 0)

	if (pActiveArea ~= nil) then
		writeData(SceneObject(pPlayer):getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING, SceneObject(pActiveArea):getObjectID())
		createObserver(ENTEREDAREA, self.taskName, "handleEnteredAreaEvent", pActiveArea)
	end

	return pActiveArea
end

-- Handle the entered active area event.
-- @param pActiveArea pointer to the active area that is entered.
-- @param pPlayer pointer to the creature who is entering the active area.
-- @param nothing not used.
function GoToLocation:handleEnteredAreaEvent(pActiveArea, pPlayer, nothing)
	if not SceneObject(pPlayer):isCreatureObject() then
		return 0
	end

	local storedActiveAreaId = readData(SceneObject(pPlayer):getObjectID() .. self.taskName .. ACTIVE_AREA_ID_STRING)

	if storedActiveAreaId == SceneObject(pActiveArea):getObjectID() then
		self:onEnteredActiveArea(pPlayer)
		return 1
	end

	return 0
end

-- Start the GoToLocation.
-- @param pPlayer pointer to the creature object of the player.
function GoToLocation:taskStart(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		Logger:log("Failed to spawn " .. self.taskName .. " location.", LT_ERROR)
		return false
	end

	Logger:log("Spawning " .. self.taskName .. " active area location.", LT_INFO)

	local spawnPlanet = self.spawnPlanet

	if (spawnPlanet == "") then
		spawnPlanet = SceneObject(pPlayer):getZoneName()
	end

	local point = self.spawnPoint

	if (self.randomLocation) then
		local tempX, tempY
		if next(point) == nil then
			tempX = SceneObject(pPlayer):getWorldPositionX()
			tempY = SceneObject(pPlayer):getWorldPositionY()
		else
			tempX = point.x
			tempY = point.y
		end

		local tempPoint = getSpawnArea(spawnPlanet, tempX, tempY, self.randomMinDistance, self.randomMaxDistance, 20, 10, true)
		point.x = tempPoint[1]
		point.y = tempPoint[3]
	end

	local pActiveArea = self:setupActiveArea(pPlayer, point, spawnPlanet, self.spawnRadius)
	if pActiveArea ~= nil then
		local waypointId = PlayerObject(pGhost):addWaypoint(spawnPlanet, self.waypointDescription, "", point.x, point.y, WAYPOINTORANGE, true, true, WAYPOINTQUESTTASK)

		if waypointId ~= nil then
			self:onSuccessfulSpawn(pPlayer, pActiveArea)
			return true
		end
	end

	-- Something failed above, clean up and end the task.
	Logger:log("Failed to spawn " .. self.taskName .. " location.", LT_ERROR)
	self:finish(pPlayer)

	return false
end

-- Handle the task finish event.
-- @param pPlayer pointer to the creature object of the player that the event was triggered for.
function GoToLocation:taskFinish(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	Logger:log("Despawning " .. self.taskName .. " location.", LT_INFO)
	local playerID = SceneObject(pPlayer):getObjectID()

	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)

	local areaID = readData(playerID .. self.taskName .. ACTIVE_AREA_ID_STRING)
	local pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	return true
end

return GoToLocation
