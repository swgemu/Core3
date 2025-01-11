local Logger = require("utils.logger")

CorsecSquadronScreenplay = ScreenPlay:new {
	screenplayName = "CorsecSquadronScreenplay",

	DEBUG_CORSEC = true,

	QUEST_STRING_1 = {type = "patrol", name = "corellia_privateer_1"},
	QUEST_STRING_1_SIDE = {type = "destroy_surpriseattack", name = "corellia_privateer_1"},
	QUEST_STRING_2 = {type = "destroy", name = "corellia_privateer_2"},
	QUEST_STRING_3 = {type = "patrol", name = "corellia_privateer_3"},
	QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier1_4a"},

	-- Quest Steps
	ACCEPTED_MISSION_1 = 1, -- corellia_privateer_1 -- Task 1 - Player needs to enter Corellia Space
	PATROLLING_1 = 2, -- corellia_privateer_1 -- Task 2 - Player is in Space Corellia and given first patrol waypoint
	PATROLLING_2 = 3,
	PATROLLING_3 = 4,
	ATTACK_1 = 5,
	FINISHED_MISSION_1 = 6,

	-- Patrol Points
	patrolPoints = {
		{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, questStep = 2, radius = 250},
		{zoneName = "space_corellia", x = -4540, z = -6023, y = -6111, questStep = 3, radius = 250},
		{zoneName = "space_corellia", x = -2907, z = -4914, y = -5085, questStep = 4, radius = 250},
	},

	-- Surpise Attack Ships
	surpriseAttackShips = {
		corellia_privateer_1 = {zone = "space_corellia", spawns = {{count = 1, shipName = "blacksun_fighter_s02_tier1"}, {count = 3, shipName = "blacksun_fighter_s01_tier1"}}, total = 4},
	},
}

registerScreenPlay("CorsecSquadronScreenplay", true)

function CorsecSquadronScreenplay:start()
	self:spawnActiveAreas()
end

function CorsecSquadronScreenplay:spawnActiveAreas()
	local areasTable = self.patrolPoints
	local totalAreas = #areasTable

	if (totalAreas < 1) then
		return
	end

	for i = 1, totalAreas, 1 do
		local zoneName = areasTable[i].zoneName
		local x = areasTable[i].x
		local z = areasTable[i].z
		local y = areasTable[i].y
		local questStep = areasTable[i].questStep

		if (not isZoneEnabled(zoneName)) then
			goto skip
		end

		local pQuestArea = spawnSpaceActiveArea(zoneName, "object/space_active_area.iff", x, z, y, areasTable[i].radius)

		if pQuestArea == nil then
			Logger:log("CorsecSquadronScreenplay: pQuestArea is nil.", LT_ERROR)
			return
		end

		local questAreaID = SceneObject(pQuestArea):getObjectID()

		-- Write the quest step to the quest area
		writeData(questAreaID .. ":QuestStep", questStep)

		-- Add Entry Observer for ships
		createObserver(ENTEREDAREA, self.screenplayName, "notifyEnteredQuestArea", pQuestArea)

		::skip::
	end
end

function CorsecSquadronScreenplay:clearPatrolWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local waypointID = tonumber(getQuestStatus(playerID .. ":CorsecSquadron:waypointID"))

	-- Clear the waypointID and waypoint off the player
	removeQuestStatus(playerID .. ":CorsecSquadron:waypointID")

	-- Clear the waypoint from the player object
	PlayerObject(pGhost):removeWaypoint(waypointID, true)
end

function CorsecSquadronScreenplay:resetRheaQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	removeQuestStatus(SceneObject(pPlayer):getObjectID() .. ":CorsecSquadron")
	self:clearPatrolWaypoint(pPlayer)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, "CorsecSquadronScreenplay", "enteredZone", pPlayer)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 1)
	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, 1)
	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, 1)
	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, 1)
	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_4.type, self.QUEST_STRING_4.name, 1)

	print("finished clearing")
end

