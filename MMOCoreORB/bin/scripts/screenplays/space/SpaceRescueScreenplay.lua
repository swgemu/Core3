SpaceRescueScreenplay = SpaceQuestLogic:new {
	className = "SpaceRescueScreenplay",

	questName = "",
	questType = "rescue",

	questZone = "",

	creditReward = 0,
	itemReward = {
		--{species = {}, item = ""},
	},

	sideQuest = false,
	sideQuestType = "",
	sideQuestName = "",

	DEBUG_SPACE_RESCUE = false,

	-- Rescue mission specific variables
	arrivalDelay = 5, -- In Seconds before spawning rescue target

	rescueShip = "", -- Ship template to spawn as rescue target
	rescueLocation = {x = 0, z = 0, y = 0}, -- Where to spawn the rescue target

	repairDelay = 30, -- In Seconds for repairs to complete after docking

	attackDelay = 10, -- In Seconds after docking before attackers spawn (during repairs)
	attackShips = {
		-- {{count = 2, shipName = "enemy_ship_tier3"}},
	},

	-- Escort points after repair - route to safety/hyperspace
	escortPoints = {
		--{patrolPointName = "", zoneName = "", x = 0, z = 0, y = 0, escortNumber = 1, radius = 250},
	},

	escortSpeed = 20,

	-- Attackers during escort phase (e.g., single named ship)
	escortAttackDelay = 10, -- In Seconds after escort starts before attackers spawn
	escortAttackShips = {
		-- {{count = 1, shipName = "aynat_vaporizer_tier3"}},
	},

	tauntData = {
		panicCount = 5,
		thanksCount = 5,
	},
}

registerScreenPlay("SpaceRescueScreenplay", false)

--[[

		Space Rescue Quest Functions

--]]

function SpaceRescueScreenplay:start()
end

function SpaceRescueScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":startQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	if (pNpc == "") then
		pNpc = nil
	end

	-- Activate the Journal Quest
	SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, self.questType, self.questName, false)

	local spaceQuestHash = getHashCode(self.questZone)
	local zoneName = SceneObject(pPlayer):getZoneName()
	local playerZoneHash = getHashCode(zoneName)

	-- Check if the player is in the proper zone already
	if (playerZoneHash == spaceQuestHash and not SpaceHelpers:isInYacht(pPlayer)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, true)

		-- Setup the rescue mission
		createEvent(self.arrivalDelay * 1000, self.className, "setupRescue", pPlayer, "")
	end

	-- Create initial observer for player entering Zone
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

function SpaceRescueScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":completeQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Remove waypoint
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Send completion message
	SpaceHelpers:sendQuestUpdate(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":complete")

	-- Complete the Journal Quest
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	-- Remove dock observer
	dropObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)

	self:cleanUpQuestData(playerID)

	if (self.sideQuest and (self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.COMPLETION or self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.BIDIRECTIONAL)) then
		local alertMessage = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":split_quest_alert"

		-- Split Quest Alert
		createEvent(self.sideQuestDelay * 1000, "SpaceHelpers", "sendQuestAlert", pPlayer, alertMessage)

		-- Trigger Sidequest
		createEvent(self.sideQuestDelay * 1050, self.sideQuestType .. "_" .. self.sideQuestName, "startQuest", pPlayer, "")
	end
end

function SpaceRescueScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":failQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Send failure message
	SpaceHelpers:sendQuestUpdate(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":failed_destroy")

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	-- Remove dock observer
	dropObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)

	self:cleanUpQuestData(playerID)

	-- Fail the parent quest
	if (self.parentQuestType ~= nil and self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.parentQuestName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.sideQuestName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.sideQuestName, "failQuest", pPlayer, "false")
	end

	if (self.sideQuest and (self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.FAILURE or self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.BIDIRECTIONAL)) then
		local alertMessage = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":split_quest_alert_fail"

		-- Split Quest Alert
		createEvent(self.sideQuestDelay * 1000, "SpaceHelpers", "sendQuestAlert", pPlayer, alertMessage)

		-- Trigger Sidequest
		createEvent(self.sideQuestDelay * 1050, self.sideFailQuestType .. "_" .. self.sideFailQuestName, "startQuest", pPlayer, "")
	end
end

function SpaceRescueScreenplay:resetQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to resetQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":resetQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, false)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	-- Remove dock observer
	dropObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)

	self:cleanUpQuestData(SceneObject(pPlayer):getObjectID())
