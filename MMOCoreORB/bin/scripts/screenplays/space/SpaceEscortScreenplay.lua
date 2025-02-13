SpaceEscortScreenplay = SpaceQuestLogic:new {
	className = "SpaceEscortScreenplay",

	DEBUG_SPACE_ESCORT = false,

	escortRange = 1000,
	escortShip = "",

	escortPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	spawnAttackWaves = true,
	checkPlayerDistance = true,

	attackDelay = 0, -- In Seconds
	attackShips = {},
}

registerScreenPlay("SpaceEscortScreenplay", false)

--[[

		Space Escortr Quest Functions

--]]

function SpaceEscortScreenplay:start()
	self:spawnActiveAreas()
end

function SpaceEscortScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_ESCORT) then
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
	local pRootParent = SceneObject(pPlayer):getRootParent()

	-- Check if the player is in the proper zone already
	if (playerZoneHash == spaceQuestHash and pRootParent ~= nil and SceneObject(pRootParent):getObjectName() ~= "player_sorosuub_space_yacht") then
		createEvent(2000, self.className, "setupEscort", pPlayer, "")
	end

	-- Create inital observer for player entering Zone and to handle failing quest
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

function SpaceEscortScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_ESCORT) then
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

function SpaceEscortScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_ESCORT) then
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

	self:cleanUpQuestData(SceneObject(pPlayer):getObjectID())

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end
end

function SpaceEscortScreenplay:cleanUpQuestData(playerID)
	-- Delete the stored escorted ship ID
	deleteData(playerID .. ":" .. self.className .. ":escortID:")

	-- Delete player location data
	deleteData(playerID .. ":" .. self.className .. ":location:")

	-- Delete Start point
	deleteData(playerID .. self.className .. ":startPoint:")

	-- Delete the distance warnings
	deleteData(playerID .. ":" .. self.className .. ":distanceWarnings:")
end

