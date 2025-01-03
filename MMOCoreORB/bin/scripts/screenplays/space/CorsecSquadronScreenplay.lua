local Logger = require("utils.logger")

CorsecSquadronScreenplay = ScreenPlay:new {
	className = "CorsecSquadronScreenplay",

	-- Quest Steps
	ACCEPTED_MISSION_1 = 1, -- corellia_privateer_1 -- Task 1 - Player needs to enter Corellia Space
	PATROLLING_1 = 2, -- corellia_privateer_1 -- Task 2 - Player is in Space Corellia and given first patrol waypoint
	PATROLLING_2 = 3,
	PATROLLING_3 = 4,
	FINISHED_MISSION_1 = 5,

	-- Patrol Points
	patrolPoints = {
		{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, questStep = 2, radius = 250},
		{zoneName = "space_corellia", x = -4540, z = -6023, y = -6111, questStep = 3, radius = 250},
		{zoneName = "space_corellia", x = -2907, z = -4914, y = -5085, questStep = 4, radius = 250},
	},
}

registerScreenPlay("CorsecSquadronScreenplay", true)

function CorsecSquadronScreenplay:start()
	self:spawnActiveAreas()
end

function CorsecSquadronScreenplay:spawnActiveAreas()
	local areasTable = self.patrolPoints
	local totalAreas = #areasTable

	if (totalAreas < 1) then
		return
	end

	for i = 1, totalAreas, 1 do
		local zoneName = areasTable[i].zoneName
		local x = areasTable[i].x
		local z = areasTable[i].z
		local y = areasTable[i].y
		local questStep = areasTable[i].questStep

		if (not isZoneEnabled(zoneName)) then
			goto skip
		end

		local pQuestArea = spawnSpaceActiveArea(zoneName, "object/space_active_area.iff", x, z, y, areasTable[i].radius)

		if pQuestArea == nil then
			Logger:log("CorsecSquadronScreenplay: pQuestArea is nil.", LT_ERROR)
			return
		end

		local questAreaID = SceneObject(pQuestArea):getObjectID()

		writeData(questAreaID .. ":QuestStep", questStep)

		createObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pQuestArea)

		::skip::
	end
end

--[[

		Observers

--]]

function CorsecSquadronScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
	if (pPlayer == nil) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local currentStep = getQuestStatus(playerID .. ":CorsecSquadron")
	local spaceCorelliaHash = getHashCode("space_corellia")

	if (currentStep == nil) then
		currentStep = 0
	else
		currentStep = tonumber(currentStep)
	end

	--print("CorsecSquadronScreenplay:enteredZone called -- Current Quest Step: " .. currentStep .. " Zone Hash: " .. zoneNameHash .. " space_corellia: " .. spaceCorelliaHash)

	-- First Quest - Patrol
	if (currentStep >= self.ACCEPTED_MISSION_1 or currentStep < self.FINISHED_MISSION_1) then
		-- Player is in the correct zone
		if (currentStep == self.ACCEPTED_MISSION_1 and zoneNameHash == spaceCorelliaHash) then
			-- Complete the quest task 1
			SpaceHelpers:completeSpaceQuestTask(pPlayer, "patrol", "corellia_privateer_1", 0, true)

			-- Activate quest task 2
			SpaceHelpers:activateSpaceQuestTask(pPlayer, "patrol", "corellia_privateer_1", 2, true)

			-- Update the players quest status
			setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_1)

			-- Add patrol point to the player
			local point1 = self.patrolPoints[1]
			local waypointID = PlayerObject(pGhost):addWaypoint(point1.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", point1.x, point1.z, point1.y, WAYPOINTBLUE, true, true, 0, 1)

			setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)

			return 0
		-- Player went to wrong zone, fail mission
		else
			-- Set Quest failed
			SpaceHelpers:failSpaceQuest(pPlayer, "patrol", "corellia_privateer_1", true)

			-- Remove players quest status
			removeQuestStatus(playerID .. ":CorsecSquadron")

			return 1
		end
	end

	return 1
end

function CorsecSquadronScreenplay:notifyEnteredQuestArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil) or (not SceneObject(pShip):isPlayerShip())) then
		return 0
	end

	--print("notifyEnteredQuestArea - Ship: " .. SceneObject(pShip):getDisplayedName() .. " entered SpaceActiveArea - X: " .. SceneObject(pActiveArea):getPositionX() .. " Z: " .. SceneObject(pActiveArea):getPositionZ() .. " Y: " .. SceneObject(pActiveArea):getPositionY() .. " Object Position - X: " .. SceneObject(pShip):getPositionX() .. " Z: " .. SceneObject(pShip):getPositionZ() .. " Y: " .. SceneObject(pShip):getPositionY())

	local pPilot = LuaShipObject(pShip):getPilot()

	if (pPilot == nil or not SceneObject(pPilot):isPlayerCreature()) then
		return 0
	end

	local pGhost = CreatureObject(pPilot):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local playerID = SceneObject(pPilot):getObjectID()
	local waypointID = tonumber(getQuestStatus(playerID .. ":CorsecSquadron:waypointID"))
	local currentStep = tonumber(getQuestStatus(playerID .. ":CorsecSquadron"))

	--print("Player Pilot: " .. SceneObject(pPilot):getDisplayedName() .. " Current Quest Step: " .. currentStep .. " WaypointID: " .. waypointID)

	-- Clear the waypointID and waypoint off the player
	removeQuestStatus(playerID .. ":CorsecSquadron:waypointID")
	PlayerObject(pGhost):removeWaypoint(waypointID, true)

	-- 1st Patrol point
	if (currentStep == self.PATROLLING_1) then
		-- Update the players quest status
		setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_2)

		-- Add patrol point to the player
		local point2 = self.patrolPoints[2]
		local waypointID = PlayerObject(pGhost):addWaypoint(point2.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", point2.x, point2.z, point2.y, WAYPOINTBLUE, true, true, 0, 1)

		setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)
	-- 2nd Patrol Point
	elseif (currentStep == self.PATROLLING_2) then
		-- Update the players quest status
		setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_3)

		-- Add patrol point to the player
		local point3 = self.patrolPoints[3]
		local waypointID = PlayerObject(pGhost):addWaypoint(point3.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", point3.x, point3.z, point3.y, WAYPOINTBLUE, true, true, 0, 1)

		setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)
	-- 3rd/Final Patrol Point
	elseif (currentStep == self.PATROLLING_3) then
		-- Complete the quest task 2
		SpaceHelpers:completeSpaceQuestTask(pPilot, "patrol", "corellia_privateer_1", 2, false)

		-- Complete Journal Quest
		SpaceHelpers:completeSpaceQuest(pPilot, "patrol", "corellia_privateer_1", true)

		-- Update the players quest status
		setQuestStatus(playerID .. ":CorsecSquadron", self.FINISHED_MISSION_1)

		-- Remove the zone entry observer
		dropObserver(ZONESWITCHED, "CorsecSquadronScreenplay", "enteredZone", pPilot)
	end

	return 0
end