end

function SpaceRescueScreenplay:cleanUpQuestData(playerID)
	-- Clean up stored data
	deleteData(playerID .. ":" .. self.className .. ":waypointID")
	deleteData(playerID .. ":" .. self.className .. ":rescueShipID")
	deleteData(playerID .. ":" .. self.className .. ":escortPointIndex")
	deleteData(playerID .. ":" .. self.className .. ":repairsComplete")
end

--[[

		Space Rescue Observers

--]]

function SpaceRescueScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
	if (pPlayer == nil) then
		return 0
	end

	if (not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return 1
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	-- Skip if in yacht
	if (SpaceHelpers:isInYacht(pPlayer)) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local spaceQuestHash = getHashCode(self.questZone)

	if (zoneNameHash == spaceQuestHash) then
		-- Player entered the quest zone
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, true)

		-- Setup the rescue mission
		createEvent(self.arrivalDelay * 1000, self.className, "setupRescue", pPlayer, "")

		return 0
	elseif (SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		-- Player left quest zone after starting - fail mission
		createEvent(2000, self.className, "failQuest", pPlayer, "true")
		return 1
	end

	return 0
end

--[[

		Space Rescue Setup Functions

--]]

function SpaceRescueScreenplay:setupRescue(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		self:failQuest(pPlayer, "true")
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":setupRescue called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local rescueLocation = self.rescueLocation

	-- Send arrival message
	SpaceHelpers:sendQuestUpdate(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":arrival_phase_1")

	-- Create waypoint to rescue location
	local waypointID = PlayerObject(pGhost):addWaypoint(self.questZone, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":quest_location_t", "", rescueLocation.x, rescueLocation.z, rescueLocation.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	-- Store the waypointID
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	-- Spawn the rescue target ship
	self:spawnRescueShip(pPlayer)
end

function SpaceRescueScreenplay:spawnRescueShip(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":spawnRescueShip called -- Ship: " .. self.rescueShip)
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local rescueLocation = self.rescueLocation

	-- Spawn the rescue ship at the location
	local pRescueShip = spawnShipAgent(self.rescueShip, self.questZone, rescueLocation.x, rescueLocation.z, rescueLocation.y)

	if (pRescueShip == nil) then
		Logger:log(self.className .. ":spawnRescueShip -- Failed to spawn rescue ship: " .. self.rescueShip, LT_ERROR)
		self:failQuest(pPlayer, "true")
		return
	end

	-- Set up the ship
	ShipAiAgent(pRescueShip):setMissionOwner(pPlayer)

	-- Make ship stationary (damaged, not moving)
	ShipAiAgent(pRescueShip):setMinimumGuardPatrol(0)
	ShipAiAgent(pRescueShip):setMaximumGuardPatrol(50)
	ShipAiAgent(pRescueShip):setGuardPatrol()

	local rescueShipID = SceneObject(pRescueShip):getObjectID()

	-- Store the rescue ship ID
	writeData(playerID .. ":" .. self.className .. ":rescueShipID", rescueShipID)

	-- Add as mission object
	CreatureObject(pPlayer):addSpaceMissionObject(rescueShipID, true)

	-- Create observer for ship destruction
	createObserver(SHIPDESTROYED, self.className, "handleTargetDestroyed", pRescueShip)

	-- Create observer for player docking
	if (not hasObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)) then
		createObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)
	end

	-- Send message that ship is waiting
	createEvent(2000, "SpaceHelpers", "sendQuestUpdate", pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":arrival_phase_2")

	-- Activate dock task
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 2, true)
end

--[[

		Space Rescue Docking and Repair Functions

--]]

function SpaceRescueScreenplay:dockedShip(pPlayer, pTargetShip, cargoHash)
	if (pPlayer == nil or pTargetShip == nil) then
		return 1
	end

	if (not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local rescueShipID = readData(playerID .. ":" .. self.className .. ":rescueShipID")
	local targetShipID = SceneObject(pTargetShip):getObjectID()

	-- Verify this is the rescue ship
	if (rescueShipID ~= targetShipID) then
		return 0
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":dockedShip called -- Player docked with rescue target")
	end

	-- Send docking started message
	SpaceHelpers:sendQuestUpdate(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":docking_started")

	-- Play docking music
	CreatureObject(pPlayer):playMusicMessage("sound/mus_quest_theme_docking.snd")

	-- Complete dock task
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 2, false)

	-- Activate repair task
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 3, true)

	-- Schedule attackers to spawn
	if (#self.attackShips > 0) then
		createEvent(self.attackDelay * 1000, self.className, "spawnAttackers", pPlayer, "")
	end

	-- Schedule repairs to complete
	createEvent(self.repairDelay * 1000, self.className, "repairsComplete", pPlayer, "")

	-- Send docking complete message after short delay
	createEvent(3000, "SpaceHelpers", "sendQuestUpdate", pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":docking_complete")

	-- Remove dock observer - only dock once
	dropObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)

	return 1