function SpaceEscortScreenplay:setupEscort(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to setupEscort due to pPlayer being nil.", LT_ERROR)
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Complete the quest task 1
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

	-- Activate quest task 2
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 2, false)

	-- Quest Progress update
	SpaceHelpers:sendQuestProgess(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":title")

	local randomStart = getRandomNumber(1, #self.escortPoints)
	writeData(playerID .. self.className .. ":startPoint:", randomStart)

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":setupEscort called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Escort Point # Selected: " .. randomStart)
	end

	-- Add escort point to the player
	local escortPoint = self.escortPoints[randomStart]
	local waypointID = PlayerObject(pGhost):addWaypoint(escortPoint.zoneName, "Escort Rendevous", "Escort Rendevous", escortPoint.x, escortPoint.z, escortPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
	end

	-- Store the waypointID on the player
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	local questUpdate = LuaStringIdChatParameter("@spacequest/escort/" .. self.questName .. ":quest_update")
	questUpdate:setTO("@spacequest/escort/" .. self.questName .. ":found_loc")

	CreatureObject(pPlayer):sendSystemMessage(questUpdate:_getObject())
end

function SpaceEscortScreenplay:spawnActiveAreas()
	local areasTable = self.escortPoints

	for i = 1, #areasTable, 1 do
		local zoneName = areasTable[i].zoneName
		local x = areasTable[i].x
		local z = areasTable[i].z
		local y = areasTable[i].y
		local escortNumber = areasTable[i].escortNumber

		if (not isZoneEnabled(zoneName)) then
			goto skip
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

		if (self.DEBUG_SPACE_ESCORT) then
			print(self.className .. ":spawnActiveAreas - Area Spawned ID: " .. questAreaID .. " Observer: " .. self.className .. ":notifyEnteredQuestArea Escort Point Number: " .. escortNumber)
		end

		::skip::
	end
end

function SpaceEscortScreenplay:spawnEscortShip(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.className .. " -- Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to spawnEscortShip due to pPlayer being nil.", LT_ERROR)
		return
	end

	-- Remove the rendevous waypoint from player
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	local playerID = SceneObject(pPlayer):getObjectID()

	local randomStart = readData(playerID .. self.className .. ":startPoint:")
	deleteData(playerID .. self.className .. ":startPoint:")

	local x = self.escortPoints[randomStart].x
	local z = self.escortPoints[randomStart].z
	local y = self.escortPoints[randomStart].y

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":spawnEscortShip called -- Escort Ship: " .. self.escortShip .. " Space Zone: " .. self.questZone .. " X: " .. x .. " Z: " .. z .. " Y: " .. y)
	end

	-- Spawn the ship to be escorted
	local pShipAgent = spawnShipAgent(self.escortShip, self.questZone, x, z, y)

	if (pShipAgent == nil) then
		self:failQuest(pPlayer, "true")

		CreatureObject(pPlayer):sendSystemMessage("Quest failed due to the escorting ship failing to spawn.")
		return
	end

	local agentID = SceneObject(pShipAgent):getObjectID()

	-- Set the agent as a mission object
	CreatureObject(pPlayer):addSpaceMissionObject(agentID, true)

	-- Set Fixed Patrol and escort flags
	ShipAiAgent(pShipAgent):setFixedPatrol()
	ShipAiAgent(pShipAgent):setEscort()

	ShipAiAgent(pShipAgent):setEscortSpeed(20)

	-- Set as same space faction
	ShipObject(pShipAgent):setShipFactionString(SpaceHelpers:getPlayerSpaceFactionString(pPlayer))

	-- Add kill observer
	createObserver(OBJECTDESTRUCTION, self.className, "notifyEscortShipDestroyed", pShipAgent)

	-- Assign the escort points
	createEvent(5 * 1000, self.className, "assignEscortPoints", pShipAgent, "")

	-- Write the playersID that is escorting
	writeData(agentID .. ":" .. self.className .. ":escorterID:", playerID)

	-- Write the starting point name
	writeStringData(agentID .. ":" .. self.className .. ":startingPoint:", self.escortPoints[randomStart].name)

	-- Write the ship agent that is being escorted by the player
	writeData(playerID .. ":" .. self.className .. ":escortID:", agentID)

	-- Write the escort ships progress
	writeData(agentID .. ":" .. self.className .. ":escortShipProgress:", #self.escortPoints)

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. " -- Escort Ship Spawned - Name: " .. ShipObject(pShipAgent):getShipName())
	end

	if (self.checkPlayerDistance) then
		-- Player needs to stay within 1000m. Members in group also count if they are in space as well
		createEvent(60 * 1000, self.className, "checkEscort", pShipAgent, "")
	end

	-- Player effect for player
	CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_spawn_escort.cef", "")

	-- Player escort arrival music
	CreatureObject(pPlayer):playMusicMessage("sound/mus_quest_escort_arrival.snd")

	-- Send Message to Players
	ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, "@spacequest/escort/" .. self.questName .. ":reason_" .. tostring(getRandomNumber(1, self.tauntData.tauntCount)))

	-- Schedule attack wave
	createEvent(self.attackDelay * 1000, self.className, "spawnAttackWave", pShipAgent, "")
end

