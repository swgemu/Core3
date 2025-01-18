SpaceDestroyScreenplay = SpaceQuestLogic:new {
	className = "SpaceDestroyScreenplay",

	DEBUG_SPACE_DESTROY = false,

	killsRequired = 0,

	shipLocations = {},
	shipTypes = {},
}

registerScreenPlay("SpaceDestroyScreenplay", false)

--[[

		Space Destroy Quest Functions

--]]

function SpaceDestroyScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DESTROY) then
		print(self.className .. ":startQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, self.questType, self.questName, 1)

	-- Create inital observer for player entering Zone
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

function SpaceDestroyScreenplay:completeQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DESTROY) then
		print(self.className .. ":completeQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Activate the Journal Quest
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, 1)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)
end

function SpaceDestroyScreenplay:failQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DESTROY) then
		print(self.className .. ":failQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, 1)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoints(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	-- Remove Ship Destruction observer
	dropObserver(DESTROYEDSHIP, self.className, "notifyDestroyedShip", pPlayer)

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		-- Fail the parent quest
		SpaceHelpers:failSpaceQuest(pPlayer, self.parentQuestType, self.questName, 0)
	end
end

--[[

		Space Destroy Observers

--]]

function SpaceDestroyScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
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

	if (self.DEBUG_SPACE_DESTROY) then
		print(self.className .. ":enteredZone called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Player Zone Hash: " .. zoneNameHash .. " questZone hash: " .. spaceQuestHash)
	end

	-- Player is in the correct zone
	if (zoneNameHash == spaceQuestHash and not SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, 0)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, 1)

		-- Create Ship Destruction observer
		createObserver(DESTROYEDSHIP, self.className, "notifyDestroyedShip", pPlayer, 1)

		-- Give Waypoints for Spawns
		local waypointTable = self.shipLocations
		local waypointIDs = {}

		if (self.DEBUG_SPACE_DESTROY) then
			print(self.className .. " -- Waypoint table size: " .. #waypointTable)
		end

		for i = 1, #waypointTable, 1 do
			local point = waypointTable[i]

			local waypointID = PlayerObject(pGhost):addWaypoint(self.questZone, "@spacequest/destroy/" .. self.questName .. ":quest_destroy_t", "", point.x, point.z, point.y, WAYPOINT_SPACE, true, true, 0)

			if (waypointID > 0) then
				waypointIDs[#waypointIDs + 1] = tostring(waypointID)

				if (self.DEBUG_SPACE_DESTROY) then
					print(self.className .. " -- Waypoint Added #" .. i .. " ID: " .. waypointID)
				end

				local pWaypoint = getSceneObject(waypointID)

				if (pWaypoint ~= nil) then
					WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
				end
			end
		end

		writeStringVectorSharedMemory(playerID .. ":" .. self.className .. ":waypointVector", waypointIDs)

		return 0
	else
		self:failQuest(pPlayer)

		return 1
	end

	return 0
end

function SpaceDestroyScreenplay:notifyDestroyedShip(pPlayer, pShipAgent)
	if (pShipAgent == nil or not SceneObject(pShipAgent):isShipAiAgent()) then
		return 0
	end

	if (self.DEBUG_SPACE_DESTROY) then
		print(self.className .. ":notifyDestroyedShip -- Called for Destructed ShipAgent Object: " .. ShipObject(pShipAgent):getShipName() .. " Destructor: " .. SceneObject(pPlayer):getDisplayedName())
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	-- Check is kill task is active
	if (not SpaceHelpers:isSpaceQuestTaskActive(pPlayer, self.questType, self.questName, 1)) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local shipTempName = ShipAiAgent(pShipAgent):getShipAgentTemplateName()
	local checkShips = self.shipTypes
	local isValid = false

	if (self.DEBUG_SPACE_DESTROY) then
		print(self.className .. " -- Destructed Ship Template Name: " .. shipTempName)
	end

	for i = 1, #checkShips, 1 do
		if (shipTempName == checkShips[i]) then
			isValid = true
		end
	end

	local killCount = readData(playerID .. ":" .. self.className .. ":killCount")

	if (isValid) then
		killCount = killCount + 1
	end

	-- Kill counter sent to player
	CreatureObject(pPlayer):sendSystemMessage(killCount .. " Killed") -- "@quest/groundquests:destroy_counter"

	-- Check if player has enough kills
	if (killCount >= self.killsRequired) then
		-- Complete Task
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 1, 1)

		-- Remove kill count
		deleteData(playerID .. ":" .. self.className .. ":killCount")

		-- Drop the zone observer
		dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

		-- Clear Quest Waypoints
		SpaceHelpers:clearQuestWaypoints(pPlayer, self.className)

		return 1
	else
		writeData(playerID .. ":" .. self.className .. ":killCount", killCount)

		return 0
	end

	return 1
end