end

function SpaceRescueScreenplay:spawnAttackers(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":spawnAttackers called")
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local rescueShipID = readData(playerID .. ":" .. self.className .. ":rescueShipID")
	local pRescueShip = getSceneObject(rescueShipID)

	if (pRescueShip == nil) then
		return
	end

	-- Send attack notification
	SpaceHelpers:sendQuestUpdate(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":attack_notify")

	local pPilotShip = SpaceHelpers:getPlayerShip(pPlayer)

	if (pPilotShip == nil) then
		return
	end

	local rescueLocation = self.rescueLocation
	local attackShips = self.attackShips

	for i = 1, #attackShips, 1 do
		local waveShips = attackShips[i]

		for j = 1, #waveShips, 1 do
			local shipData = waveShips[j]
			local count = shipData.count or 1
			local shipName = shipData.shipName

			for k = 1, count, 1 do
				local pAttacker = spawnShipAgent(shipName, self.questZone, rescueLocation.x + getRandomNumber(200, 400), rescueLocation.z + getRandomNumber(-100, 100), rescueLocation.y + getRandomNumber(200, 400))

				if (pAttacker ~= nil) then
					ShipAiAgent(pAttacker):setMissionOwner(pPlayer)
					ShipAiAgent(pAttacker):setMinimumGuardPatrol(100)
					ShipAiAgent(pAttacker):setMaximumGuardPatrol(500)
					ShipAiAgent(pAttacker):setGuardPatrol()

					-- Attack the rescue ship
					ShipAiAgent(pAttacker):setDefender(pRescueShip)
					ShipAiAgent(pAttacker):engageShipTarget(pRescueShip)

					local attackerID = SceneObject(pAttacker):getObjectID()
					CreatureObject(pPlayer):addSpaceMissionObject(attackerID, false)
				end
			end
		end
	end
end

function SpaceRescueScreenplay:repairsComplete(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":repairsComplete called")
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Mark repairs as complete
	writeData(playerID .. ":" .. self.className .. ":repairsComplete", 1)

	-- Send repairs complete message
	SpaceHelpers:sendQuestUpdate(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":rescue_phase_2")

	-- Complete repair task
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 3, false)

	-- Activate escort task
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 4, true)

	-- Start escort phase
	self:assignEscortPoints(pPlayer)
end

--[[

		Space Rescue Escort Functions

--]]

