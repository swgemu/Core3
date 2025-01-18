SpaceEscortScreenplay = SpaceQuestLogic:new {
	className = "SpaceEscortScreenplay",

	DEBUG_SPACE_ESCORT = true,

	escortRange = 1000,
	escortShip = "",

	escortPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	checkPlayerDistance = true,
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

function SpaceEscortScreenplay:completeQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":completeQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Activate the Journal Quest
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, false)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	if (self.completeParent) then
		-- Complete the parent quest
		createEvent(100, self.parentQuestType .. "_" .. self.questName, "completeQuest", pPlayer, "")
	end
end

function SpaceEscortScreenplay:failQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":failQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, 1)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Delete the stored escorted ship ID
	deleteData(playerID .. ":" .. self.className .. ":escortID:")

	-- Delete player location data
	deleteData(playerID .. ":" .. self.className .. ":location:")

	-- Delete Start point
	deleteData(playerID .. self.className .. ":startPoint:")

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "")
	end
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

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":setupEscort called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
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

	local playerID = SceneObject(pPlayer):getObjectID()

	local randomStart = readData(playerID .. self.className .. ":startPoint:")
	deleteData(playerID .. self.className .. ":startPoint:")

	local x = self.escortPoints[randomStart].x
	local z = self.escortPoints[randomStart].z
	local y = self.escortPoints[randomStart].y

	local playerDirection = {}
	local playerRoot = SceneObject(pPlayer):getRootParent()

	if (playerRoot ~= nil) then
		playerDirection = SceneObject(playerRoot):getDirection()
	end

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":spawnEscortShip called -- Escort Ship: " .. self.escortShip .. " Space Zone: " .. self.questZone .. " X: " .. x .. " Z: " .. z .. " Y: " .. y)
		print("Player Direction: w = " .. playerDirection[1] .. " x = " .. playerDirection[2] .. " y = " .. playerDirection[3] .. " z = " .. playerDirection[4])
	end

	-- Spawn the ship to be escorted
	local pShipAgent = spawnShipAgent(self.escortShip, self.questZone, x, z + 20, y)

	if (pShipAgent == nil) then
		self:failQuest(pPlayer)

		CreatureObject(pPlayer):sendSystemMessage("Quest failed due to the escorting ship failing to spawn.")
		return
	end

	local agentID = SceneObject(pShipAgent):getObjectID()

	-- Set the agent a mission object
	CreatureObject(pPlayer):addMissionCriticalObject(agentID, true)

	-- Set ship flag on agent
	ShipAiAgent(pShipAgent):setFixedPatrol()

	-- Write the playersID that is escorting
	writeData(agentID .. ":" .. self.className .. ":escorterID:", playerID)

	-- Write the starting point name
	writeStringData(agentID .. ":" .. self.className .. ":startingPoint:", self.escortPoints[randomStart].name)

	-- Write the ship agent that is being escorted by the player
	writeData(playerID .. ":" .. self.className .. ":escortID:", agentID)

	-- Assign the escort points
	createEvent(10 * 1000, self.className, "assignEscortPoints", pShipAgent, "")

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
	createEvent(getRandomNumber(5, 10), self.className, "spawnAttackWave", pShipAgent, "")
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

	while (#escortPoints > 0) do
		local randomPoint = getRandomNumber(1, #escortPoints)
		local pointName = escortPoints[randomPoint].name

		if (pointName ~= startingPointName) then
			-- Add the name escort points to the agent
			ShipAiAgent(pShipAgent):addFixedPatrolPoint(pointName)
		end

		-- Drop the point from the table
		table.remove(escortPoints, randomPoint)
	end
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

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		createEvent(10 * 1000, self.className, "removeEscortShip", pShipAgent, "")

		return
	end

	-- Player is not actively on this quest task
	if (not SpaceHelpers:isSpaceQuestTaskActive(pPlayer, self.questType, self.questName, 2)) then
		createEvent(10 * 1000, self.className, "removeEscortShip", pShipAgent, "")

		return 0
	end

	if (self.DEBUG_SPACE_ESCORT) then
		CreatureObject(pPlayer):sendSystemMessage("Escort checkup")
	end

	-- Make sure player is in the zone and still in range of ship being escorted
	if ((SceneObject(pShipAgent):getZoneName() ~= SceneObject(pPlayer):getZoneName()) or not SceneObject(pShipAgent):isInRangeWithObject(pPlayer, self.escortRange)) then
		self:failQuest(pPlayer)

		createEvent(10 * 1000, self.className, "removeEscortShip", pShipAgent, "")

		return
	end

	-- Reschedule the check
	createEvent(60 * 1000, self.className, "checkEscort", pShipAgent, "")
end

function SpaceEscortScreenplay:removeEscortShip(pShipAgent)
	if (pShipAgent == nil) then
		return
	end

	-- Make ship fly away first
	ShipObject(pShipAgent):setHyperspacing(true);

	SceneObject(pShipAgent):setPosition(8000, 8000, 8000)

	local shipAgentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(shipAgentID .. ":" .. self.className .. ":escorterID:")
	deleteData(shipAgentID .. ":" .. self.className .. ":escorterID:")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer ~= nil) then
		-- Remove the agent a mission object
		CreatureObject(pPlayer):removeMissionCriticalObject(shipAgentID)
	end

	-- Remove the escort ship
	SceneObject(pShipAgent):destroyObjectFromWorld()
end

function SpaceEscortScreenplay:spawnAttackWave(pShipAgent)
	if (pShipAgent == nil) then
		return
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
		self:failQuest(pPlayer)

		return 1
	end

	return 0
end

function SpaceEscortScreenplay:notifyEnteredQuestArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil)) then
		return 0
	end

	-- Player is not actively on this quest task
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

		-- Remove the old waypoint from player
		SpaceHelpers:clearQuestWaypoint(pPilot, self.className)

		-- Send player arrival message
		local questUpdate = LuaStringIdChatParameter("@spacequest/escort/" .. self.questName .. ":quest_update")
		questUpdate:setTO("@spacequest/escort/" .. self.questName .. ":arrived_at_loc")
	
		CreatureObject(pPilot):sendSystemMessage(questUpdate:_getObject())

		-- Schedule escort ship spawning
		createEvent(getRandomNumber(5, 10), self.className, "spawnEscortShip", pPilot, "")
	elseif (SceneObject(pShip):isShipAiAgent()) then
		local shipAgentID = SceneObject(pShip):getObjectID()
		local playerID = readData(shipAgentID .. ":" .. self.className .. ":escorterID:")
	
		local pPlayer = getSceneObject(playerID)
	
		if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
			createEvent(1000, self.className, "removeEscortShip", pShipAgent, "")

			return 0
		end

		if (self.DEBUG_SPACE_ESCORT) then
			print(self.className .. ":notifyEnteredQuestArea - Ship: " .. SceneObject(pShip):getDisplayedName() .. " entered SpaceActiveArea - X: " .. SceneObject(pActiveArea):getPositionX() .. " Z: " .. SceneObject(pActiveArea):getPositionZ() .. " Y: " .. SceneObject(pActiveArea):getPositionY() .. " Object Position - X: " .. SceneObject(pShip):getPositionX() .. " Z: " .. SceneObject(pShip):getPositionZ() .. " Y: " .. SceneObject(pShip):getPositionY())
		end
	
		-- TODO: continue quest logic here
	
		CreatureObject(pPlayer):sendSystemMessage("Arriving at Escort Point!")


		return 0
	end

	return 0
end
