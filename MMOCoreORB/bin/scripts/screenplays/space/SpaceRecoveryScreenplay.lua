SpaceRecoveryScreenplay = SpaceQuestLogic:new {
	className = "SpaceRecoveryScreenplay",

	-- Screenplay Specific Variables

	DEBUG_SPACE_RECOVERY = true,

	arrivalDelay = 5, -- In Seconds

	recoverShip = "",

	escortPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	recoveryPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	escortSpeed = 20,
	testEscortSpeed = 40,

	attackDelay = 30, -- In Seconds
	attackShips = {},

	recoveryDelay = 5,

	tauntData = {
		panicCount = 5,
	},
}

registerScreenPlay("SpaceRecoveryScreenplay", false)

--[[

		Space Recovery Quest Functions

--]]

function SpaceRecoveryScreenplay:start()
end

function SpaceRecoveryScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
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

		createEvent(self.arrivalDelay * 1000, self.className, "setupRecover", pPlayer, "")
	end

	-- Create inital observer for player entering Zone and to handle failing quest
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

function SpaceRecoveryScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
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

	self:cleanUpQuestData(SceneObject(pPlayer):getObjectID())
end

function SpaceRecoveryScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":failQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	-- Despawn Any ships
	self:despawnShips(pPlayer)

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()

	local failedTypeString = ":failed_escape"
	local failedType = readData(playerID .. self.className .. ":failedType:")
	deleteData(playerID .. self.className .. ":failedType:")

	if (failedType == 1) then
		failedTypeString = ":failed_destroy"
	end

	-- Quest Update
	SpaceHelpers:sendQuestUpdate(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. failedTypeString)

	-- Clean Up data last
	self:cleanUpQuestData(playerID)

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end
end

function SpaceRecoveryScreenplay:cleanUpQuestData(playerID)
	deleteData(playerID .. self.className .. ":failedType:")
	deleteData(playerID .. self.className .. ":recoveryShip:")

	deleteStringVectorSharedMemory(playerID .. self.className .. ":spawnedShips:")
end

