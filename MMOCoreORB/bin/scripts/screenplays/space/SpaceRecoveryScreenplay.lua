SpaceRecoveryScreenplay = SpaceQuestLogic:new {
	className = "SpaceRecoveryScreenplay",

	-- Screenplay Specific Variables

	DEBUG_SPACE_RECOVERY = false,

	arrivalDelay = 5, -- In Seconds

	recoverShip = "",
	recoveryConversationMobile = "",

	preRecoveryPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	recoveryPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	escortSpeed = 20,
	testEscortSpeed = 40,

	attackDelay = 30, -- In Seconds

	attackShips = {
		{},
	},

	recoveryDelay = 5,

	tauntData = {
		panicCount = 5,
		thanksCount = 5,
	},
}

registerScreenPlay("SpaceRecoveryScreenplay", false)

--[[

		Space Recovery Quest Functions

--]]

function SpaceRecoveryScreenplay:start()
	self:spawnActiveAreas()
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

	self:despawnShips(pPlayer)

	self:cleanUpQuestData(SceneObject(pPlayer):getObjectID())

	if (self.sideQuest and self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.COMPLETION) then
		local alertMessage = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":split_quest_alert"

		-- Split Quest Alert
		createEvent((self.sideQuestDelay * 1000), "SpaceHelpers", "sendQuestAlert", pPlayer, alertMessage)

		-- Trigger Sidequest
		createEvent(self.sideQuestDelay * 1050, self.sideQuestType .. "_" .. self.sideQuestName, "startQuest", pPlayer, "")

		if (self.sideQuestType == "surival") then
			-- REMOVE AFTER IMPLEMENTATION
			createEvent((self.sideQuestDelay * 1000) + 2000, self.sideQuestType .. "_" .. self.sideQuestName, "completeQuest", pPlayer, "true")
		end
	end
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

	local failedType = readData(playerID .. self.className .. ":failedType:")
	deleteData(playerID .. self.className .. ":failedType:")

	if (notifyBool) then
		local failedTypeString = ":failed_escape"

		if (failedType == 1) then
			failedTypeString = ":failed_destroy"
		end

		-- Quest Update
		SpaceHelpers:sendQuestUpdate(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. failedTypeString)
	end

	-- Clean Up data last
	self:cleanUpQuestData(playerID)

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.parentQuestName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.sideQuestName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.sideQuestName, "failQuest", pPlayer, "false")
	end
end

function SpaceRecoveryScreenplay:cleanUpQuestData(playerID)
	deleteData(playerID .. self.className .. ":failedType:")
	deleteData(playerID .. self.className .. ":recoveryShip:")
	deleteData(playerID .. self.className .. ":totalActiveWaves:")

	deleteStringVectorSharedMemory(playerID .. self.className .. ":spawnedShips:")
	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
end

