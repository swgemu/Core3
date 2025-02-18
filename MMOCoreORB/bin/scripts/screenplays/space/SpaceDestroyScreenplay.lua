SpaceDestroyScreenplay = SpaceQuestLogic:new {
	className = "SpaceDestroyScreenplay",

	questName = "",
	questType = "",

	questZone = "",

	creditReward = 0,
	itemReward = {
		--{species = {}, item = ""},
	},

	DEBUG_SPACE_DESTROY = false,

	dutyMission = false,

	sideQuest = false,
	sideQuestType = "",
	sideQuestStart = 0, -- Kill Number
	sideQuestDelay = 0, -- Time in seconds to wait to trigger side quest

	parentQuest = "",
	parentQuestType = "", -- Quest type of parent quest, used for completing tasks

	-- Screenplay Specific Variables
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

function SpaceDestroyScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DESTROY) then
		print(self.className .. ":completeQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	-- Activate the Journal Quest
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)
end

function SpaceDestroyScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DESTROY) then
		print(self.className .. ":failQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoints(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	-- Remove Ship Destruction observer
	dropObserver(DESTROYEDSHIP, self.className, "notifyDestroyedShip", pPlayer)

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
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
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, false)

		-- Create Ship Destruction observer
		createObserver(DESTROYEDSHIP, self.className, "notifyDestroyedShip", pPlayer, true)

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

		-- Quest update message
		SpaceHelpers:sendQuestUpdate(pPlayer, #waypointTable .. " waypoint(s) to possible destroy target locations have been added to your datapad.") -- "destroy_target_waypoints"

		-- Player effect for player
		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_waypoint_target.cef", "")
	elseif (not hasObserver(DESTROYEDSHIP, self.className, "notifyDestroyedShip", pPlayer)) then
		self:failQuest(pPlayer, "true")
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

	if (not isValid) then
		return 0
	end

	local killCount = readData(playerID .. ":" .. self.className .. ":killCount")

	-- Increase kill count
	killCount = killCount + 1

	-- Check if player has enough kills
	if (killCount >= self.killsRequired) then
		-- Complete Task
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 1, false)

		-- Remove kill count
		deleteData(playerID .. ":" .. self.className .. ":killCount")

		-- Clear Quest Waypoints
		SpaceHelpers:clearQuestWaypoints(pPlayer, self.className)

		-- Player effect for player
		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_all.cef", "")

		-- Complete the quest
		createEvent(200, self.className, "completeQuest", pPlayer, "true")

		return 1
	end

	if (killCount == 1) then
		SpaceHelpers:sendQuestProgess(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":title")
	end

	-- Kill counter sent to player
	SpaceHelpers:sendQuestUpdate(pPlayer, self.killsRequired - killCount .. " targets remaining to be destroyed.") --  "destroy_remainder_update"

	writeData(playerID .. ":" .. self.className .. ":killCount", killCount)

	return 0
end