function SpaceEscortScreenplay:assignEscortPoints(pShipAgent)
	if (pShipAgent == nil) then
		return
	end

	local agentID = SceneObject(pShipAgent):getObjectID()

	-- Get the starting point name so we do not re-use it when assigning
	local startingPointName = readStringData(agentID .. ":" .. self.className .. ":startingPoint:")
	deleteStringData(agentID .. ":" .. self.className .. ":startingPoint:")

	-- Add escort points randomly
	local escortPoints = self.escortPoints
	local totalPoints = 0

	while (#escortPoints > 0) do
		local randomPoint = getRandomNumber(1, #escortPoints)
		local pointName = escortPoints[randomPoint].name

		if (pointName ~= startingPointName) then
			-- Add the name escort points to the agent
			ShipAiAgent(pShipAgent):addFixedPatrolPoint(pointName)

			totalPoints = totalPoints + 1
		end

		-- Drop the point from the table
		table.remove(escortPoints, randomPoint)
	end

	writeData(agentID .. ":" .. self.className .. ":escortShipProgress:", totalPoints)
end

function SpaceEscortScreenplay:checkEscort(pShipAgent)
	if (pShipAgent == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed escort check due to null escort Ship.", LT_ERROR)
		return
	end

	local shipAgentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(shipAgentID .. ":" .. self.className .. ":escorterID:")

	local pPlayer = getSceneObject(playerID)

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":checkEscort -- Escort Ship: " .. ShipObject(pShipAgent):getShipName() .. " Escorting Player ID: " .. playerID)
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() or not SpaceHelpers:isSpaceQuestTaskActive(pPlayer, self.questType, self.questName, 2)) then
		createEvent(10 * 1000, self.className, "removeEscortShip", pShipAgent, "")
		return
	end

	-- Make sure player is in the zone
	if (SceneObject(pShipAgent):getZoneName() ~= SceneObject(pPlayer):getZoneName()) then
		self:failQuest(pPlayer, "true")
		createEvent(10 * 1000, self.className, "removeEscortShip", pShipAgent, "")
		return
	end

	local distance = SceneObject(pShipAgent):getDistanceTo3d(pPlayer)
	local warningCount = readData(playerID .. ":" .. self.className .. ":distanceWarnings:")
	deleteData(playerID .. ":" .. self.className .. ":distanceWarnings:")

	if (self.DEBUG_SPACE_ESCORT) then
		CreatureObject(pPlayer):sendSystemMessage("Escort checkup -- Escort Ship: " .. ShipObject(pShipAgent):getShipName() .. " Escorting Player: " .. SceneObject(pPlayer):getDisplayedName() .. " Current Distance: " .. distance .. " Warning Count: " .. warningCount)
	end

	-- Player is out of range
	if (distance > self.escortRange) then
		-- Player is outside of the escort range
		if (warningCount < 1) then
			warningCount = warningCount + 1

			ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, "@space/quest:escort_too_far1")

			-- Update Warning count
			writeData(playerID .. ":" .. self.className .. ":distanceWarnings:", warningCount)
		elseif (warningCount < 2) then
			warningCount = warningCount + 1

			ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, "@space/quest:escort_too_far2")

			-- Update Warning count
			writeData(playerID .. ":" .. self.className .. ":distanceWarnings:", warningCount)
		else
			ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, "@space/quest:escort_too_far3")

			self:failQuest(pPlayer, "true")

			createEvent(500, self.className, "removeEscortShip", pShipAgent, "")

			return
		end
	end

	createEvent(60 * 1000, self.className, "checkEscort", pShipAgent, "")
end

function SpaceEscortScreenplay:removeEscortShip(pShipAgent)
	if (pShipAgent == nil) then
		return
	end

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":removeEscortShip -- Escort Ship: " .. ShipObject(pShipAgent):getShipName())
	end

	-- Despawn the attack waves
	self:removeAttackShips(pShipAgent)

	-- Make ship fly away first
	ShipObject(pShipAgent):setHyperspacing(true);

	SceneObject(pShipAgent):setPosition(8000, 8000, 8000)

	local shipAgentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(shipAgentID .. ":" .. self.className .. ":escorterID:")
	deleteData(shipAgentID .. ":" .. self.className .. ":escorterID:")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer ~= nil) then
		-- Remove the agent a mission object
		CreatureObject(pPlayer):removeSpaceMissionObject(shipAgentID, true)
	end

	-- Remove the escort ship
	SceneObject(pShipAgent):destroyObjectFromWorld()
end