function SpaceRescueScreenplay:assignEscortPoints(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":assignEscortPoints called")
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local rescueShipID = readData(playerID .. ":" .. self.className .. ":rescueShipID")
	local pRescueShip = getSceneObject(rescueShipID)

	if (pRescueShip == nil) then
		self:failQuest(pPlayer, "true")
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local escortPoints = self.escortPoints

	if (#escortPoints == 0) then
		-- No escort points, complete mission immediately
		self:completeQuest(pPlayer, "true")
		return
	end

	-- Build patrol points table for the ship
	local pointsTable = {}

	for i = 1, #escortPoints, 1 do
		local point = escortPoints[i]
		pointsTable[i] = {patrolPointName = point.patrolPointName, zoneName = point.zoneName or self.questZone, x = point.x, z = point.z, y = point.y, patrolNumber = i, radius = point.radius or 250}
	end

	-- Set escort point index
	writeData(playerID .. ":" .. self.className .. ":escortPointIndex", 1)

	-- Switch ship to patrol mode and assign points
	ShipAiAgent(pRescueShip):setFixedPatrol()
	ShipAiAgent(pRescueShip):assignFixedPatrolPointsTable(pointsTable, self.escortSpeed)

	-- Create observer for reaching patrol points
	createObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pRescueShip)

	-- Clear old waypoint and create escort waypoint
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	local firstPoint = escortPoints[1]
	local waypointID = PlayerObject(pGhost):addWaypoint(self.questZone, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":quest_escort_t", "", firstPoint.x, firstPoint.z, firstPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	-- Schedule escort attackers if configured
	if (self.escortAttackShips ~= nil and #self.escortAttackShips > 0) then
		createEvent(self.escortAttackDelay * 1000, self.className, "spawnEscortAttackers", pPlayer, "")
	end
end

function SpaceRescueScreenplay:spawnEscortAttackers(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":spawnEscortAttackers called")
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local rescueShipID = readData(playerID .. ":" .. self.className .. ":rescueShipID")
	local pRescueShip = getSceneObject(rescueShipID)

	if (pRescueShip == nil) then
		return
	end

	-- Send attack notification
	SpaceHelpers:sendQuestUpdate(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":attack_notify")

	local pPilotShip = SpaceHelpers:getPlayerShip(pPlayer)

	if (pPilotShip == nil) then
		return
	end

	-- Get current position of rescue ship for spawning attackers nearby
	local shipX = SceneObject(pRescueShip):getPositionX()
	local shipZ = SceneObject(pRescueShip):getPositionZ()
	local shipY = SceneObject(pRescueShip):getPositionY()

	local escortAttackShips = self.escortAttackShips

	for i = 1, #escortAttackShips, 1 do
		local waveShips = escortAttackShips[i]

		for j = 1, #waveShips, 1 do
			local shipData = waveShips[j]
			local count = shipData.count or 1
			local shipName = shipData.shipName

			for k = 1, count, 1 do
				local pAttacker = spawnShipAgent(shipName, self.questZone, shipX + getRandomNumber(200, 400), shipZ + getRandomNumber(-100, 100), shipY + getRandomNumber(200, 400))

				if (pAttacker ~= nil) then
					ShipAiAgent(pAttacker):setMissionOwner(pPlayer)
					ShipAiAgent(pAttacker):setMinimumGuardPatrol(100)
					ShipAiAgent(pAttacker):setMaximumGuardPatrol(500)
					ShipAiAgent(pAttacker):setGuardPatrol()

					-- Attack the rescue ship
					ShipAiAgent(pAttacker):setDefender(pRescueShip)
					ShipAiAgent(pAttacker):engageShipTarget(pRescueShip)

					local attackerID = SceneObject(pAttacker):getObjectID()
					CreatureObject(pPlayer):addSpaceMissionObject(attackerID, false)
				end
			end
		end
	end
end

function SpaceRescueScreenplay:notifyEnteredQuestArea(pRescueShip, pPlayer, pointNum)
	if (pRescueShip == nil) then
		return 1
	end

	local missionOwnerID = ShipAiAgent(pRescueShip):getMissionOwnerID()
	local pOwner = getSceneObject(missionOwnerID)

	if (pOwner == nil or not SceneObject(pOwner):isPlayerCreature()) then
		return 1
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":notifyEnteredQuestArea called -- Point: " .. pointNum)
	end

	local pGhost = CreatureObject(pOwner):getPlayerObject()

	if (pGhost == nil) then
		return 1
	end

	local playerID = SceneObject(pOwner):getObjectID()
	local escortPoints = self.escortPoints
	local currentIndex = readData(playerID .. ":" .. self.className .. ":escortPointIndex")

	-- Check if this is the final point
	if (currentIndex >= #escortPoints) then
		-- Mission complete!
		dropObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pRescueShip)
		self:completeQuest(pOwner, "true")
		return 1
	end

	-- Move to next point
	local nextIndex = currentIndex + 1
	writeData(playerID .. ":" .. self.className .. ":escortPointIndex", nextIndex)

	-- Update waypoint to next point
	local nextPoint = escortPoints[nextIndex]

	SpaceHelpers:clearQuestWaypoint(pOwner, self.className)

	local waypointID = PlayerObject(pGhost):addWaypoint(self.questZone, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":quest_escort_t", "", nextPoint.x, nextPoint.z, nextPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	return 0
end

function SpaceRescueScreenplay:handleTargetDestroyed(pRescueShip, pKiller)
	if (pRescueShip == nil) then
		return 1
	end

	local missionOwnerID = ShipAiAgent(pRescueShip):getMissionOwnerID()
	local pPlayer = getSceneObject(missionOwnerID)

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	if (self.DEBUG_SPACE_RESCUE) then
		print(self.className .. ":handleTargetDestroyed called -- Rescue ship destroyed")
	end

	-- Fail the quest
	self:failQuest(pPlayer, "true")

	return 1
end