function SpaceRecoveryScreenplay:spawnActiveAreas()
	local areasTable = self.recoveryPoints

	for i = 1, #areasTable, 1 do
		local zoneName = areasTable[i].zoneName
		local x = areasTable[i].x
		local z = areasTable[i].z
		local y = areasTable[i].y
		local escortNumber = areasTable[i].escortNumber

		if (not isZoneEnabled(zoneName)) then
			goto continue
		end

		local pQuestArea = spawnSpaceActiveArea(zoneName, "object/space_active_area.iff", x, z, y, areasTable[i].radius)

		if pQuestArea == nil then
			Logger:log(self.className .. ":spawnActiveAreas -- pQuestArea is nil.", LT_ERROR)
			return
		end

		local questAreaID = SceneObject(pQuestArea):getObjectID()

		-- Write the escort point number
		writeData(questAreaID .. ":" .. self.className, escortNumber)

		-- Add Entry Observer for ships
		createObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pQuestArea)

		if (self.DEBUG_SPACE_RECOVERY) then
			print(self.className .. ":spawnActiveAreas - Area Spawned ID: " .. questAreaID .. " Observer: " .. self.className .. ":notifyEnteredQuestArea Escort Point Number: " .. escortNumber)
		end

		::continue::
	end
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
	local recoverPoint = self.preRecoveryPoints[1]
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

	for i = 1, #self.preRecoveryPoints, 1 do
		table.insert(availablePoints, self.preRecoveryPoints[i].name)
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. " -- Total Pre-Recovery Points: " .. #availablePoints)
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

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. " -- Recover Ship Spawned: " .. ShipObject(pShipAgent):getShipName() .. " ID: " .. agentID)
	end

	-- Recovery Ship Observers
	createObserver(DESTROYEDSHIP, self.className, "notifyRecoveryShipDestroyed", pShipAgent)
	createObserver(SHIPDISABLED, self.className, "notifyRecoveryShipDisabled", pShipAgent)

	-- Set the agent as a mission object
	CreatureObject(pPlayer):addSpaceMissionObject(agentID, (totalEscortingShips < 1))

	-- Set as a mission-specific ship locked to the mission holder
	ShipAiAgent(pShipAgent):setMissionOwner(pPlayer)

	-- Set Fixed Patrol and escort flags
	ShipAiAgent(pShipAgent):setFixedPatrol()

	-- Store recover ship ID
	writeData(playerID .. self.className .. ":recoveryShip:", agentID)

	if (self.recoveryConversationMobile ~= "") then
		ShipAiAgent(pShipAgent):setConversationMobile(self.recoveryConversationMobile)
	end

	-- Assign the flight path
	self:assignEscortPoints(pShipAgent, availablePoints)

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

		if (self.DEBUG_SPACE_RECOVERY) then
			print(self.className .. " -- Recover Escort Ship Spawned: " .. ShipObject(pEscortShip):getShipName() .. " ID: " .. escortID)
		end

		createObserver(DESTROYEDSHIP, self.className, "notifyEscortShipDestroyed", pEscortShip)

		-- Set the agent as a mission object
		CreatureObject(pPlayer):addSpaceMissionObject(escortID, (totalEscortingShips == i))

		-- Set as a mission-specific ship locked to the mission holder
		ShipAiAgent(pEscortShip):setMissionOwner(pPlayer)

		-- Set Fixed Patrol and escort flags
		ShipAiAgent(pEscortShip):setFixedPatrol()

		-- Assign the flight path
		self:assignEscortPoints(pEscortShip, availablePoints)

		-- Add to the list of shipIDs
		table.insert(shipIDs, escortID)

		::continue::
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":spawnEscortShip -- Storing Total Ship IDs: " .. #shipIDs)
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

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":assignEscortPoints to -- Ship: " .. ShipObject(pShipAgent):getShipName() .. " Total Points to assign: " .. #flightPath)
	end

	ShipAiAgent(pShipAgent):assignFixedPatrolPointsTable(flightPath)
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
	local attackShips = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

	for i = 1, #attackShips, 1 do
		table.insert(shipIDs, attackShips[i])
	end

	if (pRecoveryShip ~= nil and ShipAiAgent(pRecoveryShip):getMissionOwnerID() == playerID) then
		dropObserver(DESTROYEDSHIP, self.className, "notifyRecoveryShipDestroyed", pRecoveryShip)
		dropObserver(SHIPDISABLED, self.className, "notifyRecoveryShipDisabled", pRecoveryShip)

		deleteData(recoveryShipID .. ":" .. self.className .. ":recoveryShipProgress:")

		-- Make ship fly away first
		ShipObject(pRecoveryShip):setHyperspacing(true);

		local hyperspaceLocation = ShipObject(pRecoveryShip):getSpawnPointInFrontOfShip(2500, 8000)

		SceneObject(pRecoveryShip):setPosition(hyperspaceLocation[1], hyperspaceLocation[2], hyperspaceLocation[3])

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

		deleteData(shipID .. self.className .. ":activeWaveAssignment:")

		if (pShipAgent == nil) then
			goto continue
		end

		-- This function can all be used to despawn wave attack ships, check to remove both observers
		dropObserver(DESTROYEDSHIP, self.className, "notifyEscortShipDestroyed", pShipAgent)
		dropObserver(DESTROYEDSHIP, self.className, "notifyAttackShipDestroyed", pShipAgent)

		-- Make ship fly away first
		ShipObject(pShipAgent):setHyperspacing(true);

		local hyperspaceLocation = ShipObject(pShipAgent):getSpawnPointInFrontOfShip(2500, 8000)

		SceneObject(pShipAgent):setPosition(hyperspaceLocation[1], hyperspaceLocation[2], hyperspaceLocation[3])

		createEvent(2000, "SpaceHelpers", "delayedDestroyShipAgent", pShipAgent, "")

		::continue::
	end
