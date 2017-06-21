local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local Logger = require("utils.logger")

Patrol = Task:new {
	-- Task properties
	taskName = "",
	-- Patrol properties
	waypointName = "",
	numPoints = 0,
	areaSize = 0,
	originX = 0,
	originY = 0,
	forceSpawn = false,
	
	onPlayerKilled = nil,
	onEnteredActiveArea = nil
}

function Patrol:setupPatrolPoints(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local radius = 1024 -- Default radius
	local curQuest = QuestManager.getCurrentQuestID(pPlayer)
	local pQuest = getQuestInfo(curQuest)

	if (pQuest ~= nil) then
		local questRadius = LuaQuestInfo(pQuest):getQuestParameter()
		if (questRadius ~= "" and questRadius ~= nil) then
			radius = tonumber(questRadius)
		end
	end

	for i = 1, self.numPoints, 1 do
		local offsetX = getRandomNumber(-75, 75)
		local offsetY = getRandomNumber(-75, 75)
		local offsetTheta = getRandomNumber(-2, 2)
		local theta = (i * 45 + offsetTheta) * 0.0175;

		local x = (self.originX + offsetX) + (radius * math.cos(theta))
		local y = (self.originY + offsetY) + (radius * math.sin(theta))

		local planetName = SceneObject(pPlayer):getZoneName()
		local spawnPoint = getSpawnPoint(planetName, x, y, 0, 200, self.forceSpawn)

		local pActiveArea = spawnActiveArea(planetName, "object/active_area.iff", spawnPoint[1], spawnPoint[2], spawnPoint[3], self.areaSize, 0)

		if (pActiveArea == nil) then
			return nil
		end

		local areaID = SceneObject(pActiveArea):getObjectID()

		writeData(areaID .. self.taskName .. "ownerID", playerID)
		writeData(areaID .. self.taskName .. "waypointNum", i)
		writeData(playerID .. self.taskName .. "waypointNum" .. i, areaID)
		createObserver(ENTEREDAREA, self.taskName, "handleEnteredAreaEvent", pActiveArea)
		
		local pGhost = CreatureObject(pPlayer):getPlayerObject()
		
		if (pGhost ~= nil) then
			local waypointID = PlayerObject(pGhost):addWaypoint(planetName, self.waypointName, "", spawnPoint[1], spawnPoint[3], WAYPOINTYELLOW, true, true, 0, 0)
			writeData(areaID .. self.taskName .. "waypointID", waypointID)
		end
	end
end

function Patrol:handleEnteredAreaEvent(pActiveArea, pPlayer)
	if pActiveArea == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local areaID = SceneObject(pActiveArea):getObjectID()
	local ownerID = readData(areaID .. self.taskName .. "ownerID")
	if ownerID == SceneObject(pPlayer):getObjectID() then
		local wpNum = readData(areaID .. self.taskName .. "waypointNum")
		self:destroyWaypoint(pPlayer, wpNum)
		local wpDone = readData(ownerID .. ":patrolWaypointsReached") + 1

		writeData(ownerID .. ":patrolWaypointsReached", wpDone)
		self:onEnteredActiveArea(pPlayer, pActiveArea)
		SceneObject(pActiveArea):destroyObjectFromWorld()
		return 1
	end

	return 0
end

function Patrol:destroyWaypoint(pPlayer, num)
	local playerID = SceneObject(pPlayer):getObjectID()
	local areaID = readData(playerID .. self.taskName .. "waypointNum" .. num)

	local waypointNum = readData(areaID .. self.taskName .. "waypointNum")
	local waypointID = readData(areaID .. self.taskName .. "waypointID")

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	
	if (pGhost ~= nil) then
		PlayerObject(pGhost):removeWaypoint(waypointID, true)
	end

	local pActiveArea = getSceneObject(areaID)

	if (pActiveArea ~= nil) then
		SceneObject(pActiveArea):destroyObjectFromWorld()
	end

	deleteData(playerID .. self.taskName .. "waypointNum" .. waypointNum)
	deleteData(areaID .. self.taskName .. "waypointID")
	deleteData(areaID .. self.taskName .. "waypointNum")
	deleteData(areaID .. self.taskName .. "ownerID")
end

function Patrol:waypointCleanup(pPlayer)
	for i = 1, self.numPoints, 1 do
		self:destroyWaypoint(pPlayer, i)
	end
end

function Patrol:failPatrol(pPlayer)
	self:waypointCleanup(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	
	deleteData(playerID .. ":completedCurrentPoint")
	deleteData(playerID .. ":patrolWaypointsReached")
	writeData(playerID .. ":failedPatrol", 1)
	return true
end

function Patrol:taskStart(pPlayer)
	self:setupPatrolPoints(pPlayer)
	createObserver(OBJECTDESTRUCTION, self.taskName, "playerKilled", pPlayer)
	
	return true
end

function Patrol:playerKilled(pPlayer, pKiller, nothing)
	if (pPlayer == nil) then
		return 0
	end

	self:callFunctionIfNotNil(self.onPlayerKilled, false, pPlayer)

	return 0
end

function Patrol:taskFinish(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	deleteData(playerID .. ":patrolWaypointsReached")
	deleteData(playerID .. ":completedCurrentPoint")
	deleteData(playerID .. ":failedPatrol")
	dropObserver(OBJECTDESTRUCTION, self.taskName, "playerKilled", pPlayer)
	self:waypointCleanup(pPlayer)
	return true
end

return Patrol