function SpaceEscortScreenplay:spawnAttackWave(pEscortAgent)
	if (pEscortAgent == nil or not self.spawnAttackWaves) then
		return
	end

	local playerID = readData(SceneObject(pEscortAgent):getObjectID() .. ":" .. self.className .. ":escorterID:")
	local pPlayer = getSceneObject(playerID)

	-- This will fail to spawn the scheduled wave if the escort is over
	if (pPlayer == nil or not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		return
	end

	-- Send attack alert message
	CreatureObject(pPlayer):sendSystemMessage("@spacequest/escort/" .. self.questName .. ":attack_notify")

	-- Player effect for player
	CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_spawn_wave.cef", "")

	local x = SceneObject(pEscortAgent):getPositionX()
	local z = SceneObject(pEscortAgent):getPositionZ()
	local y = SceneObject(pEscortAgent):getPositionY()
	local spawnZone = self.questZone

	local spawnTable = self.attackShips
	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

	local playerFactionHash = SpaceHelpers:getPlayerSpaceFactionHash(pPlayer)

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":spawnAttackWave -- Spawn Table Size: " .. #spawnTable .. " Spawn Zone: " .. spawnZone .. " Player Faction Hash: " .. playerFactionHash)
	end

	for i = 1, #spawnTable, 1 do
		local pShipAgent = spawnShipAgent(spawnTable[i], spawnZone, x + (getRandomNumber(200, 850) - getRandomNumber(200, 850)), z  + (getRandomNumber(200, 850) - getRandomNumber(200, 850)), y  + (getRandomNumber(200, 850) - getRandomNumber(200, 850)))

		if (pShipAgent == nil) then
			goto continue
		end

		-- Ship attacking the escort ship should be hyperspaced out and destroyed, just in case make sure they are cleaned up
		ShipAiAgent(pShipAgent):setDespawnOnNoPlayerInRange(true)

		-- Add players faction as enemy
		ShipAiAgent(pShipAgent):addSpaceFactionEnemy(playerFactionHash)

		-- Add kill observer
		createObserver(OBJECTDESTRUCTION, self.className, "notifyAttackShipDestroyed", pShipAgent)

		local agentID = SceneObject(pShipAgent):getObjectID()

		-- Set as space mission object
		CreatureObject(pPlayer):addSpaceMissionObject(agentID, (i == #spawnTable))

		-- Add to the list of shipIDs
		shipIDs[#shipIDs + 1] = agentID

		-- Write the playersID that is escorting
		writeData(agentID .. ":" .. self.className .. ":escorterID:", playerID)

		-- Add aggo and set the escort ship as ShipAgents Defender
		ShipAiAgent(pShipAgent):addAggro(pEscortAgent, 1)
		ShipAiAgent(pShipAgent):setDefender(pEscortAgent)

		::continue::
	end

	-- Store the Spawned Attack Ships
	writeStringVectorSharedMemory(playerID .. self.className .. ":attackShips:", shipIDs)

	-- Schedule next attack wave
	createEvent(self.attackDelay * 1000, self.className, "spawnAttackWave", pEscortAgent, "")
end


function SpaceEscortScreenplay:removeAttackShips(pShipAgent)
	if (pShipAgent == nil) then
		return
	end

	local agentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(agentID .. ":" .. self.className .. ":escorterID:")
	local pPlayer = getSceneObject(playerID)

	-- Delete the data
	deleteData(agentID .. ":" .. self.className .. ":escorterID:")

	-- Remove from Attack Ships Vector
	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

	for i = 1, #shipIDs, 1 do
		local attackAgentID = tonumber(shipIDs[i])

		-- Remove the attacking ship agent as a mission object
		if (pPlayer ~= nil) then
			CreatureObject(pPlayer):removeSpaceMissionObject(attackAgentID, true)
		end

		-- Get pointer to attack ship
		local pAttackShip = getSceneObject(attackAgentID)

		if (pAttackShip == nil) then
			goto continue
		end

		-- Make ship fly away first
		ShipObject(pAttackShip):setHyperspacing(true);

		SceneObject(pAttackShip):setPosition(8000, 8000, 8000)

		deleteData(SceneObject(pAttackShip):getObjectID() .. ":" .. self.className .. ":escorterID:")

		if (pPlayer ~= nil) then
			-- Remove the attacking ship agent as a mission object
			CreatureObject(pPlayer):removeSpaceMissionObject(attackAgentID, true)
		end

		-- Remove the escort ship
		SceneObject(pAttackShip):destroyObjectFromWorld()

		createEvent(2000, "SpaceHelpers", "delayedDestroyShipAgent", pAttackShip, "")

		::continue::
	end
end

--[[

		Space Escort Observers

--]]

function SpaceEscortScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
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

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":enteredZone called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Player Zone Hash: " .. zoneNameHash .. " questZone hash: " .. spaceQuestHash)
	end

	-- Player is in the correct zone
	if (zoneNameHash == spaceQuestHash and not SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, 0)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, 1)

		-- Setup the escort for the player
		self:setupEscort(pPlayer)

		return 0
	else
		createEvent(2000, self.className, "failQuest", pPlayer, "true")

		return 1
	end

	return 0
end

function SpaceEscortScreenplay:notifyEnteredQuestArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil)) then
		return 0
	end

	if (SceneObject(pShip):isPlayerShip()) then
		local pPilot = ShipObject(pShip):getPilot()

		if (pPilot == nil or not SceneObject(pPilot):isPlayerCreature()) then
			return 0
		end

		-- Player is not actively on this quest task
		if (not SpaceHelpers:isSpaceQuestTaskActive(pPilot, self.questType, self.questName, 2)) then
			return 0
		end

		if (self.DEBUG_SPACE_ESCORT) then
			print(self.className .. ":notifyEnteredQuestArea - Ship: " .. SceneObject(pShip):getDisplayedName() .. " entered SpaceActiveArea - X: " .. SceneObject(pActiveArea):getPositionX() .. " Z: " .. SceneObject(pActiveArea):getPositionZ() .. " Y: " .. SceneObject(pActiveArea):getPositionY() .. " Object Position - X: " .. SceneObject(pShip):getPositionX() .. " Z: " .. SceneObject(pShip):getPositionZ() .. " Y: " .. SceneObject(pShip):getPositionY())
		end

		local playerID = SceneObject(pPilot):getObjectID()
		local playerLocation = readData(playerID .. ":" .. self.className .. ":location:")

		-- Check to ensure player is arriving at the points in order
		if (playerLocation > 1) then
			return 0
		end

		-- Update player count
		writeData(playerID .. ":" .. self.className .. ":location:", 2)

		-- Send player arrival message
		local questUpdate = LuaStringIdChatParameter("@spacequest/escort/" .. self.questName .. ":quest_update")
		questUpdate:setTO("@spacequest/escort/" .. self.questName .. ":arrived_at_loc")

		CreatureObject(pPilot):sendSystemMessage(questUpdate:_getObject())

		-- Schedule escort ship spawning
		createEvent(getRandomNumber(5, 11) * 1000, self.className, "spawnEscortShip", pPilot, "")
	elseif (SceneObject(pShip):isShipAiAgent()) then
		-- Make Sure its the right type of ship
		if (ShipAiAgent(pShip):getShipAgentTemplateName() ~= self.escortShip) then
			return 0
		end

		local shipAgentID = SceneObject(pShip):getObjectID()
		local playerID = readData(shipAgentID .. ":" .. self.className .. ":escorterID:")

		-- The escort ship will be inside one of the active areas before it can be assigned the data to track its escorting player
		if (playerID == 0) then
			return 0
		end

		local pPlayer = getSceneObject(playerID)

		if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
			createEvent(1000, self.className, "removeEscortShip", pShip, "")
			return 0
		end

		if (self.DEBUG_SPACE_ESCORT) then
			print(self.className .. ":notifyEnteredQuestArea - Ship: " .. SceneObject(pShip):getDisplayedName() .. " entered SpaceActiveArea - X: " .. SceneObject(pActiveArea):getPositionX() .. " Z: " .. SceneObject(pActiveArea):getPositionZ() .. " Y: " .. SceneObject(pActiveArea):getPositionY() .. " Object Position - X: " .. SceneObject(pShip):getPositionX() .. " Z: " .. SceneObject(pShip):getPositionZ() .. " Y: " .. SceneObject(pShip):getPositionY())
		end

		local shipProgress = readData(shipAgentID .. ":" .. self.className .. ":escortShipProgress:")
		deleteData(shipAgentID .. ":" .. self.className .. ":escortShipProgress:")

		shipProgress = shipProgress - 1

		if (self.DEBUG_SPACE_ESCORT) then
			print(self.className .. " - Escort Ship Progress: " .. shipProgress)
		end

		-- Escort is complete
		if (shipProgress <= 0) then
			-- Send Thanks Message to Player
			ShipAiAgent(pShip):tauntPlayer(pPlayer, "@spacequest/escort/" .. self.questName .. ":thanks_" .. tostring(getRandomNumber(1, self.tauntData.thanksCount)))

			-- Hyperspace out escort ship with thanks message
			createEvent(500, self.className, "removeEscortShip", pShip, "")

			local questUpdate = LuaStringIdChatParameter("@spacequest/escort/" .. self.questName .. ":quest_update")
			questUpdate:setTO("@spacequest/escort/" .. self.questName .. ":complete")

			CreatureObject(pPlayer):sendSystemMessage(questUpdate:_getObject())

			-- Complete quest
			createEvent(1000, self.className, "completeQuest", pPlayer, "true")

			return 0
		end

		-- Write the escort ships progress
		writeData(shipAgentID .. ":" .. self.className .. ":escortShipProgress:", shipProgress)

		return 0
	end

	return 0