end

function SpaceRecoveryScreenplay:startRecovery(pRecoveryShip)
	if (pRecoveryShip == nil or not SceneObject(pRecoveryShip):isShipAiAgent()) then
		Logger:log(self.className .. ":startRecovery -- pRecoveryShip is nil.", LT_ERROR)
		return
	end

	local missionOwnerID = ShipAiAgent(pRecoveryShip):getMissionOwnerID()
	local pPlayer = getSceneObject(missionOwnerID)

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
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

	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)
end

function SpaceRecoveryScreenplay:continueRecovery(pRecoveryShip)
	if (pRecoveryShip == nil or not SceneObject(pRecoveryShip):isShipAiAgent()) then
		Logger:log(self.className .. ":continueRecovery -- pRecoveryShip is nil.", LT_ERROR)
		return
	end

	local missionOwnerID = ShipAiAgent(pRecoveryShip):getMissionOwnerID()
	local pPlayer = getSceneObject(missionOwnerID)

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	local pPlayerShip = SceneObject(pPlayer):getRootParent()

	if (pPlayerShip == nil or not SceneObject(pPlayerShip):isShipObject()) then
		self:failQuest(pPlayer)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":continueRecovery -- Called for Destructed ShipAgent Object: " .. ShipObject(pRecoveryShip):getShipName() .. " Mission Owner: " .. SceneObject(pPlayer):getDisplayedName())
	end

	local tauntString = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":capture_phase_2"

	ShipAiAgent(pRecoveryShip):tauntPlayer(pPlayer, tauntString)

	local recoveryAgentID = SceneObject(pRecoveryShip):getObjectID()

	-- Update quest journal
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 2, false)
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 3, true)

	-- Drop it as a mission object for now
	CreatureObject(pPlayer):removeSpaceMissionObject(recoveryAgentID, true)

	-- Update the ships faction
	ShipObject(pRecoveryShip):setShipFactionString(SpaceHelpers:getPlayerShipFactionString(pPlayer))

	ShipAiAgent(pRecoveryShip):swapSpaceFactionAssociations()

	-- Remove as enemy
	ShipAiAgent(pRecoveryShip):removeEnemyShip(SceneObject(pPlayerShip):getObjectID())
	TangibleObject(pRecoveryShip):clearPvpStatusBit(AGGRESSIVE)

	-- Repair the ship
	ShipAiAgent(pRecoveryShip):repairShipAgent(100)

	-- Give Ship Escort Flag
	ShipAiAgent(pRecoveryShip):setEscort()

	-- Set Escort Speed
	if (self.DEBUG_SPACE_RECOVERY) then
		ShipAiAgent(pRecoveryShip):setEscortSpeed(self.testEscortSpeed)
	else
		ShipAiAgent(pRecoveryShip):setEscortSpeed(self.escortSpeed)
	end

	-- Broadcast we are a friendly now
	TangibleObject(pRecoveryShip):broadcastPvpStatusBitmask()

	-- Re-add to the mission object list
	CreatureObject(pPlayer):addSpaceMissionObject(recoveryAgentID, true)

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

	local pointsTable = {}

	for i = 1, totalPoints, 1 do
		table.insert(pointsTable, flightPath[i].name)
	end

	ShipAiAgent(pRecoveryShip):assignFixedPatrolPointsTable(pointsTable)

	writeData(SceneObject(pRecoveryShip):getObjectID() .. ":" .. self.className .. ":recoveryShipProgress:", totalPoints)
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

	local totalActiveWaves = readData(missionOwnerID .. self.className .. ":totalActiveWaves:")

	if (totalActiveWaves >= 2) then
		return
	end

	totalActiveWaves = totalActiveWaves + 1

	deleteData(missionOwnerID .. self.className .. ":totalActiveWaves:")
	writeData(missionOwnerID .. self.className .. ":totalActiveWaves:", totalActiveWaves)

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
	local spawnTables = self.attackShips
	local attackShipsGroup = readData(missionOwnerID .. self.className .. ":attackShipsGroup:") + 1

	-- Check if we should use the next group of attack ships in the attackShips table
	if (attackShipsGroup > #spawnTables) then
		attackShipsGroup = 1

		deleteData(missionOwnerID .. self.className .. ":attackShipsGroup:")
	end

	writeData(missionOwnerID .. self.className .. ":attackShipsGroup:", attackShipsGroup)

	-- Get the proper table of ships
	spawnTable = self.attackShips[attackShipsGroup]

	local shipIDs = readStringVectorSharedMemory(missionOwnerID .. self.className .. ":spawnedShips:")
	deleteStringVectorSharedMemory(missionOwnerID .. self.className .. ":spawnedShips:")

	local newShipIDs = {}

	for i = 1, #shipIDs, 1 do
		table.insert(newShipIDs, shipIDs[i])
	end

	local playerFactionHash = SpaceHelpers:getPlayerSpaceFactionHash(pPlayer)

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":spawnAttackWave -- Spawn Table Size: " .. #spawnTable .. " Spawn Zone: " .. spawnZone .. " Player Faction Hash: " .. playerFactionHash .. " Active Wave Assignement: " .. totalActiveWaves .. " Attack Ships Group Selection: " .. attackShipsGroup)
		print("Recovery Ship Position - x = " .. x .. " z = " .. z .. " y = " .. y .. " Spawn Position - x = " .. spawnLocation[1] .. " z = " .. spawnLocation[2] .. " y = " .. spawnLocation[3])

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
		table.insert(newShipIDs, agentID)

		-- Set the wave number
		writeData(agentID .. self.className .. ":activeWaveAssignment:", totalActiveWaves)

		-- Update the count for this wave assignment
		local waveCount = readData(missionOwnerID .. self.className .. ":activeWaveCount_" .. tostring(totalActiveWaves) .. ":")

		deleteData(missionOwnerID .. self.className .. ":activeWaveCount_" .. tostring(totalActiveWaves) .. ":")
		writeData(missionOwnerID .. self.className .. ":activeWaveCount_" .. tostring(totalActiveWaves) .. ":", waveCount + 1)

		-- Add aggo and set the escort ship as ShipAgents Defender
		ShipAiAgent(pShipAgent):engageShipTarget(pRecoveryShip)

		::continue::
	end

	-- Store the Spawned Attack Ships
	writeStringVectorSharedMemory(missionOwnerID .. self.className .. ":attackShips:", newShipIDs)

	-- Schedule next attack wave
	createEvent(self.attackDelay * 1000, self.className, "spawnAttackWave", pRecoveryShip, "")

	-- Send Panic Message to Players
	ShipAiAgent(pRecoveryShip):tauntPlayer(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":panic_" .. tostring(getRandomNumber(1, self.tauntData.panicCount)))
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

	local recoveryAgentID = SceneObject(pShipAgent):getObjectID()

	-- Remove agent as mission object
	CreatureObject(pPlayer):removeSpaceMissionObject(recoveryAgentID, true)

	-- Quest Update
	SpaceHelpers:sendQuestUpdate(pPlayer, "@space/quest:warpout_failure")

	-- Write failed type for ship being destroyed
	writeData(SceneObject(pPlayer):getObjectID() .. self.className .. ":failedType:", 1)

	-- Schedule Fail event
	createEvent(2000, self.className, "failQuest", pPlayer, "")

	return 1
end

function SpaceRecoveryScreenplay:notifyRecoveryShipDisabled(pShipAgent, pPlayer)
	if (pShipAgent == nil or not SceneObject(pShipAgent):isShipAiAgent()) then
		return 1
	end

	local missionOwnerID = ShipAiAgent(pShipAgent):getMissionOwnerID()

	if (pPlayer == nil or missionOwnerID ~= SceneObject(pPlayer):getObjectID()) then
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

	local missionOwnerID = ShipAiAgent(pShipAgent):getMissionOwnerID()

	if (pPlayer == nil or missionOwnerID ~= SceneObject(pPlayer):getObjectID()) then
		pPlayer = getSceneObject(missionOwnerID)
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	local shipAgentID = SceneObject(pShipAgent):getObjectID()

	-- Remove agent as mission object
	CreatureObject(pPlayer):removeSpaceMissionObject(shipAgentID, true)

	-- Drop Ships from spawned vector
	local spawnedShips = readStringVectorSharedMemory(missionOwnerID .. self.className .. ":spawnedShips:")
	deleteStringVectorSharedMemory(missionOwnerID .. self.className .. ":spawnedShips:")

	local newShipIDs = {}

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyEscortShipDestroyed -- Called for ShipAgent Object: " .. ShipObject(pShipAgent):getShipName() .. " Total Spawned Ships " .. #spawnedShips .. " Mission Owner ID: " .. missionOwnerID)
	end

	for i = 1, #spawnedShips, 1 do
		local shipID = spawnedShips[i]

		if (tonumber(shipID) == shipAgentID) then
			goto continue
		end

		table.insert(newShipIDs, shipID)

		::continue::
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyEscortShipDestroyed -- Ships Remaining: " .. #newShipIDs)
	end

	if (#newShipIDs > 0) then
		-- Store the remaining Escort Ships
		writeStringVectorSharedMemory(missionOwnerID .. self.className .. ":spawnedShips:", newShipIDs)

		local messageString = LuaStringIdChatParameter("@spacequest/" .. self.questType .. "/" .. self.questName .. ":escort_remaining")
		messageString:setDI(#newShipIDs)

		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	else
		-- Send attack over message
		CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" .. self.questName .. ":escort_wiped_out")

		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_all.cef", "")
	end

	return 1
end

function SpaceRecoveryScreenplay:notifyAttackShipDestroyed(pShipAgent, pPlayer)
	if (pShipAgent == nil or not SceneObject(pShipAgent):isShipAiAgent()) then
		return 1
	end

	local missionOwnerID = ShipAiAgent(pShipAgent):getMissionOwnerID()

	if (pPlayer == nil or missionOwnerID ~= SceneObject(pPlayer):getObjectID()) then
		pPlayer = getSceneObject(missionOwnerID)
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	local recoveryShipID = readData(missionOwnerID .. self.className .. ":recoveryShip:")
	local pRecoveryShip = getSceneObject(recoveryShipID)

	if (pRecoveryShip == nil or not SceneObject(pRecoveryShip):isShipAiAgent()) then
		self:failQuest(pPlayer)
		return 1
	end

	local shipAgentID = SceneObject(pShipAgent):getObjectID()

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyAttackShipDestroyed - Ship Destoyed: " .. SceneObject(pShipAgent):getDisplayedName() .. " Quest Owner Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	-- Remove agent as mission object
	CreatureObject(pPlayer):removeSpaceMissionObject(shipAgentID, true)

	local attackShips = readStringVectorSharedMemory(missionOwnerID .. self.className .. ":attackShips:")
	deleteStringVectorSharedMemory(missionOwnerID .. self.className .. ":attackShips:")

	local remainingShips = {}

	for i = 1, #attackShips, 1 do
		local shipID = tonumber(attackShips[i])

		if (shipID == shipAgentID) then
			goto continue
		end

		table.insert(remainingShips, shipID)

		::continue::
	end

	if (#remainingShips > 0) then
		writeStringVectorSharedMemory(missionOwnerID .. self.className .. ":attackShips:", remainingShips)

		local messageString = LuaStringIdChatParameter("@space/quest:destroy_duty_targets_remaining")
		messageString:setDI(#remainingShips)

		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	else
		-- Player Notifications
		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_wave.cef", "")
		CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" .. self.questName .. ":attack_stopped")

		-- Send thank you
		ShipAiAgent(pRecoveryShip):tauntPlayer(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":thanks_" .. tostring(getRandomNumber(1, self.tauntData.thanksCount)))
	end

	-- Get the Attack ships wave assignement
	local agentsWave = readData(shipAgentID .. self.className .. ":activeWaveAssignment:")
	deleteData(shipAgentID .. self.className .. ":activeWaveAssignment:")

	-- Update the count for this wave assignment
	local waveCount = readData(missionOwnerID .. self.className .. ":activeWaveCount_" .. tostring(agentsWave) .. ":")

	-- Last ship from this wave, decrement, store data and schedule another
	if (waveCount <= 1) then
		-- Remove this waves count
		deleteData(missionOwnerID .. self.className .. ":activeWaveCount_" .. tostring(agentsWave) .. ":")

		-- Decrement the active wave count
		local currentWaves = readData(missionOwnerID .. self.className .. ":totalActiveWaves:")
		deleteData(missionOwnerID .. self.className .. ":totalActiveWaves:")

		if (currentWaves > 1) then
			writeData(missionOwnerID .. self.className .. ":totalActiveWaves:", currentWaves - 1)
		end

		if (self.attackDelay > 0) then
			-- Schedule attack wave
			createEvent(self.attackDelay * 1000, self.className, "spawnAttackWave", pRecoveryShip, "")
		end
	else
		-- Update the count for this wave assignement
		writeData(missionOwnerID .. self.className .. ":activeWaveCount_" .. tostring(agentsWave) .. ":", waveCount - 1)
	end

	return 1
end

function SpaceRecoveryScreenplay:notifyEnteredQuestArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil)) then
		return 0
	end

	if (not SceneObject(pShip):isShipAiAgent()) then
		return 0
	end

	local shipAgentID = SceneObject(pShip):getObjectID()
	local missionOwnerID = ShipAiAgent(pShip):getMissionOwnerID()
	local recoveryShipID = readData(missionOwnerID .. self.className .. ":recoveryShip:")

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyEnteredQuestArea - Ship ID: " .. shipAgentID .. " Recovery Ship ID: " .. recoveryShipID .. " Mission Owner ID: " .. missionOwnerID)
	end

	-- Prevent attacking ships triggering escort progress
	if (recoveryShipID ~= shipAgentID) then
		return 0
	end

	local pPlayer = getSceneObject(missionOwnerID)

	if (pPlayer == nil) then
		return 0
	end

	if (not SceneObject(pPlayer):isPlayerCreature() or not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		createEvent(1000, self.className, "failQuest", pPlayer, "false")
		return 0
	end

	local shipProgress = readData(shipAgentID .. ":" .. self.className .. ":recoveryShipProgress:")
	deleteData(shipAgentID .. ":" .. self.className .. ":recoveryShipProgress:")

	shipProgress = shipProgress - 1

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyEnteredQuestArea - Recovery Ship: " .. SceneObject(pShip):getDisplayedName() .. " Player Escorting: " .. SceneObject(pPlayer):getDisplayedName() .. " Recovery Progress: " .. shipProgress)
	end

	-- Escort is not complete
	if (shipProgress > 0) then
		-- Write the escort ships progress
		writeData(shipAgentID .. ":" .. self.className .. ":recoveryShipProgress:", shipProgress)

		return 0
	end

	-- Complete the quest final task 3
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 3, false)

	local questUpdate = LuaStringIdChatParameter("@spacequest/" .. self.questType .. "/" .. self.questName .. ":quest_update")
	questUpdate:setTO("@spacequest/" .. self.questType .. "/" .. self.questName .. ":recovery_success")

	CreatureObject(pPlayer):sendSystemMessage(questUpdate:_getObject())

	-- Send Complete Message to Player & Group
	ShipAiAgent(pShip):tauntPlayer(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":complete")

	-- Complete quest
	createEvent(1000, self.className, "completeQuest", pPlayer, "true")

	return 0
end
