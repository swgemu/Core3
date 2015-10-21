local Task = require("quest.tasks.task")
local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

Escort = Task:new {
	-- Task properties
	taskName = "",
	-- GoToLocation properties
	waypointDescription = "",
	returnPoint = {},
	returnPlanet = "",
	areaRadius = 32,

	escortDespawnTime = 60 * 1000, -- Number of milliseconds after entering active area

	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil
}

function Escort:setupActiveArea(pCreatureObject, spawnPoint, spawnPlanet, spawnRadius)
	local pActiveArea = spawnActiveArea(spawnPlanet, "object/active_area.iff", spawnPoint.x, 0, spawnPoint.y, spawnRadius, 0)

	if (pActiveArea ~= nil) then
		writeData(SceneObject(pCreatureObject):getObjectID() .. self.taskName .. "areaID", SceneObject(pActiveArea):getObjectID())
		createObserver(ENTEREDAREA, self.taskName, "handleEnteredAreaEvent", pActiveArea)
	end

	return pActiveArea
end

function Escort:handleEnteredAreaEvent(pActiveArea, pCreatureObject)
	if not SceneObject(pCreatureObject):isCreatureObject() then
		return 0
	end

	local creatureID = SceneObject(pCreatureObject):getObjectID()
	local escortID = readData(SceneObject(pActiveArea):getObjectID() .. self.taskName .. "escortID")

	if escortID == creatureID then
		local playerID = readData(creatureID .. self.taskName .. "ownerID")
		local pPlayer = getSceneObject(playerID)

		if (pPlayer == nil) then
			return 1
		end

		writeData(creatureID .. ":safe", 1)

		self:callFunctionIfNotNil(self.onEnteredActiveArea, nil, pPlayer)

		self:finish(pPlayer)
		return 1
	end

	return 0
end

function Escort:handleEscortDespawn(pEscort)
	if (pEscort == nil) then
		return
	end

	local escortID = SceneObject(pEscort):getObjectID()
	local playerID = readData(escortID .. self.taskName .. "ownerID")

	deleteData(playerID .. self.taskName .. "escortID")
	deleteData(escortID .. self.taskName .. "ownerID")
	deleteData(escortID .. ":safe")

	SceneObject(pEscort):destroyObjectFromWorld()
end

function Escort:taskStart(pCreatureObject, pEscort)
	local playerID = SceneObject(pCreatureObject):getObjectID()
	local escortID = SceneObject(pEscort):getObjectID()

	local pActiveArea = self:setupActiveArea(pCreatureObject, self.returnPoint, self.returnPlanet, self.areaRadius)
	if pActiveArea ~= nil then
		local waypointId = ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
			return playerObject:addWaypoint(self.returnPlanet, self.waypointDescription, "", self.returnPoint.x, self.returnPoint.y, WAYPOINTORANGE, true, true, 0)
		end)

		if waypointId ~= nil then
			writeData(playerID .. self.taskName .. "waypointID", waypointId)
			AiAgent(pEscort):setAiTemplate("follow")
			AiAgent(pEscort):setFollowObject(pCreatureObject)

			writeData(playerID .. self.taskName .. "escortID", escortID)
			writeData(SceneObject(pActiveArea):getObjectID() .. self.taskName .. "escortID", escortID)
			writeData(escortID .. self.taskName .. "ownerID", playerID)
			writeData(playerID .. ":escortInProgress", 1)

			self:callFunctionIfNotNil(self.onSuccessfulSpawn, nil, pCreatureObject, pEscort)
			return true
		end
	end

	Logger:log("Failed to start " .. self.taskName .. " escort.", LT_ERROR)
	self:finish(pCreatureObject)

	return false
end

function Escort:taskFinish(pCreatureObject)
	local playerID = SceneObject(pCreatureObject):getObjectID()
	local waypointId = readData(playerID .. self.taskName .. "waypointID")

	ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		playerObject:removeWaypoint(waypointId, true)
	end)

	local areaID = readData(playerID .. self.taskName .. "areaID")
	local pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	local escortID = readData(playerID .. self.taskName .. "escortID")
	local pEscort = getSceneObject(escortID)

	if (pEscort ~= nil) then
		AiAgent(pEscort):setFollowObject(nil)
		createEvent(self.escortDespawnTime, self.taskName, "handleEscortDespawn", pEscort)
	end

	deleteData(playerID .. ":escortInProgress")
	self:callFunctionIfNotNil(self.onFinish, nil, pCreatureObject)

	return true
end

return Escort
