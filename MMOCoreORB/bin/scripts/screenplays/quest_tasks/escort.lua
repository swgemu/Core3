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

function Escort:setupActiveArea(pPlayer, spawnPoint, spawnPlanet, spawnRadius)
	local pActiveArea = spawnActiveArea(spawnPlanet, "object/active_area.iff", spawnPoint.x, 0, spawnPoint.y, spawnRadius, 0)

	if (pActiveArea ~= nil) then
		writeData(SceneObject(pPlayer):getObjectID() .. self.taskName .. "areaID", SceneObject(pActiveArea):getObjectID())
		createObserver(ENTEREDAREA, self.taskName, "handleEnteredAreaEvent", pActiveArea)
	end

	return pActiveArea
end

function Escort:handleEnteredAreaEvent(pActiveArea, pCreature)
	if not SceneObject(pCreature):isCreatureObject() then
		return 0
	end

	local creatureID = SceneObject(pCreature):getObjectID()
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

function Escort:taskStart(pPlayer, pEscort)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		Logger:log("Failed to start " .. self.taskName .. " escort.", LT_ERROR)
		return false
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local escortID = SceneObject(pEscort):getObjectID()

	local pActiveArea = self:setupActiveArea(pPlayer, self.returnPoint, self.returnPlanet, self.areaRadius)
	if pActiveArea ~= nil then
		local waypointId = PlayerObject(pGhost):addWaypoint(self.returnPlanet, self.waypointDescription, "", self.returnPoint.x, self.returnPoint.y, WAYPOINTORANGE, true, true, WAYPOINTQUESTTASK)

		if waypointId ~= nil then
			writeData(playerID .. ":escortInProgress", 1)

			self:setEscortFollow(pPlayer, pEscort)
			writeData(SceneObject(pActiveArea):getObjectID() .. self.taskName .. "escortID", escortID)
			self:callFunctionIfNotNil(self.onSuccessfulSpawn, nil, pPlayer, pEscort)
			return true
		end
	end

	Logger:log("Failed to start " .. self.taskName .. " escort.", LT_ERROR)
	self:finish(pPlayer)

	return false
end

function Escort:setEscortFollow(pPlayer, pEscort)
	local playerID = SceneObject(pPlayer):getObjectID()
	local escortID = SceneObject(pEscort):getObjectID()

	AiAgent(pEscort):setAiTemplate("escort")
	AiAgent(pEscort):setFollowObject(pPlayer)

	writeData(playerID .. self.taskName .. "escortID", escortID)
	writeData(escortID .. self.taskName .. "ownerID", playerID)
end

function Escort:taskFinish(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)

	local areaID = readData(playerID .. self.taskName .. "areaID")
	local pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	local escortID = readData(playerID .. self.taskName .. "escortID")
	local pEscort = getSceneObject(escortID)

	if (pEscort ~= nil) then
		AiAgent(pEscort):setFollowObject(nil)
		createEvent(self.escortDespawnTime, self.taskName, "handleEscortDespawn", pEscort, "")
	end

	deleteData(playerID .. ":escortInProgress")
	self:callFunctionIfNotNil(self.onFinish, nil, pPlayer)

	return true
end

return Escort