end

function SpaceEscortScreenplay:notifyEscortShipDestroyed(pShipAgent, pKillerShip)
	if (pShipAgent == nil) then
		return 1
	end

	local agentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(agentID .. ":" .. self.className .. ":escorterID:")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		Logger:log(self.className .. ":notifyEscortShipDestroyed - Quest Owner is nil.", LT_ERROR)
		return 1
	end

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":notifyEscortShipDestroyed - Ship Destoyed: " .. SceneObject(pShipAgent):getDisplayedName() .. " Quest Owner Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	-- Hyperspace out any remaining attack waves
	createEvent(200, self.className, "removeAttackShips", pShipAgent, "")

	-- Clean Up Data
	deleteData(agentID .. ":" .. self.className .. ":escortShipProgress:")

	if (SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		-- Escort Ship was Destroyed, fail the quest
		createEvent(500, self.className, "failQuest", pPlayer, "true")
	end

	return 1
end

function SpaceEscortScreenplay:notifyAttackShipDestroyed(pShipAgent, pKillerShip)
	if (pShipAgent == nil) then
		return 1
	end

	local agentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(agentID .. ":" .. self.className .. ":escorterID:")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		Logger:log(self.className .. ":notifyAttackShipDestroyed - Quest Owner is nil.", LT_ERROR)
		return 1
	end

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":notifyAttackShipDestroyed - Ship Destoyed: " .. SceneObject(pShipAgent):getDisplayedName() .. " Quest Owner Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	-- Remove as Mission Objects
	CreatureObject(pPlayer):removeSpaceMissionObject(agentID, true)

	-- Remove from Attack Ships Vector
	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
	local newIDs = {}

	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

	local index = 0

	for i = 1, #shipIDs, 1 do
		local shipID = tonumber(shipIDs[i])

		if (agentID ~= shipID) then
			newIDs[#newIDs + 1] = shipID
		end
	end

	if (#newIDs > 0) then
		-- Store the Spawned Attack Ships
		writeStringVectorSharedMemory(playerID .. self.className .. ":attackShips:", newIDs)

		local messageString = LuaStringIdChatParameter("@space/quest:destroy_duty_targets_remaining")
		messageString:setDI(#newIDs)

		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	else
		-- Send attack over message
		CreatureObject(pPlayer):sendSystemMessage("@spacequest/escort/" .. self.questName .. ":attack_stopped")

		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_wave.cef", "")
	end

	return 1
end