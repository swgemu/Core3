SpaceEscortScreenplay = SpaceQuestLogic:new {
	className = "SpaceEscortScreenplay",

	DEBUG_SPACE_ESCORT = true,

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
	SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, self.questType, self.questName, 1)

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
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, 1)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	if (self.completeParentTask) then
		-- Complete the parent quest task
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.parentQuestType, self.questName, self.parentTaskToComplete, 0)
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

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		-- Fail the parent quest
		SpaceHelpers:failSpaceQuest(pPlayer, self.parentQuestType, self.questName, 0)
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
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, 0)

	-- Activate quest task 2
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 2, 1)

	-- Add escort point to the player
	local escortPoint = self.escortPoints[1]
	local waypointID = PlayerObject(pGhost):addWaypoint(escortPoint.zoneName, "Escort Rendevous", "Escort Rendevous", escortPoint.x, escortPoint.z, escortPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
	end

	-- Store the waypointID on the player
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	-- Quest Update Message
	local questMessage = LuaStringIdChatParameter("@spacequest/escort/" .. self.questName .. ":quest_update")
	questMessage:setTO("@spacequest/escort/" .. self.questName .. ":found_loc") -- "Meet the convoy at the following location."

	-- Send player the message
	CreatureObject(pPlayer):sendSystemMessage(questMessage:_getObject())
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
		if (i == 1) then
			createObserver(ENTEREDAREA, self.className, "notifyEnteredStartingArea", pQuestArea)
		else
			createObserver(ENTEREDAREA, self.className, "notifyEnteredEscortArea", pQuestArea)
		end

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

	local x = self.escortPoints[1].x
	local z = self.escortPoints[1].z
	local y = self.escortPoints[1].y

	local playerDirection = {}
	local playerRoot = SceneObject(pPlayer):getRootParent()

	if (playerRoot ~= nil) then
		playerDirection = SceneObject(playerRoot):getDirection()
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	--TODO: Add method to spawn ship behind player based on direction

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

	-- Set ship flag on agent
	ShipAiAgent(pShipAgent):setFixedPatrol()

	local agentID = SceneObject(pShipAgent):getObjectID()

	-- Write the playersID that is escorting
	writeData(agentID .. ":" .. self.className .. ":escorterID:", playerID)

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
	playClientEffectLoc(playerID, "clienteffect/ui_quest_spawn_escort.cef", self.questZone, x, z, y, 0)

	-- Send Message to Players
	ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, "@spacequest/escort/" .. self.questName .. ":reason_1")
end

function SpaceEscortScreenplay:assignEscortPoints(pShipAgent)
	if (pShipAgent == nil) then
		return
	end

	-- Forum post mentioned randomized points?

	-- Add escort points
	local escortPoints = self.escortPoints

	-- Start at the second escort point, we are already at the first
	for i = 2, #escortPoints, 1 do
		local pointName = escortPoints[i].name

		-- Add the name escort points to th agent
		ShipAiAgent(pShipAgent):addFixedPatrolPoint(pointName)
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
		deleteData(shipAgentID .. ":" .. self.className .. ":escorterID:")
		return
	end

	-- Player is not actively on this quest task
	if (not SpaceHelpers:isSpaceQuestTaskActive(pPlayer, self.questType, self.questName, 2)) then
		return 0
	end


	CreatureObject(pPlayer):sendSystemMessage("Escort checkup")


	-- Make sure player is still in range of ship being escorted
	if (not SceneObject(pShipAgent):isInRangeWithObject(pPlayer, 1000)) then
		self:failQuest(pPlayer)

		-- Send Abort Message to Players
		ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, "@spacequest/escort/" .. self.questName .. ":abort")

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



	-- Make ship fly away first??


	SceneObject(pShipAgent):destroyObjectFromWorld()
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

function SpaceEscortScreenplay:notifyEnteredStartingArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil) or (not SceneObject(pShip):isPlayerShip())) then
		return 0
	end

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":notifyEnteredStartingArea - Ship: " .. SceneObject(pShip):getDisplayedName() .. " entered SpaceActiveArea - X: " .. SceneObject(pActiveArea):getPositionX() .. " Z: " .. SceneObject(pActiveArea):getPositionZ() .. " Y: " .. SceneObject(pActiveArea):getPositionY() .. " Object Position - X: " .. SceneObject(pShip):getPositionX() .. " Z: " .. SceneObject(pShip):getPositionZ() .. " Y: " .. SceneObject(pShip):getPositionY())
	end

	local pPilot = LuaShipObject(pShip):getPilot()

	if (pPilot == nil or not SceneObject(pPilot):isPlayerCreature()) then
		return 0
	end

	-- Player is not actively on this quest task
	if (not SpaceHelpers:isSpaceQuestTaskActive(pPilot, self.questType, self.questName, 2)) then
		return 0
	end

	local pGhost = CreatureObject(pPilot):getPlayerObject()

	if (pGhost == nil) then
		return 0
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
	CreatureObject(pPilot):sendSystemMessage("@spacequest/escort/" .. self.questName .. ":arrived_at_loc")

	-- Player esort music
	CreatureObject(pPilot):playMusicMessage("sound/mus_quest_escort_arrival.snd")

	-- Schedule escort ship spawning
	createEvent(getRandomNumber(5, 10), self.className, "spawnEscortShip", pPilot, "")

	return 0
end

function SpaceEscortScreenplay:notifyEnteredEscortArea(pActiveArea, pShipAgent)
	if ((pActiveArea == nil) or (pShipAgent == nil) or (not SceneObject(pShipAgent):isShipAiAgent())) then
		return 0
	end

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":notifyEnteredEscortArea - Ship: " .. SceneObject(pShipAgent):getDisplayedName() .. " entered SpaceActiveArea - X: " .. SceneObject(pActiveArea):getPositionX() .. " Z: " .. SceneObject(pActiveArea):getPositionZ() .. " Y: " .. SceneObject(pActiveArea):getPositionY() .. " Object Position - X: " .. SceneObject(pShipAgent):getPositionX() .. " Z: " .. SceneObject(pShipAgent):getPositionZ() .. " Y: " .. SceneObject(pShipAgent):getPositionY())
	end

	local shipAgentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(shipAgentID .. ":" .. self.className .. ":escorterID:")

	local pPlayer = getSceneObject(playerID)

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":checkEscort -- Escort Ship: " .. ShipObject(pShipAgent):getShipName() .. " Escorting Player ID: " .. playerID)
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		deleteData(shipAgentID .. ":" .. self.className .. ":escorterID:")
		return 0
	end



	CreatureObject(pPlayer):sendSystemMessage("Arriving at Escort Point!")




	return 0
end