function SpaceRecoveryScreenplay:setupRecover(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to setupRecover due to pPlayer being nil.", LT_ERROR)
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Mission Updates
	CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" .. self.questName .. ":arrival_phase_1")

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":setupEscort called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Schedule the ship arrival
	createEvent(self.arrivalDelay * 1000, self.className, "spawnRecoveryShip", pPlayer, "")
end

function SpaceRecoveryScreenplay:spawnRecoveryShip(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to spawnRecoveryShip due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":spawnRecoveryShip called")
	end

	local pPlayerShip = SceneObject(pPlayer):getRootParent()

	if (pPlayerShip == nil or not SceneObject(pPlayerShip):isShipObject()) then
		Logger:log(self.className .. ":spawnRecoveryShip - pPlayerShip is nil.", LT_ERROR)
		return
	end
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Add Initial point to the player
	local recoverPoint = self.escortPoints[1]
	local startingPointName = recoverPoint.name

	local waypointID = PlayerObject(pGhost):addWaypoint(recoverPoint.zoneName, "Mission Target", "Mission Target", recoverPoint.x, recoverPoint.z, recoverPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
	end

	-- Store the waypointID on the player
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	--[[

		Build the escort path

	]]

	local totalPoints = 0
	local availablePoints = {}
	local chosenPoints = {}

	for i = 1, #self.escortPoints do
		table.insert(availablePoints, self.escortPoints[i])
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. " -- Total Available escort Points: " .. #availablePoints)
	end

	while (#availablePoints > 0) do
		local randomPoint = getRandomNumber(1, #availablePoints)
		local pointName = availablePoints[randomPoint].name

		-- Do not add the spawn point, the ships are already here
		if (pointName ~= startingPointName) then
			-- Add the named escort points to the array
			table.insert(chosenPoints, pointName)
		end

		-- Drop the point from the table
		table.remove(availablePoints, randomPoint)
	end

	--[[

			Spawn the Recovery Ship and Escorting Ships

	]]

	local escortingShips = self.escortShips
	local totalEscortingShips = #escortingShips
	local spawnLocation = SpaceHelpers:getRandomPositionInSphere(recoverPoint.x, recoverPoint.z, recoverPoint.y, 100, 200)

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":spawnEscortShip called -- Recover Ship: " .. self.recoverShip .. " Space Zone: " .. recoverPoint.zoneName .. " X: " .. spawnLocation.x .. " Z: " .. spawnLocation.z .. " Y: " .. spawnLocation.y)
	end

	-- Spawn the ship to be recovered
	local pShipAgent = spawnShipAgent(self.recoverShip, recoverPoint.zoneName, spawnLocation.x, spawnLocation.z, spawnLocation.y)

	if (pShipAgent == nil) then
		self:failQuest(pPlayer, "true")

		CreatureObject(pPlayer):sendSystemMessage("Quest failed due to the recovery ship failing to spawn.")
		return
	end

	local agentID = SceneObject(pShipAgent):getObjectID()

	-- Recovery Ship Observers
	createObserver(DESTROYEDSHIP, self.className, "notifyRecoveryShipDestroyed", pShipAgent)
	createObserver(SHIPDISABLED, self.className, "notifyRecoveryShipDisabled", pShipAgent)

	-- Set the agent as a mission object
	CreatureObject(pPlayer):addSpaceMissionObject(agentID, (totalEscortingShips < 1))

	-- Set as a mission-specific ship locked to the mission holder
	ShipAiAgent(pShipAgent):setMissionOwner(pPlayer)

	-- Set Fixed Patrol and escort flags
	ShipAiAgent(pShipAgent):setFixedPatrol()

	-- Add to the list of shipIDs
	writeData(playerID .. self.className .. ":recoveryShip:", agentID)

	if (self.DEBUG_SPACE_RECOVERY) then
		ShipAiAgent(pShipAgent):setEscortSpeed(self.testEscortSpeed)
	else
		ShipAiAgent(pShipAgent):setEscortSpeed(self.escortSpeed)
	end

	-- Assign the flight path
	self:assignEscortPoints(pShipAgent, chosenPoints)

	local shipIDs = {}

	-- Spawn Escorting Ships
	local escortSpawn = ShipObject(pShipAgent):getSpawnPointBehindShip(25, 75)

	for i = 1, totalEscortingShips, 1 do
		-- Spawn the ship to be recovered
		local pEscortShip = spawnShipAgent(escortingShips[i], recoverPoint.zoneName, escortSpawn[1], escortSpawn[2], escortSpawn[3])

		if (pEscortShip == nil) then
			goto continue
		end

		local escortID = SceneObject(pEscortShip):getObjectID()

		createObserver(DESTROYEDSHIP, self.className, "notifyEscortShipDestroyed", pEscortShip)

		-- Set the agent as a mission object
		CreatureObject(pPlayer):addSpaceMissionObject(escortID, (totalEscortingShips == i))

		-- Set as a mission-specific ship locked to the mission holder
		ShipAiAgent(pEscortShip):setMissionOwner(pPlayer)

		-- Set Fixed Patrol and escort flags
		ShipAiAgent(pEscortShip):setFixedPatrol()

		if (self.DEBUG_SPACE_RECOVERY) then
			ShipAiAgent(pEscortShip):setEscortSpeed(self.testEscortSpeed)
		else
			ShipAiAgent(pEscortShip):setEscortSpeed(self.escortSpeed)
		end

		-- Add to the list of shipIDs
		shipIDs[#shipIDs + 1] = escortID

		-- Assign the flight path
		self:assignEscortPoints(pEscortShip, chosenPoints)

		::continue::
	end

	-- Store the spawned ship IDs
	writeStringVectorSharedMemory(playerID .. self.className .. ":spawnedShips:", shipIDs)

	-- Player effect for player
	CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_spawn_escort.cef", "")

	-- Player escort arrival music
	CreatureObject(pPlayer):playMusicMessage("sound/mus_quest_escort_arrival.snd")

	-- Mission update
	CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" .. self.questName .. ":arrival_phase_2")
end

function SpaceRecoveryScreenplay:assignEscortPoints(pShipAgent, flightPath)
	if (pShipAgent == nil) then
		Logger:log(self.className .. ":assignEscortPoints -- pShipAgent is nil.", LT_ERROR)
		return
	end

	local totalPoints = #flightPath

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":assignEscortPoints to -- Ship: " .. ShipObject(pShipAgent):getShipName() .. " Total Points to assign: " .. totalPoints)
	end

	for i = 1, totalPoints, 1 do
		ShipAiAgent(pShipAgent):addFixedPatrolPoint(flightPath[i], (i == 1))
	end
end

function SpaceRecoveryScreenplay:despawnShips(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.className .. ":despawnShips -- pPlayer is nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":despawnShips called")
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Destroy the recovery ship
	local recoveryShipID = readData(playerID .. self.className .. ":recoveryShip:")
	local pRecoveryShip = getSceneObject(recoveryShipID)

	-- Destroy the escort ships
	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":spawnedShips:")

	if (pRecoveryShip ~= nil and ShipAiAgent(pRecoveryShip):getMissionOwnerID() == playerID) then
		dropObserver(DESTROYEDSHIP, self.className, "notifyRecoveryShipDestroyed", pRecoveryShip)
		dropObserver(SHIPDISABLED, self.className, "notifyRecoveryShipDisabled", pRecoveryShip)

		-- Make ship fly away first
		ShipObject(pRecoveryShip):setHyperspacing(true);

		SceneObject(pRecoveryShip):setPosition(8000, 8000, 8000)

		createEvent(2000, "SpaceHelpers", "delayedDestroyShipAgent", pRecoveryShip, "")

		-- Remove as Space Mission Object
		CreatureObject(pPlayer):removeSpaceMissionObject(recoveryShipID, (#shipIDs == 0))
	end

	-- Destroy Any other ships that are spawned (escorts and wave attacks)
	for i = 1, #shipIDs, 1 do
		local shipID = tonumber(shipIDs[i])
		local pShipAgent = getSceneObject(shipID)

		-- Remove as Space Mission Object
		CreatureObject(pPlayer):removeSpaceMissionObject(shipID, (i == #shipIDs))

		if (pShipAgent == nil) then
			goto continue
		end

		-- This function can all be used to despawn wave attack ships, check to remove both observers
		dropObserver(DESTROYEDSHIP, self.className, "notifyEscortShipDestroyed", pShipAgent)
		dropObserver(DESTROYEDSHIP, self.className, "notifyAttackShipDestroyed", pShipAgent)

		-- Make ship fly away first
		ShipObject(pShipAgent):setHyperspacing(true);

		SceneObject(pShipAgent):setPosition(8000, 8000, 8000)

		createEvent(2000, "SpaceHelpers", "delayedDestroyShipAgent", pShipAgent, "")

		::continue::
	end
end

function SpaceRecoveryScreenplay:startRecovery(pRecoveryShip)
	if (pRecoveryShip == nil or not SceneObject(pRecoveryShip):isShipAiAgent()) then
		Logger:log(self.className .. ":startRecovery -- pRecoveryShip is nil.", LT_ERROR)
		return 1
	end

	local missionOwnerID = ShipAiAgent(pRecoveryShip):getMissionOwnerID()
	local pPlayer = getSceneObject(missionOwnerID)

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":startRecovery -- Called for Recovered ShipAgent Object: " .. ShipObject(pRecoveryShip):getShipName() .. " Recovering Player: " .. SceneObject(pPlayer):getDisplayedName())
	end

	local tauntString = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":capture_phase_1"

	ShipAiAgent(pRecoveryShip):tauntPlayer(pPlayer, tauntString)

	-- Docking Music
	CreatureObject(pPlayer):playMusicMessage("sound/mus_quest_theme_docking.snd")

	-- Capture Update
	CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" .. self.questName .. ":capture_started")

	createEvent(self.recoveryDelay * 1000, self.className, "continueRecovery", pRecoveryShip, "")
end

function SpaceRecoveryScreenplay:continueRecovery(pRecoveryShip)
	if (pRecoveryShip == nil or not SceneObject(pRecoveryShip):isShipAiAgent()) then
		Logger:log(self.className .. ":continueRecovery -- pRecoveryShip is nil.", LT_ERROR)
		return 1
	end

	local missionOwnerID = ShipAiAgent(pRecoveryShip):getMissionOwnerID()
	local pPlayer = getSceneObject(missionOwnerID)

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":continueRecovery -- Called for Destructed ShipAgent Object: " .. ShipObject(pRecoveryShip):getShipName() .. " Destructor: " .. SceneObject(pPlayer):getDisplayedName())
	end

	local tauntString = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":capture_phase_2"

	ShipAiAgent(pRecoveryShip):tauntPlayer(pPlayer, tauntString)

	-- Update quest journal
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 2, false)
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 3, true)

	-- Update the ships faction
	ShipObject(pRecoveryShip):setShipFactionString(SpaceHelpers:getPlayerShipFactionString(pPlayer))

	local playerFactionHash = SpaceHelpers:getPlayerShipFactionHash(pPlayer)

	ShipAiAgent(pRecoveryShip):addSpaceFactionAlly(playerFactionHash)
	ShipAiAgent(pRecoveryShip):removeSpaceFactionEnemy(playerFactionHash)

	-- Give Ship Escort Flag
	ShipAiAgent(pRecoveryShip):setEscort()

	-- Repair the ship
	ShipAiAgent(pRecoveryShip):repairShipAgent(100)

	-- Assign the escort points
	createEvent(10 * 1000, self.className, "assignRecoveryPoints", pRecoveryShip, "")

	if (self.attackDelay > 0) then
		-- Schedule attack wave
		createEvent(self.attackDelay * 1000, self.className, "spawnAttackWave", pRecoveryShip, "")
	end
end

function SpaceRecoveryScreenplay:assignRecoveryPoints(pRecoveryShip)
	if (pRecoveryShip == nil) then
		Logger:log(self.className .. ":assignRecoveryPoints -- pRecoveryShip is nil.", LT_ERROR)
		return
	end

	local flightPath = self.recoveryPoints
	local totalPoints = #flightPath

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":assignRecoveryPoints to -- Ship: " .. ShipObject(pRecoveryShip):getShipName() .. " Total Points to assign: " .. totalPoints)
	end

	for i = 1, totalPoints, 1 do
		ShipAiAgent(pRecoveryShip):addFixedPatrolPoint(flightPath[i].name, (i == 1))
	end
end

function SpaceRecoveryScreenplay:spawnAttackWave(pRecoveryShip)
	if (pRecoveryShip == nil) then
		return
	end

	local missionOwnerID = ShipAiAgent(pRecoveryShip):getMissionOwnerID()
	local pPlayer = getSceneObject(missionOwnerID)

	-- This will fail to spawn the scheduled wave if the escort is over
	if (pPlayer == nil or not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return
	end

	local pPlayerShip = SceneObject(pPlayer):getRootParent()

	if (pPlayerShip == nil or not SceneObject(pPlayerShip):isShipObject()) then
		Logger:log(self.className .. ":spawnAttackWave - pPlayerShip is nil.", LT_ERROR)
		self:failQuest(pPlayer, "true")
		return
	end

	-- Send attack alert message
	CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" .. self.questName .. ":attack_notify")

	-- Player effect for player
	CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_spawn_wave.cef", "")

	local x = SceneObject(pRecoveryShip):getPositionX()
	local z = SceneObject(pRecoveryShip):getPositionZ()
	local y = SceneObject(pRecoveryShip):getPositionY()
	local spawnZone = self.questZone

	local spawnLocation = ShipObject(pRecoveryShip):getSpawnPointInFrontOfShip(600, 1200)

	local spawnTable = {}

	if (self.dutyMission) then
		spawnTable = self.attackGroups[getRandomNumber(1, #self.attackGroups)]
	else
		spawnTable = self.attackShips
	end

	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

	local playerFactionHash = SpaceHelpers:getPlayerSpaceFactionHash(pPlayer)

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":spawnAttackWave -- Spawn Table Size: " .. #spawnTable .. " Spawn Zone: " .. spawnZone .. " Player Faction Hash: " .. playerFactionHash)
		print("Player Position - x = " .. x .. " z = " .. z .. " y = " .. y .. " Spawn Position - x = " .. spawnLocation[1] .. " z = " .. spawnLocation[2] .. " y = " .. spawnLocation[3])

		drawClientPath(pRecoveryShip, x, z, y, spawnLocation[1], spawnLocation[2], spawnLocation[3])
	end

	for i = 1, #spawnTable, 1 do
		local pShipAgent = spawnShipAgent(spawnTable[i], spawnZone, spawnLocation[1], spawnLocation[2], spawnLocation[3], pRecoveryShip)

		if (pShipAgent == nil) then
			goto continue
		end

		-- Set as a mission-specific ship locked to the mission holder
		ShipAiAgent(pShipAgent):setMissionOwner(pPlayer)

		-- Set as a wave attack ship
		ShipAiAgent(pShipAgent):setWaveAttack()

		-- Ship attacking the escort ship should be hyperspaced out and destroyed, just in case make sure they are cleaned up
		ShipAiAgent(pShipAgent):setDespawnOnNoPlayerInRange(true)

		-- Add players faction as enemy
		ShipAiAgent(pShipAgent):addSpaceFactionEnemy(playerFactionHash)
		ShipAiAgent(pShipAgent):removeSpaceFactionAlly(playerFactionHash)

		-- Add kill observer
		createObserver(DESTROYEDSHIP, self.className, "notifyAttackShipDestroyed", pShipAgent)

		local agentID = SceneObject(pShipAgent):getObjectID()

		-- Set as space mission object
		CreatureObject(pPlayer):addSpaceMissionObject(agentID, (i == #spawnTable))

		-- Add to the list of shipIDs
		shipIDs[#shipIDs + 1] = agentID

		-- Write the playersID that is escorting
		writeData(agentID .. ":" .. self.className .. ":escorterID:", missionOwnerID)

		-- Add aggo and set the escort ship as ShipAgents Defender
		ShipAiAgent(pShipAgent):engageShipTarget(pRecoveryShip)

		::continue::
	end

	-- Store the Spawned Attack Ships
	writeStringVectorSharedMemory(missionOwnerID .. self.className .. ":attackShips:", shipIDs)

	-- Schedule next attack wave
	createEvent(self.attackDelay * 1000, self.className, "spawnAttackWave", pRecoveryShip, "")

	-- Send Panic Message to Players
	ShipAiAgent(pRecoveryShip):tauntPlayer(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":reason_" .. tostring(getRandomNumber(1, self.tauntData.panicCount)))
end

--[[

		Space Escort Observers

--]]

function SpaceRecoveryScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
	if (pPlayer == nil) then
		return 0
	end

	if (not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return 1
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return 0
	end

	if (SpaceHelpers:isInYacht(pPlayer)) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local spaceQuestHash = getHashCode(self.questZone)

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":enteredZone called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Player Zone Hash: " .. zoneNameHash .. " questZone hash: " .. spaceQuestHash)
	end

	-- Player is in the correct zone
	if (zoneNameHash == spaceQuestHash and not SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, true)

		-- Spawn recovery ships for the player
		createEvent(4000, self.className, "setupRecover", pPlayer, "")

		return 0
	elseif (zoneNameHash ~= spaceQuestHash and SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		createEvent(2000, self.className, "failQuest", pPlayer, "true")

		return 1
	end

	return 0
end

function SpaceRecoveryScreenplay:notifyRecoveryShipDestroyed(pShipAgent, pPlayer)
	if (pShipAgent == nil or not SceneObject(pShipAgent):isShipAiAgent()) then
		return 1
	end

	if (pPlayer == nil) then
		return 1
	end

	local missionOwnerID = ShipAiAgent(pShipAgent):getMissionOwnerID()

	if (missionOwnerID ~= SceneObject(pPlayer):getObjectID()) then
		pPlayer = getSceneObject(missionOwnerID)
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyRecoveryShipDestroyed -- Called for Destructed ShipAgent Object: " .. ShipObject(pShipAgent):getShipName() .. " Destructor: " .. SceneObject(pPlayer):getDisplayedName())
	end

	-- Write data for ship being destroyed
	writeData(SceneObject(pPlayer):getObjectID() .. self.className .. ":failedType:", 1)

	-- Schedule Fail event
	createEvent(2000, self.className, "failQuest", pPlayer, "")

	return 1
end

function SpaceRecoveryScreenplay:notifyRecoveryShipDisabled(pShipAgent, pPlayer)
	if (pShipAgent == nil or not SceneObject(pShipAgent):isShipAiAgent()) then
		return 1
	end

	if (pPlayer == nil) then
		return 1
	end

	local missionOwnerID = ShipAiAgent(pShipAgent):getMissionOwnerID()

	if (missionOwnerID ~= SceneObject(pPlayer):getObjectID()) then
		pPlayer = getSceneObject(missionOwnerID)
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyRecoveryShipDisabled -- Called for Disabled ShipAgent Object: " .. ShipObject(pShipAgent):getShipName() .. " Mission Owner: " .. SceneObject(pPlayer):getDisplayedName())
	end

	local tauntString = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":angry_disable"

	ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, tauntString)

	-- Update quest journal
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 1, false)
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 2, true)

	createEvent(self.recoveryDelay * 1000, self.className, "startRecovery", pShipAgent, "")

	return 1
end

function SpaceRecoveryScreenplay:notifyEscortShipDestroyed(pShipAgent, pPlayer)
	if (pShipAgent == nil or not SceneObject(pShipAgent):isShipAiAgent()) then
		return 1
	end

	if (pPlayer == nil) then
		return 1
	end

	local missionOwnerID = ShipAiAgent(pShipAgent):getMissionOwnerID()
	local shipAgentID = SceneObject(pShipAgent):getObjectID()

	-- Drop Ships from spawned vector
	local spawnedShips = readStringVectorSharedMemory(missionOwnerID .. self.className .. ":spawnedShips:")
	deleteStringVectorSharedMemory(missionOwnerID .. self.className .. ":spawnedShips:")

	local newShipIDs = {}

	for i = 1, #spawnedShips, 1 do
		local shipID = tonumber(spawnedShips[i])

		if (shipID == shipAgentID) then
			goto continue
		end

		table.insert(newShipIDs, shipID)

		::continue::
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyEscortShipDestroyed -- Called for ShipAgent Object: " .. ShipObject(pShipAgent):getShipName() .. " Ships Remaining: " .. #newShipIDs)
	end

	if (#newShipIDs > 0) then
		-- Store the remaining Escort Ships
		writeStringVectorSharedMemory(missionOwnerID .. self.className .. ":spawnedShips:", newShipIDs)

		local messageString = LuaStringIdChatParameter("@spacequest/" .. self.questType .. "/" .. self.questName .. ":escort_remaining")
		messageString:setDI(#newIDs)

		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	else
		-- Send attack over message
		CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" .. self.questName .. ":escort_wiped_out")

		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_all.cef", "")
	end

	return 1
end