function CorsecSquadronScreenplay:schedulePatrolAttack(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local currentStep = getQuestStatus(playerID .. ":CorsecSquadron")

	if (currentStep == nil) then
		currentStep = 0
	else
		currentStep = tonumber(currentStep)
	end

	if (currentStep == self.ATTACK_1) then
		-- Send update message
		CreatureObject(pPlayer):sendSystemMessage("@spacequest/patrol/corellia_privateer_1:split_quest_alert") -- "\\#pcontrast3 Tactical Computer: <\\#pcontrast1Pirate wing detected.  They are moving to attack!\\#pcontrast3>"

		local surpriseAttackName = self.QUEST_STRING_1_SIDE.name

		-- Active surpise attack side quest
		SpaceHelpers:activateSpaceQuest(pPlayer, nil, self.QUEST_STRING_1_SIDE.type, surpriseAttackName, 1)

		local attackShips = self.surpriseAttackShips.corellia_privateer_1

		-- Trigger surpise attack
		SpaceHelpers:spawnSurpriseAttack(pPlayer, self.QUEST_STRING_1.name, attackShips)
	end
end

--[[

		Observers

--]]

function CorsecSquadronScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
	if (pPlayer == nil) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local currentStep = getQuestStatus(playerID .. ":CorsecSquadron")
	local spaceCorelliaHash = getHashCode("space_corellia")

	if (currentStep == nil) then
		currentStep = 0
	else
		currentStep = tonumber(currentStep)
	end

	if (self.DEBUG_CORSEC) then
		print("CorsecSquadronScreenplay:enteredZone called -- Current Quest Step: " .. currentStep .. " Zone Hash: " .. zoneNameHash .. " space_corellia: " .. spaceCorelliaHash)
	end

	-- First Quest - Patrol
	if (currentStep >= self.ACCEPTED_MISSION_1 or currentStep < self.FINISHED_MISSION_1) then
		-- Player is in the correct zone
		if (zoneNameHash == spaceCorelliaHash) then
			if (currentStep == self.ACCEPTED_MISSION_1) then
				-- Complete the quest task 1
				SpaceHelpers:completeSpaceQuestTask(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 0, 0)

				-- Activate quest task 2
				SpaceHelpers:activateSpaceQuestTask(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 2, 1)

				-- Update the players quest status
				setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_1)

				-- Add patrol point to the player
				local point1 = self.patrolPoints[1]
				local waypointID = PlayerObject(pGhost):addWaypoint(point1.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", point1.x, point1.z, point1.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

				local pWaypoint = getSceneObject(waypointID)

				if (pWaypoint ~= nil) then
					WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.QUEST_STRING_1.type .. "/" .. self.QUEST_STRING_1.name .. ":title_d")
				end

				setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)

				CreatureObject(pPlayer):sendSystemMessage("@space/quest:patrol_new_waypoint") -- "Patrol waypoint located."

				return 0
			-- Player failed the suprise attack, they have the chance to re-do the patrols and attack again
			elseif (currentStep == self.ATTACK_1) then
				-- Send update message
				CreatureObject(pPlayer):sendSystemMessage("@spacequest/destroy_surpriseattack/corellia_privateer_1:split_quest_alert_fail") -- "\\#pcontrast3 Sgt Rhea: < \\#pcontrast1 You appear to have hit a little snag out there Captain.  Get patched up and run the patrol route again. \\#pcontrast3 >"

				-- Set Quest failed
				SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, 1)

				-- Update the players quest status to start the patrols again
				setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_1)

				-- Add patrol point to the player
				local point1 = self.patrolPoints[1]
				local waypointID = PlayerObject(pGhost):addWaypoint(point1.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", point1.x, point1.z, point1.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

				local pWaypoint = getSceneObject(waypointID)

				if (pWaypoint ~= nil) then
					WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.QUEST_STRING_1.type .. "/" .. self.QUEST_STRING_1.name .. ":title_d")
				end

				setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)

				return 0
			end
		-- Player went to wrong zone, fail missions
		else
			-- Set Quest failed
			if (currentStep == self.ATTACK_1) then
				SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, 0)
			end

			SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 1)

			-- Remove players quest status
			removeQuestStatus(playerID .. ":CorsecSquadron")

			-- Remove any patrol points
			self:clearPatrolWaypoint(pPlayer)

			return 1
		end
	end

	return 1
end

