SpacePatrolScreenplay = SpaceQuestLogic:new {
	className = "SpacePatrolScreenplay",

	DEBUG_SPACE_PATROL = false,

	patrolPoints = {},
}

registerScreenPlay("SpacePatrolScreenplay", false)

--[[

		Space Patrol Quest Functions

--]]

function SpacePatrolScreenplay:start()
	self:spawnActiveAreas()
end

-- Setup quest for player
function SpacePatrolScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
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

	-- Make sure they do not have old patrol progress stored
	deleteData(SceneObject(pPlayer):getObjectID() .. ":" .. self.className)
end

function SpacePatrolScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_PATROL) then
		print(self.className .. ":completeQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	-- Complete the Journal Quest
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)
end

function SpacePatrolScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_PATROL) then
		print(self.className .. ":failQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	-- Clear Patrol progress
	deleteData(SceneObject(pPlayer):getObjectID() .. ":" .. self.className)

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end
end

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
			Logger:log(self.className .. ":spawnActiveAreas -- pQuestArea is nil.", LT_ERROR)
			return
		end

		local questAreaID = SceneObject(pQuestArea):getObjectID()

		-- Write the patrol point number so the player goes in order
		writeData(questAreaID .. ":" .. self.className, patrolNumber)

		-- Add Entry Observer for ships
		createObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pQuestArea)

		if (self.DEBUG_SPACE_PATROL) then
			print(self.className .. ":spawnActiveAreas - Area Spawned ID: " .. questAreaID .. " Observer: " .. self.className .. ":notifyEnteredQuestArea Patrol Number: " .. patrolNumber)
		end

		::skip::
	end
end

function SpacePatrolScreenplay:alertPatrolPoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	SpaceHelpers:sendQuestUpdate(pPlayer, "@space/quest:patrol_new_waypoint") -- "Patrol waypoint located."

	-- Player effect for player
	CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_waypoint_patrol.cef", "")
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
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 2
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 2, false)

		-- Add patrol point to the player
		local patrolPoint = self.patrolPoints[1]
		local waypointID = PlayerObject(pGhost):addWaypoint(patrolPoint.zoneName, "@spacequest/patrol/" .. self.questName .. ":quest_patrol_t", "", patrolPoint.x, patrolPoint.z, patrolPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

		local pWaypoint = getSceneObject(waypointID)

		if (pWaypoint ~= nil) then
			WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
		end

		-- Store the waypointID on the player
		setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

		createEvent(4000, self.className, "alertPatrolPoint", pPlayer, "")

		return 0
	else
		createEvent(2000, self.className, "failQuest", pPlayer, "true")
		return 1
	end

	return 0
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

	-- Player is not actively on this quest
	if (not SpaceHelpers:isSpaceQuestActive(pPilot, self.questType, self.questName)) then
		return 0
	end

	local pGhost = CreatureObject(pPilot):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local playerID = SceneObject(pPilot):getObjectID()
	local playerPointCount = readData(playerID .. ":" .. self.className)
	local pointNumber = readData(SceneObject(pActiveArea):getObjectID() .. ":" .. self.className)

	if (self.DEBUG_SPACE_PATROL) then
		print(self.className .. ":notifyEnteredQuestArea - Patrol Point Number: " ..  pointNumber .. " Player Point: " .. playerPointCount)
	end

	-- Check to ensure player is arriving at the points in order
	if ((pointNumber - 1) ~= playerPointCount) then
		return 0
	end

	-- Send player arrival message
	SpaceHelpers:sendQuestUpdate(pPilot, "@space/quest:patrol_waypoint_arrived") -- "You have arrived at a patrol nav point."

	-- Remove the old waypoint from player
	SpaceHelpers:clearQuestWaypoint(pPilot, self.className)

	-- Check to see if its the final patrol point
	if (pointNumber == #self.patrolPoints) then
		deleteData(playerID .. ":" .. self.className)
		return 0
	-- Arrived at first waypoint, send them the initial progress message
	elseif (playerPointCount == 0) then
		SpaceHelpers:sendQuestProgess(pPilot, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":title")
	end

	-- Update players point count
	writeData(playerID .. ":" .. self.className, pointNumber)

	-- Add next patrol point to the player
	local patrolPoint = self.patrolPoints[pointNumber + 1]
	local waypointID = PlayerObject(pGhost):addWaypoint(patrolPoint.zoneName, "@spacequest/patrol/" .. self.questName .. ":quest_patrol_t", "", patrolPoint.x, patrolPoint.z, patrolPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	if (waypointID <= 0) then
		return 0
	end

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")

		-- Send Message for new patrol Point
		createEvent(100, self.className, "alertPatrolPoint", pPilot, "")
	end

	-- Store the waypointID on the player
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	-- Check for side quest
	if (self.sideQuest and (self.sideQuestStart == pointNumber)) then
		local alertMessage = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":split_quest_alert"

		-- Trigger Completion of this quest
		createEvent((self.sideQuestDelay * 1000) - 500, self.className, "completeQuest", pPilot, "false")

		-- Split Quest Alert
		createEvent((self.sideQuestDelay * 1000) - 500, "SpaceHelpers", "sendQuestAlert", pPilot, alertMessage)

		-- Trigger Sidequest
		createEvent(self.sideQuestDelay * 1000, self.sideQuestType .. "_" .. self.questName, "startQuest", pPilot, "")

		-- Trigger Removal of patrol Point
		createEvent(self.sideQuestDelay * 1000, "SpaceHelpers", "clearQuestWaypoint", pPilot, self.className)
	end

	return 0
end
