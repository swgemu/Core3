local ObjectManager = require("managers.object.object_manager")

SpacePatrolScreenplay = SpaceQuestLogic:new {
	className = "SpacePatrolScreenplay",

	DEBUG_SPACE_PATROL = true, -- Set false before merge

	patrolPoints = {},
}

registerScreenPlay("SpacePatrolScreenplay", false)

function SpacePatrolScreenplay:start()
	self:spawnActiveAreas()
end

-- Setup quest for player
function SpacePatrolScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_PATROL) then
		print(self.className .. ":startQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Activate the Journal Quest
	SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, self.questType, self.questName, 1)

	-- Create inital observer for player entering Corellia Space
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

--[[

		Observers

--]]

function SpacePatrolScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
	if (pPlayer == nil) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return 0
	end

	local pRootParent = SceneObject(pPlayer):getRootParent()

	if (pRootParent ~= nil and SceneObject(pRootParent):getObjectName() == "player_sorosuub_space_yacht") then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local spaceQuestHash = getHashCode(self.questZone)

	if (self.DEBUG_SPACE_PATROL) then
		print(self.className .. ":enteredZone called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Player Zone Hash: " .. zoneNameHash .. " questZone hash: " .. spaceQuestHash)
	end

	-- Player is in the correct zone
	if (zoneNameHash == spaceQuestHash and not SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		-- Complete the quest task 1
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, 0)

		-- Activate quest task 2
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 2, 1)

		-- Add patrol point to the player
		local patrolPoint = self.patrolPoints.corellia_privateer_1[1]
		local waypointID = PlayerObject(pGhost):addWaypoint(patrolPoint.zoneName, "@spacequest/patrol/" .. self.questName .. ":quest_patrol_t", "", patrolPoint.x, patrolPoint.z, patrolPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

		local pWaypoint = getSceneObject(waypointID)

		if (pWaypoint ~= nil) then
			WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
		end

		setQuestStatus(playerID .. ":" .. self.className, waypointID)

		-- Send player system message
		CreatureObject(pPlayer):sendSystemMessage("@space/quest:patrol_new_waypoint") -- "Patrol waypoint located."

		return 0
	else
		-- Set Quest failed
		SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, 1)

		-- Remove any patrol points
		self:clearQuestWaypoint(pPlayer)
	end

	return 1
end

function SpacePatrolScreenplay:notifyEnteredQuestArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil) or (not SceneObject(pShip):isPlayerShip())) then
		return 0
	end

	if (self.DEBUG_SPACE_PATROL) then
		print(self.className .. ":notifyEnteredQuestArea - Ship: " .. SceneObject(pShip):getDisplayedName() .. " entered SpaceActiveArea - X: " .. SceneObject(pActiveArea):getPositionX() .. " Z: " .. SceneObject(pActiveArea):getPositionZ() .. " Y: " .. SceneObject(pActiveArea):getPositionY() .. " Object Position - X: " .. SceneObject(pShip):getPositionX() .. " Z: " .. SceneObject(pShip):getPositionZ() .. " Y: " .. SceneObject(pShip):getPositionY())
	end

	local pPilot = LuaShipObject(pShip):getPilot()

	if (pPilot == nil or not SceneObject(pPilot):isPlayerCreature()) then
		return 0
	end

	local pGhost = CreatureObject(pPilot):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local playerID = SceneObject(pPilot):getObjectID()
	local playerPointCount = readData(playerID .. ":" .. self.className)
	local pointNumber = readData(SceneObject(pActiveArea):getObjectID() .. ":" .. self.className)

	-- Check to ensure player is arriving at the points in order
	if ((pointNumber - 1) ~= playerPointCount) then
		return 0
	end

	-- Send player arrival message
	CreatureObject(pPilot):sendSystemMessage("@space/quest:patrol_waypoint_arrived") -- "You have arrived at a patrol nav point."

	-- Remove the old waypoint from player
	self:clearQuestWaypoint(pPlayer)

	-- Check to see if its the final patrol point
	if (pointNumber == #self.patrolPoints) then
		deleteData(playerID .. ":" .. self.className)
		return 0
	end

	-- Update players point count
	writeData(playerID .. ":" .. self.className, pointNumber)

	-- Add next patrol point to the player
	local patrolPoint = self.patrolPoints[pointNumber + 1]
	local waypointID = PlayerObject(pGhost):addWaypoint(patrolPoint.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", patrolPoint.x, patrolPoint.z, patrolPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	if (waypointID <= 0) then
		return 0
	end

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
	end

	-- Store new patrol point on player
	setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)

	-- Send Message for new patrol Point
	CreatureObject(pPilot):sendSystemMessage("@space/quest:patrol_new_waypoint") -- "Patrol waypoint located."

	return 0
end

--[[

		Functions

--]]

function SpacePatrolScreenplay:spawnActiveAreas()
	local areasTable = self.patrolPoints

	for i = 1, #areasTable, 1 do
		local zoneName = areasTable[i].zoneName
		local x = areasTable[i].x
		local z = areasTable[i].z
		local y = areasTable[i].y
		local patrolNumber = areasTable[i].patrolNumber

		if (not isZoneEnabled(zoneName)) then
			goto skip
		end

		local pQuestArea = spawnSpaceActiveArea(zoneName, "object/space_active_area.iff", x, z, y, areasTable[i].radius)

		if pQuestArea == nil then
			Logger:log("CorsecSquadronScreenplay: pQuestArea is nil.", LT_ERROR)
			return
		end

		local questAreaID = SceneObject(pQuestArea):getObjectID()

		-- Write the quest step to the quest area
		writeData(questAreaID .. ":" .. self.className, patrolNumber)

		-- Add Entry Observer for ships
		createObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pQuestArea)

		if (self.DEBUG_SPACE_PATROL) then
			print(self.className .. ":spawnActiveAreas - Area Spawned ID: " .. questAreaID .. " Observer: " .. self.className .. ":notifyEnteredQuestArea Patrol Number: " .. patrolNumber)
		end

		::skip::
	end
end

function SpacePatrolScreenplay:clearQuestWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local waypointID = tonumber(getQuestStatus(playerID .. ":" .. self.className))

	-- Clear the waypointID and waypoint off the player
	removeQuestStatus(playerID .. ":" .. self.className)

	-- Clear the waypoint from the player object
	PlayerObject(pGhost):removeWaypoint(waypointID, true)
end