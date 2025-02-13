SpaceAssassinateScreenplay = SpaceQuestLogic:new {
	className = "SpaceAssassinateScreenplay",

	DEBUG_SPACE_ASSASSINATE = false,

	arrivalDelay = 5, -- Seconds
	failTimer = 20, -- Minutes

	assassinateTarget = "",
	assassinateEscorts = {},
}

function SpaceAssassinateScreenplay:startQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (pNpc == "") then
		pNpc = nil
	end

	-- Activate the Journal Quest
	SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, self.questType, self.questName, false)

	local spaceQuestHash = getHashCode(self.questZone)
	local zoneName = SceneObject(pPlayer):getZoneName()
	local playerZoneHash = getHashCode(zoneName)
	local pRootParent = SceneObject(pPlayer):getRootParent()

	-- Check if the player is in the proper zone already
	if (playerZoneHash == spaceQuestHash and pRootParent ~= nil and SceneObject(pRootParent):getObjectName() ~= "player_sorosuub_space_yacht") then
		createEvent(2000, self.className, "deployTargets", pPlayer, "")
	end

	-- Create inital observer for player entering Zone and to handle failing quest
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

function SpaceAssassinateScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_ASSASSINATE) then
		print(self.className .. ":completeQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	-- Activate the Journal Quest
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Remove the vector, it is no longer needed
	deleteStringVectorSharedMemory(playerID .. self.className .. ":targetShips:")
end

function SpaceAssassinateScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_ASSASSINATE) then
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

	-- Despawn the target ships
	self:despawnTargetShips(pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Data to Delete
	deleteData(playerID .. ":" .. self.className .. ":TotalKills:")
	deleteData(playerID .. ":" .. self.className .. ":EscortKills:")

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end
end

function SpaceAssassinateScreenplay:failAssassination(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return
	end

	-- Failed message
	CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" ..  self.questName .. ":failed_escape")

	-- Fail the quest for the player
	createEvent(1000, self.className, "failQuest", pPlayer, "true")
end

function SpaceAssassinateScreenplay:deployTargets(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local primaryTarget = self.assassinateSpawns.target
	local escortShips = self.assassinateSpawns.escorts
	local spawnZone = self.questZone
	local playerID = SceneObject(pPlayer):getObjectID()

	if (self.DEBUG_SPACE_ASSASSINATE) then
		print(self.className .. ":deployTargets -- spawnZone: " .. spawnZone .. " Primary Target: " .. primaryTarget .. " Total Escorting Ships: " .. #escortShips)
	end

	local spawnPoint = self.targetPatrols[1]
	local x = spawnPoint.x
	local z = spawnPoint.z
	local y = spawnPoint.y

	-- Spawn the Primary Assassination Target Ship
	local pPrimaryAgent = spawnShipAgent(primaryTarget, spawnZone, x, z, y)

	if (pPrimaryAgent == nil) then
		Logger:log(self.className .. ":deployTargets -- Primary Target is nil. Template: " .. primaryTarget, LT_ERROR)
		return
	end

	local shipIDs = {}
	local primaryID = SceneObject(pPrimaryAgent):getObjectID()

	shipIDs[#shipIDs + 1] = primaryID

	-- Set Fixed Patrol
	ShipAiAgent(pPrimaryAgent):setFixedPatrol()

	self:assignPatrols(pPrimaryAgent)

	-- Set to not despawn. Screenplay will handle cleanup if time runs out of player fails
	ShipAiAgent(pPrimaryAgent):setDespawnOnNoPlayerInRange(false)

	-- Add kill observer
	createObserver(OBJECTDESTRUCTION, self.className, "notifyShipDestroyed", pPrimaryAgent)

	-- Store the quest owner
	writeData(primaryID .. ":" .. self.className .. ":QuestOwner", playerID)

	-- Set as primary target
	writeData(primaryID .. ":" .. self.className .. ":PrimaryTarget:", 1)

	-- Spawn the Escort ships
	for i = 1, #escortShips, 1 do
		local shipName = escortShips[i]

		if (self.DEBUG_SPACE_SURPRISE_ATTACK) then
			print(self.className .. "deployTargets -- spawning target escort ship: " .. shipName)
		end

		local pShipAgent = spawnShipAgent(shipName, spawnZone, x + (getRandomNumber(25, 400) - getRandomNumber(25, 400)), z, y - getRandomNumber(50, 300))

		if (pShipAgent ~= nil) then
			-- Set Fixed Patrol
			ShipAiAgent(pShipAgent):setFixedPatrol()

			-- Assign the patrols to the escort
			createEvent(i * 500, self.className, "assignPatrols", pShipAgent, "")

			-- Set to not despawn. Screenplay will handle cleanup if time runs out of player fails
			ShipAiAgent(pShipAgent):setDespawnOnNoPlayerInRange(false)

			-- Add kill observer
			createObserver(OBJECTDESTRUCTION, self.className, "notifyShipDestroyed", pShipAgent)

			local agentID = SceneObject(pShipAgent):getObjectID()

			shipIDs[#shipIDs + 1] = agentID

			-- Store the quest owner
			writeData(agentID .. ":" .. self.className .. ":QuestOwner", playerID)
		end
	end

	for i = 1, #shipIDs, 1 do
		-- Set as space mission object
		CreatureObject(pPlayer):addSpaceMissionObject(shipIDs[i], (i == #shipIDs))
	end

	-- Store the Spawned Attack Ships
	writeStringVectorSharedMemory(playerID .. self.className .. ":targetShips:", shipIDs)

	-- Send Uploading end message
	CreatureObject(pPlayer):sendSystemMessage("@spacequest/assassinate/" .. self.questName .. ":" .. "arrival_phase_2")

	-- Player enemy spawn effect for player
	CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_spawn_enemy.cef", "")

	-- Schedule the target location for the player
	createEvent(3000, self.className, "updateTargetLocation", pPlayer, "")

	-- Schedule Mission Fail
	createEvent(self.failTimer * 60 * 1000, self.className, "failAssassination", pPlayer, "")
end

function SpaceAssassinateScreenplay:updateTargetLocation(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":targetShips:")
	local pShipAgent = nil

	-- Find a ship agent that is still valid
	for i = 1, #shipIDs, 1 do
		local shipID = tonumber(shipIDs[i])

		if (pShipAgent == nil) then
			pShipAgent = getSceneObject(shipID)
		end
	end

	if (pShipAgent == nil) then
		if (self.DEBUG_SPACE_ASSASSINATE) then
			print(self.className .. ":updateTargetLocation -- All targes are nil, returning without update to player.")
		end
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	-- Remove any current waypoints
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	if (self.DEBUG_SPACE_ASSASSINATE) then
		print(self.className .. ":updateTargetLocation -- Sending player new waypoint update.")
	end

	local x = SceneObject(pShipAgent):getPositionX()
	local z = SceneObject(pShipAgent):getPositionZ()
	local y = SceneObject(pShipAgent):getPositionY()

	local waypointID = PlayerObject(pGhost):addWaypoint(self.questZone, "@spacequest/assassinate/" .. self.questName .. ":quest_target_t", "", x, z, y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
	end

	-- Store the waypointID on the player
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	-- Schedule to send out new waypoint
	createEvent(15 * 1000, self.className, "updateTargetLocation", pPlayer, "")
end

function SpaceAssassinateScreenplay:assignPatrols(pShipAgent)
	if (pShipAgent == nil) then
		return
	end

	local patrols = self.targetPatrols

	for i = 1, #patrols, 1 do
		local pointName = patrols[i].name

		ShipAiAgent(pShipAgent):addFixedPatrolPoint(pointName)
	end
end

function SpaceAssassinateScreenplay:despawnTargetShips(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":targetShips:")

	local pPlayer = getSceneObject(playerID)

	-- Remove the vector, it is no longer needed
	deleteStringVectorSharedMemory(playerID .. self.className .. ":targetShips:")

	for i = 1, #shipIDs, 1 do
		local shipID = tonumber(shipIDs[i])
		local pShipAgent = getSceneObject(shipID)

		deleteData(shipID .. ":" .. self.className .. ":QuestOwner")
		deleteData(shipID .. ":" .. self.className .. ":PrimaryTarget:")

		if (pShipAgent ~= nil) then
			-- Make ship fly away first
			ShipObject(pShipAgent):setHyperspacing(true);

			SceneObject(pShipAgent):setPosition(8000, 8000, 8000)

			createEvent(2000, "SpaceHelpers", "delayedDestroyShipAgent", pShipAgent, "")
		end

		if (pPlayer ~= nil) then
			-- Remove as Space Mission Object
			CreatureObject(pPlayer):removeSpaceMissionObject(shipID, false)
		end
	end
end

--[[

		Space Destroy Observers

--]]

function SpaceAssassinateScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
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

	if (self.DEBUG_SPACE_ASSASSINATE) then
		print(self.className .. ":enteredZone called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Player Zone Hash: " .. zoneNameHash .. " questZone hash: " .. spaceQuestHash)
	end

	-- Player is in the correct zone
	if (zoneNameHash == spaceQuestHash and not SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, false)

		-- Send Uploading start message
		CreatureObject(pPlayer):sendSystemMessage("@spacequest/assassinate/" .. self.questName .. ":arrival_phase_1")

		-- Schedule the deployment
		createEvent(self.arrivalDelay * 1000, self.className, "deployTargets", pPlayer, "")
	else
		createEvent(2000, self.className, "failQuest", pPlayer, "true")
	end

	return 0
end

function SpaceAssassinateScreenplay:notifyShipDestroyed(pShipAgent, pKillerShip)
	if (pShipAgent == nil) then
		return 1
	end

	local agentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(agentID .. ":" .. self.className .. ":QuestOwner")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		Logger:log(self.className .. ":notifyShipDestroyed - Quest Owner is nil.", LT_ERROR)
		return 1
	end

	-- Delete the quest owner data
	deleteData(agentID .. ":" .. self.className .. ":QuestOwner")

	if (self.DEBUG_SPACE_ASSASSINATE) then
		print(self.className .. ":notifyShipDestroyed - Ship Destoyed: " .. SceneObject(pShipAgent):getDisplayedName() .. " Quest Owner Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 1
	end

	-- Remove as Space Mission Object
	CreatureObject(pPlayer):removeSpaceMissionObject(agentID, false)

	local isPrimaryTarget = readData(agentID .. ":" .. self.className .. ":PrimaryTarget:")
	local totalKills = readData(playerID .. ":" .. self.className .. ":TotalKills:")
	local escortKills = readData(playerID .. ":" .. self.className .. ":EscortKills:")
	local totalEscorts = #self.assassinateSpawns.escorts

	deleteData(playerID .. ":" .. self.className .. ":TotalKills:")

	totalKills = totalKills + 1

	if (self.DEBUG_SPACE_ASSASSINATE) then
		print(self.className .. ":notifyShipDestroyed - Total Kills: " .. totalKills .. " Escort Kills: " .. escortKills)
	end

	-- The assination primary target has been killed
	if (isPrimaryTarget == 1) then
		deleteData(agentID .. ":" .. self.className .. ":PrimaryTarget:")

		CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" ..  self.questName .. ":assassinate_success")

		-- There are still escort ships remaining
		if (totalEscorts > (totalKills - 1)) then
			CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" ..  self.questName .. ":destroy_escort")
		end
	-- An escorting ship has been killed
	else
		-- Increase the escort kill count
		escortKills = escortKills + 1

		deleteData(playerID .. ":" .. self.className .. ":EscortKills:")

		-- All escort ships have been destroyed
		if (escortKills >= totalEscorts) then
			CreatureObject(pPlayer):sendSystemMessage("@spacequest/" .. self.questType .. "/" ..  self.questName .. ":escort_wiped_out")
		-- There are still escort ships remaining
		else
			local alertMsg = LuaStringIdChatParameter("@spacequest/" .. self.questType .. "/" ..  self.questName .. ":escort_remaining") -- "\\#pcontrast3 Tactical Computer: < \\#pcontrast1 An escorting craft has been destroyed, %DI remain. \\#pcontrast3 >"
			alertMsg:setDI(totalEscorts - escortKills)

			CreatureObject(pPlayer):sendSystemMessage(alertMsg:_getObject())

			-- Store the kill count
			writeData(playerID .. ":" .. self.className .. ":EscortKills:", escortKills)
		end
	end

	-- Player has killed primary target and all of the escorts
	if (totalKills >= (totalEscorts + 1)) then
		-- All enemies have been destroyed
		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_all.cef", "")

		-- Complete the quest
		createEvent(1000, self.className, "completeQuest", pPlayer, "true")

		return 1
	end

	-- Update the kill count
	writeData(playerID .. ":" .. self.className .. ":TotalKills:", totalKills)

	return 0
end
