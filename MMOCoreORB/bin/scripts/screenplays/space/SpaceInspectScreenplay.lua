SpaceInspectScreenplay = SpaceQuestLogic:new {
	className = "SpaceInspectScreenplay",

	questName = "",
	questType = "",

	questZone = "",

	creditReward = 0,
	itemReward = {
		--{species = {}, item = ""},
	},

	sideQuest = false,
	sideQuestType = "",

	DEBUG_SPACE_INSPECT = false,

	-- Screenplay Specific Variables

	inspectTargets = {},
	inspectCargo = "",

	targetLocation = {},
}

registerScreenPlay("SpaceInspectScreenplay", false)

--[[

		Space Inspect Quest Functions

--]]

function SpaceInspectScreenplay:start()
end

function SpaceInspectScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_INSPECT) then
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
	if (playerZoneHash == spaceQuestHash and not SpaceHelpers:isInYacht(pPlayer)) then
		-- Activate the quest task 0
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Setup the inspection for the player
		createEvent(1000, self.className, "setupInspection", pPlayer, "")
	end

	-- Create inital observer for player entering Zone and to handle failing quest
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

function SpaceInspectScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_INSPECT) then
		print(self.className .. ":completeQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	-- Complete the Journal Quest
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove any target waypoints
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	if (self.sideQuest and (self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.COMPLETION or self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.BIDIRECTIONAL)) then
		local alertMessage = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":split_quest_alert"

		-- Split Quest Alert
		createEvent(self.sideQuestDelay * 1000, "SpaceHelpers", "sendQuestAlert", pPlayer, alertMessage)

		-- Trigger Sidequest
		createEvent(self.sideQuestDelay * 1050, self.sideQuestType .. "_" .. self.sideQuestName, "startQuest", pPlayer, "")
	end
end

function SpaceInspectScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_INSPECT) then
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

	-- Remove the zone entry and inspect observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)
	dropObserver(INSPECTEDSHIP, self.className, "inspectedShip", pPlayer)
	dropObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.parentQuestName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.sideQuestName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.sideQuestName, "failQuest", pPlayer, "false")
	end

	if (self.sideQuest and (self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.FAILURE or self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.BIDIRECTIONAL)) then
		local alertMessage = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":split_quest_alert"

		-- Split Quest Alert
		createEvent(self.sideQuestDelay * 1000, "SpaceHelpers", "sendQuestAlert", pPlayer, alertMessage)

		-- Trigger Sidequest
		createEvent(self.sideQuestDelay * 1050, self.sideFailQuestType .. "_" .. self.sideFailQuestName, "startQuest", pPlayer, "")
	end
end

function SpaceInspectScreenplay:resetQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to resetQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_INSPECT) then
		print(self.className .. ":resetQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, false)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry and inspect observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)
	dropObserver(INSPECTEDSHIP, self.className, "inspectedShip", pPlayer)
	dropObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)
end

function SpaceInspectScreenplay:setupInspection(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		self:failQuest(pPlayer, "true")
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local inspectionLocation = self.targetLocation

	-- Give inspecion waypoint
	local waypointID = PlayerObject(pGhost):addWaypoint(self.questZone, "@spacequest/inspect/" .. self.questName .. ":quest_location_t", "", inspectionLocation.x, inspectionLocation.z, inspectionLocation.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":quest_location_d")
	end

	-- Store the waypointID on the player
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	-- Complete task 0
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

	-- Activate the quest task 1
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, true)

	if (not hasObserver(INSPECTEDSHIP, self.className, "inspectedShip", pPlayer)) then
		createObserver(INSPECTEDSHIP, self.className, "inspectedShip", pPlayer, 1)
	end
end

function SpaceInspectScreenplay:veryifyShipTargetAndCargo(pTargetShip, cargoHashString)
	if (pTargetShip == nil) then
		return false
	end

	local isValid = false

	local targetShipName = ShipAiAgent(pTargetShip):getShipAgentTemplateName()

	if (self.DEBUG_SPACE_INSPECT) then
		print(self.className .. ":veryifyShipTarget called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Target Ship Name: " .. targetShipName .. " cargoHash: " .. cargoHashString)
	end

	local inspectTargets = self.inspectTargets

	for i = 1, #inspectTargets, 1 do
		local targetShip = inspectTargets[i]

		if (targetShipName ~= targetShip) then
			goto continue
		end

		isValid = true

		::continue::
	end

	local targetCargoHash = getHashCode(self.inspectCargo)
	local cargoHash = tonumber(cargoHashString)

	if (self.DEBUG_SPACE_INSPECT) then
		print(self.className .. ":veryifyShipTarget called -- Target Cargo Hash: " .. targetCargoHash)
	end

	if (not isValid or targetCargoHash ~= cargoHash) then
		return false
	end

	if (self.DEBUG_SPACE_INSPECT) then
		print(self.className .. ":veryifyShipTarget called -- Returning true")
	end

	return true
end

--[[

		Space Inspect Observers

--]]

function SpaceInspectScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
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

	if (self.DEBUG_SPACE_INSPECT) then
		print(self.className .. ":enteredZone called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Player Zone Hash: " .. zoneNameHash .. " questZone hash: " .. spaceQuestHash)
	end

	-- Player is in the correct zone
	if (zoneNameHash == spaceQuestHash and not SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		-- Activate the quest task 0
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Setup the inspection for the player
		createEvent(1000, self.className, "setupInspection", pPlayer, "")

		return 0
	elseif (zoneNameHash ~= spaceQuestHash and SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		createEvent(2000, self.className, "failQuest", pPlayer, "true")

		return 1
	end

	return 0
end

function SpaceInspectScreenplay:inspectedShip(pPlayer, pTargetShip, cargoHash)
	if (pPlayer == nil or pTargetShip == nil) then
		return 1
	end

	if (self.DEBUG_SPACE_INSPECT) then
		print(self.className .. ":inspectedShip called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	if (not self:veryifyShipTargetAndCargo(pTargetShip, cargoHash)) then
		return 0
	end

	-- Complete task 1
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 1, false)

	-- Activate the quest task 2
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 2, true)

	SpaceHelpers:sendQuestUpdate(pPlayer, "@space/quest:inspect_found_cargo") -- "\\#00ff00 This is the cargo you're looking for. Use the '/dock' command to retrieve it! \\#pcontrast3"

	-- Create observer for the player docking with the ship
	if (not hasObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)) then
		createObserver(SHIPDOCKED, self.className, "dockedShip", pPlayer)
	end

	return 1
end

function SpaceInspectScreenplay:dockedShip(pPlayer, pTargetShip, cargoHash)
	if (pPlayer == nil or pTargetShip == nil) then
		return 1
	end

	local targetShipName = SceneObject(pTargetShip):getObjectName()

	if (self.DEBUG_SPACE_INSPECT) then
		print(self.className .. ":inspectedShip called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	if (not self:veryifyShipTargetAndCargo(pTargetShip, cargoHash)) then
		return 0
	end

	-- Complete task 2
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 2, false)

	-- Send quest update for retrieval of cargo
	SpaceHelpers:sendQuestUpdate(pPlayer, "@space/quest:inspect_recovered_cargo") -- "You recovered the cargo!"

	-- Complete the quest
	createEvent(1000, self.className, "completeQuest", pPlayer, "true")

	return 1
end
