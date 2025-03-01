SpaceDutyDestroyScreenplay = SpaceQuestLogic:new {
	className = "SpaceDutyDestroyScreenplay",

	questName = "",
	questType = "",

	questZone = "",

	creditReward = 0,
	itemReward = {
		--{species = {}, item = ""},
	},

	DEBUG_SPACE_DUTY_DESTROY = true,

	dutyMission = false,

	sideQuest = false,
	sideQuestType = "",
	sideQuestStart = 0, -- Kill Number
	sideQuestDelay = 0, -- Time in seconds to wait to trigger side quest

	parentQuest = "",
	parentQuestType = "", -- Quest type of parent quest, used for completing tasks

	-- Screenplay Specific Variables
	totalLevels = 0, -- Amount of levels a player has to complete to finish mission
	totalRounds = 0, -- Total Rounds for each of the levels
	totalWaves = 0, -- Total waves at each location that is not the boss ship

	bossShip = "",
	shipTypes = {},
}

registerScreenPlay("SpaceDutyDestroyScreenplay", false)

--[[

		Space Duty Destroy Quest Functions

--]]

function SpaceDutyDestroyScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":startQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Activate the Journal Quest
	SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, self.questType, self.questName, false)

	local spaceQuestHash = getHashCode(self.questZone)
	local zoneName = SceneObject(pPlayer):getZoneName()
	local playerZoneHash = getHashCode(zoneName)
	local pRootParent = SceneObject(pPlayer):getRootParent()

	-- Check if the player is in the proper zone already
	if (playerZoneHash == spaceQuestHash and pRootParent ~= nil and SceneObject(pRootParent):getObjectName() ~= "player_sorosuub_space_yacht") then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, true)

		-- Quest Progress Update
		SpaceHelpers:sendQuestProgess(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":title")

		-- Find a target location
		self:getTargetLocation(pPlayer)
	end

	-- Create inital observer for player entering Zone
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

function SpaceDutyDestroyScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
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

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Destroy the active area
	local areaID = writeData(playerID .. ":" .. self.className .. ":targetArea:", questAreaID)
	deleteData(playerID .. ":" .. self.className .. ":targetArea:")

	local pQuestArea = getSceneObject(areaID)

	if (pQuestArea ~= nil and SceneObject(pQuestArea):isActiveArea()) then
		dropObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pQuestArea)

		destroyObjectFromWorld(pQuestArea)
	end

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end
end

function SpaceDutyDestroyScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":completeQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	-- Activate the Journal Quest
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Clear Quest Waypoint
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Destroy the active area
	local areaID = writeData(playerID .. ":" .. self.className .. ":targetArea:", questAreaID)
	deleteData(playerID .. ":" .. self.className .. ":targetArea:")

	local pQuestArea = getSceneObject(areaID)

	if (pQuestArea ~= nil and SceneObject(pQuestArea):isActiveArea()) then
		dropObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pQuestArea)

		destroyObjectFromWorld(pQuestArea)
	end
end

function SpaceDutyDestroyScreenplay:getTargetLocation(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		self:failQuest(pPlayer, "true")
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local x = SceneObject(pPlayer):getWorldPositionX()
	local z = SceneObject(pPlayer):getWorldPositionZ()
	local y = SceneObject(pPlayer):getWorldPositionY()

	local randomLocation = SpaceHelpers:getRandomPositionInSphere(x, z, y, 1000, 1400)

	-- Spawn Active Area
	local pQuestArea = spawnSpaceActiveArea(self.questZone, "object/space_active_area.iff", randomLocation.x, randomLocation.z, randomLocation.y, 200)

	if pQuestArea == nil then
		Logger:log(self.className .. ":getTargetLocation -- pQuestArea is nil.", LT_ERROR)
		return
	end

	local questAreaID = SceneObject(pQuestArea):getObjectID()

	-- Write the target location ID
	writeData(playerID .. ":" .. self.className .. ":targetArea:", questAreaID)

	-- Add Entry Observer for ships
	createObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pQuestArea)

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":getTargetLocation - Area Spawned ID: " .. questAreaID)
	end

	-- Give Waypoint for Target
	local waypointID = PlayerObject(pGhost):addWaypoint(self.questZone, "@spacequest/destroy_duty/" .. self.questName .. ":quest_destroy_t", "", randomLocation.x, randomLocation.z, randomLocation.y, WAYPOINT_SPACE, true, true, 0)

	if (waypointID <= 0) then
		return
	end

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. " -- Waypoint Added ID: " .. waypointID)
	end

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
	end

	-- Store the waypointID on the player
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	-- Player effect for player
	CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_waypoint_target.cef", "")
end

function SpaceDutyDestroyScreenplay:spawnAttackWave(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local currentWave = readData(playerID .. ":" .. self.className .. ":currentWave:")

	-- Spawn Boss Wave
	if (currentWave >= self.totalWaves) then


		-- Add kill observer
		-- createObserver(OBJECTDESTRUCTION, self.className, "notifyShipDestroyed", pPrimaryAgent)

	-- Spawn regular attack wave
	else





	end

end

--[[

		Space Duty Destroy Observers

--]]

function SpaceDutyDestroyScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
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

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":enteredZone called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Player Zone Hash: " .. zoneNameHash .. " questZone hash: " .. spaceQuestHash)
	end

	-- Player is in the correct zone
	if (zoneNameHash == spaceQuestHash and not SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, false)

		-- Quest Progress Update
		SpaceHelpers:sendQuestProgess(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":title")

		-- Find a target location
		createEvent(2000, self.className, "getTargetLocation", pPlayer, "")
	else
		self:failQuest(pPlayer, "true")
	end

	return 0
end

function SpaceDutyDestroyScreenplay:notifyEnteredQuestArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil)) then
		return 0
	end

	if (not SceneObject(pShip):isPlayerShip()) then
		return 0
	end

	local pPilot = ShipObject(pShip):getPilot()

	if (pPilot == nil or not SceneObject(pPilot):isPlayerCreature()) then
		return 0
	end

	local playerID = SceneObject(pPilot):getObjectID()
	local areaID = SceneObject(pActiveArea):getObjectID()
	local playerAreaID = readData(playerID .. ":" .. self.className .. ":targetArea:")

	if (playerAreaID <= 0 or areaID ~= playerAreaID) then
		return
	end

	-- Spawn wave
	createEvent(4000, self.className, "spawnAttackWave", pPilot, "")

	return 1
end

function SpaceDutyDestroyScreenplay:notifyShipDestroyed(pShipAgent, pKillerShip)
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

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":notifyShipDestroyed - Ship Destoyed: " .. SceneObject(pShipAgent):getDisplayedName() .. " Quest Owner Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 1
	end


	-- Handle destuction + wave counts






	return 1
end

