local Task = require("quest.tasks.task")
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

function Patrol:setupPatrolPoints(pCreature)
	local playerID = SceneObject(pCreature):getObjectID()
	local radius = 1024 -- Default radius
	local curQuest = QuestManager.getCurrentQuestID(pCreature)
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

		local spawnPoint = getSpawnPoint(pCreature, x, y, 0, 200, self.forceSpawn)
		local planetName = SceneObject(pCreature):getZoneName()

		local pActiveArea = spawnActiveArea(planetName, "object/active_area.iff", spawnPoint[1], spawnPoint[2], spawnPoint[3], self.areaSize, 0)

		if (pActiveArea == nil) then
			return nil
		end

		local areaID = SceneObject(pActiveArea):getObjectID()

		writeData(areaID .. self.taskName .. "ownerID", playerID)
		writeData(areaID .. self.taskName .. "waypointNum", i)
		writeData(playerID .. self.taskName .. "waypointNum" .. i, areaID)
		createObserver(ENTEREDAREA, self.taskName, "handleEnteredAreaEvent", pActiveArea)
		ObjectManager.withCreaturePlayerObject(pCreature, function(ghost)
			local waypointID = ghost:addWaypoint(planetName, self.waypointName, "", spawnPoint[1], spawnPoint[3], WAYPOINTYELLOW, true, true, 0, 0)
			writeData(areaID .. self.taskName .. "waypointID", waypointID)
		end)
	end
end

function Patrol:handleEnteredAreaEvent(pActiveArea, pCreature)
	if pActiveArea == nil or not SceneObject(pCreature):isPlayerCreature() then
		return 0
	end

	local areaID = SceneObject(pActiveArea):getObjectID()
	local ownerID = readData(areaID .. self.taskName .. "ownerID")
	if ownerID == SceneObject(pCreature):getObjectID() then
		local wpNum = readData(areaID .. self.taskName .. "waypointNum")
		self:destroyWaypoint(pCreature, wpNum)
		local wpDone = readData(ownerID .. ":patrolWaypointsReached") + 1

		writeData(ownerID .. ":patrolWaypointsReached", wpDone)
		self:onEnteredActiveArea(pCreature, pActiveArea)
		SceneObject(pActiveArea):destroyObjectFromWorld()
		return 1
	end

	return 0
end

function Patrol:destroyWaypoint(pCreature, num)
	local playerID = SceneObject(pCreature):getObjectID()
	local areaID = readData(playerID .. self.taskName .. "waypointNum" .. num)

	local waypointNum = readData(areaID .. self.taskName .. "waypointNum")
	local waypointID = readData(areaID .. self.taskName .. "waypointID")

	ObjectManager.withCreaturePlayerObject(pCreature, function(ghost)
		ghost:removeWaypoint(waypointID, true)
	end)

	local pActiveArea = getSceneObject(areaID)

	if (pActiveArea ~= nil) then
		SceneObject(pActiveArea):destroyObjectFromWorld()
	end

	deleteData(playerID .. self.taskName .. "waypointNum" .. waypointNum)
	deleteData(areaID .. self.taskName .. "waypointID")
	deleteData(areaID .. self.taskName .. "waypointNum")
	deleteData(areaID .. self.taskName .. "ownerID")
end

function Patrol:waypointCleanup(pCreature)
	for i = 1, self.numPoints, 1 do
		self:destroyWaypoint(pCreature, i)
	end
end

function Patrol:failPatrol(pCreature)
	self:waypointCleanup(pCreature)
	local playerID = SceneObject(pCreature):getObjectID()
	
	deleteData(playerID .. ":patrolWaypointsReached")
	writeData(playerID .. ":failedPatrol", 1)
	return true
end

function Patrol:taskStart(pCreature)
	self:setupPatrolPoints(pCreature)
	createObserver(OBJECTDESTRUCTION, self.taskName, "playerKilled", pCreature)
end

function Patrol:playerKilled(pCreature, pKiller, nothing)
	if (pCreature == nil) then
		return 0
	end

	self:callFunctionIfNotNil(self.onPlayerKilled, false, pCreature)

	return 0
end

function Patrol:taskFinish(pCreature)
	local playerID = SceneObject(pCreature):getObjectID()
	deleteData(playerID .. ":patrolWaypointsReached")
	deleteData(playerID .. ":failedPatrol")
	self:waypointCleanup(pCreature)
	return true
end

return Patrol