function CorsecSquadronScreenplay:notifyEnteredQuestArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil) or (not SceneObject(pShip):isPlayerShip())) then
		return 0
	end

	if (self.DEBUG_CORSEC) then
		print("notifyEnteredQuestArea - Ship: " .. SceneObject(pShip):getDisplayedName() .. " entered SpaceActiveArea - X: " .. SceneObject(pActiveArea):getPositionX() .. " Z: " .. SceneObject(pActiveArea):getPositionZ() .. " Y: " .. SceneObject(pActiveArea):getPositionY() .. " Object Position - X: " .. SceneObject(pShip):getPositionX() .. " Z: " .. SceneObject(pShip):getPositionZ() .. " Y: " .. SceneObject(pShip):getPositionY())
	end

	local pPilot = LuaShipObject(pShip):getPilot()

	if (pPilot == nil or not SceneObject(pPilot):isPlayerCreature()) then
		return 0
	end

	local pGhost = CreatureObject(pPilot):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local playerID = SceneObject(pPilot):getObjectID()
	local stepString = getQuestStatus(playerID .. ":CorsecSquadron")

	if (stepString == nil) then
		return 0
	end

	CreatureObject(pPilot):sendSystemMessage("@space/quest:patrol_waypoint_arrived") -- "You have arrived at a patrol nav point."

	local currentStep = tonumber(stepString)
	local waypointID = tonumber(getQuestStatus(playerID .. ":CorsecSquadron:waypointID"))

	if (self.DEBUG_CORSEC) then
		print("Player Pilot: " .. SceneObject(pPilot):getDisplayedName() .. " Current Quest Step: " .. currentStep .. " WaypointID: " .. waypointID)
	end

	-- Clear the waypointID and waypoint off the player
	removeQuestStatus(playerID .. ":CorsecSquadron:waypointID")
	PlayerObject(pGhost):removeWaypoint(waypointID, true)

	-- 1st Patrol point
	if (currentStep == self.PATROLLING_1) then
		-- Update the players quest status
		setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_2)

		CreatureObject(pPilot):sendSystemMessage("@space/quest:patrol_new_waypoint") -- "Patrol waypoint located."

		-- Add patrol point to the player
		local point2 = self.patrolPoints[2]
		local waypointID = PlayerObject(pGhost):addWaypoint(point2.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", point2.x, point2.z, point2.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

		local pWaypoint = getSceneObject(waypointID)

		if (pWaypoint ~= nil) then
			WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.QUEST_STRING_1.type .. "/" .. self.QUEST_STRING_1.name .. ":title_d")
		end

		setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)
	-- 2nd Patrol Point
	elseif (currentStep == self.PATROLLING_2) then
		-- Update the players quest status
		setQuestStatus(playerID .. ":CorsecSquadron", self.ATTACK_1)

		CreatureObject(pPilot):sendSystemMessage("@space/quest:patrol_new_waypoint") -- "Patrol waypoint located."

		-- Add 3rd patrol point to the player
		local point3 = self.patrolPoints[3]
		local waypointID = PlayerObject(pGhost):addWaypoint(point3.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", point3.x, point3.z, point3.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

		local pWaypoint = getSceneObject(waypointID)

		if (pWaypoint ~= nil) then
			WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.QUEST_STRING_1.type .. "/" .. self.QUEST_STRING_1.name .. ":title_d")
		end

		setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)

		-- Trigger Surpise attack
		createEvent(20 * 1000, self.screenplayName, "schedulePatrolAttack", pPilot, "")

	-- 3rd/Final Patrol Point
	--elseif (currentStep == self.PATROLLING_3) then
		-- Player never hits patrol 3
	end

	return 0
end

function CorsecSquadronScreenplay:notifyShipDestroyed(pShip, pPlayer)
	if (pPlayer == nil or pShip == nil) then
		return 1
	end

	if (self.DEBUG_CORSEC) then
		print("Ship Drestoyed: " .. SceneObject(pShip):getDisplayedName() .. " Player Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	local pGhost = CreatureObject(pPilot):getPlayerObject()

	if (pGhost == nil) then
		return 1
	end

	local playerID = SceneObject(pPilot):getObjectID()
	local stepString = getQuestStatus(playerID .. ":CorsecSquadron")

	if (stepString == nil) then
		return 1
	end

	local currentStep = tonumber(stepString)

	-- Quest 1 Surprise attack
	if (currentsStep == self.ATTACK_1) then
		local totalString = readData(playerID .. "corellia_privateer_1:SurpriseAttackCount")

		-- Clear the old kill count off the player
		deleteData(playerID .. "corellia_privateer_1:SurpriseAttackCount")

		local spawnCount = tonumber(totalString)
		spawnCount = spawnCount - 1

		-- Kill counter sent to player
		CreatureObject(pPlayer):sendSystemMessage(self.surpriseAttackShips.corellia_privateer_1.total - spawnCount .. " Killed") -- "@quest/groundquests:destroy_counter"

		if (spawnCount > 0) then
			-- Update the remaining count
			writeData(playerID .. "corellia_privateer_1:SurpriseAttackCount", spawnCount)
		else
			-- Remove the 3rd waypoint, the player does not have to complete this
			self:clearPatrolWaypoint(pPilot)

			-- Complete quest for surprise attack
			SpaceHelpers:completeSpaceQuest(pPilot, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, 1)

			-- Complete the patrol quest task 2
			SpaceHelpers:completeSpaceQuestTask(pPilot, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 2, 0)

			-- Update the players quest status
			setQuestStatus(playerID .. ":CorsecSquadron", self.FINISHED_MISSION_1)

			-- Remove the zone entry observer
			dropObserver(ZONESWITCHED, "CorsecSquadronScreenplay", "enteredZone", pPilot)

			CreatureObject(pPilot):sendSystemMessage("@spacequest/destroy_surpriseattack/corellia_privateer_1:complete") -- "\\#pcontrast3 CorSec Command: < \\#pcontrast1 Well done! Return to your superior for your next assignment by travelling to the Corellian Space Station and using /comm. \\#pcontrast3 >"
		end
	end


	return 1
end