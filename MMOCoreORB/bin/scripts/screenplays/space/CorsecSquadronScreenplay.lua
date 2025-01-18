local Logger = require("utils.logger")

--[[

	Corsec Squadron Quests

]]

patrol_corellia_privateer_1 = SpacePatrolScreenplay:new {
	className = "patrol_corellia_privateer_1",

	questName = "corellia_privateer_1",
	questType = "patrol",

	questZone = "space_corellia",

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",
	sideQuestStart = 2, -- Patrol Point Number
	sideQuestDelay = 20, -- Time in seconds to wait to trigger side quest

	patrolPoints = {
		{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
		{zoneName = "space_corellia", x = -4540, z = -6023, y = -6111, patrolNumber = 2, radius = 150},
		{zoneName = "space_corellia", x = -2907, z = -4914, y = -5085, patrolNumber = 3, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_privateer_1", true)

destroy_surpriseattack_corellia_privateer_1 = SpaceSurpriseAttackScreenplay:new {
	className = "destroy_surpriseattack_corellia_privateer_1",

	questName = "corellia_privateer_1",
	questType = "destroy_surpriseattack",

	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",

	parentQuest = "patrol_corellia_privateer_1",
	parentQuestType = "patrol",
	completeParentTask = true,
	parentTaskToComplete = 2,

	surpriseAttackShips = {
		zone = "space_corellia",
		spawns = {{count = 1, shipName = "blacksun_fighter_s02_tier1"}, {count = 3, shipName = "blacksun_fighter_s01_tier1"}},
		total = 4,
	},
}

registerScreenPlay("destroy_surpriseattack_corellia_privateer_1", true)

destroy_corellia_privateer_2 = SpaceDestroyScreenplay:new {
	className = "destroy_corellia_privateer_2",

	questName = "corellia_privateer_2",
	questType = "destroy",

	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",

	killsRequired = 4,

	shipLocations = {
		{name = "black_sun_asteroid_1", x = 590, z = -3500, y = -6000},
		{name = "blacksun_asteroid_three_spawner", x = -6420, z = 6215, y = 6292},
		{name = "blacksun_asteroid_two_spawner", x = -5209, z = 6681, y = 6765},
		{name = "blacksun_deep_one_spawner", x = -5175, z = 5404, y = 6138},
		{name = "blacksun_fighter_five_spawner", x = -1894, z = 3873, y = 3360},
	},

	shipTypes = {
		"blacksun_ace_s04_tier1", "blacksun_ace_s04_tier2", "blacksun_aggressor_tier1", "blacksun_aggressor_tier2", "blacksun_bomber_ace_s04_tier1", "blacksun_bomber_ace_s04_tier2",
		"blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s02_tier1", "blacksun_bomber_s02_tier2", "blacksun_bomber_s03_tier1", "blacksun_bomber_s03_tier2",
		"blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier2", "blacksun_fighter_s03_tier1", "blacksun_fighter_s03_tier2",
		"blacksun_gunship_tier1", "blacksun_gunship_tier2", "blacksun_marauder_tier1", "blacksun_marauder_tier2", "blacksun_vehement_tier1", "blacksun_vehement_tier2", "blacksun_yt1300_tier1",
		"blacksun_yt1300_tier2", "blacksun_bomber_ace_tier3_dantooine", "blacksun_bomber_s01_tier2_tatooine", "blacksun_bomber_s02_tier3_dantooine", "blacksun_fighter_s01_tier2_tatooine",
		"blacksun_fighter_s02_tier3_dantooine",
	},
}

registerScreenPlay("destroy_corellia_privateer_2", true)

patrol_corellia_privateer_3 = SpacePatrolScreenplay:new {
	className = "patrol_corellia_privateer_3",

	questName = "corellia_privateer_3",
	questType = "patrol",

	questZone = "space_corellia",

	sideQuest = true,
	sideQuestType = "escort",
	sideQuestStart = 2,
	sideQuestDelay = 20, -- Time in seconds to wait to trigger side quest

	patrolPoints = {
		{zoneName = "space_corellia", x = 5549, z = -6501, y = -2720, patrolNumber = 1, radius = 150},
		{zoneName = "space_corellia", x = 1325, z = -6577, y = -3409, patrolNumber = 2, radius = 150},
		{zoneName = "space_corellia", x = -1514, z = -6488, y = -3864, patrolNumber = 3, radius = 150},
		{zoneName = "space_corellia", x = -5687, z = -6381, y = -4872, patrolNumber = 4, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_privateer_3", true)

escort_corellia_privateer_3 = SpaceEscortScreenplay:new {
	className = "escort_corellia_privateer_3",

	questName = "corellia_privateer_3",
	questType = "escort",

	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",

	escortShip = "freighterheavy_tier1",

	escortPoints = {
		{name = "privateer_security_escort_1", zoneName = "space_corellia", x = -5034, z = -5439, y = -4558, escortNumber = 1, radius = 150},
		{name = "privateer_security_escort_2", zoneName = "space_corellia", x = -2103, z = -5336, y = -5600, escortNumber = 2, radius = 150},
		{name = "privateer_security_escort_3", zoneName = "space_corellia", x = 1262, z = -5572, y = -5035, escortNumber = 3, radius = 150},
		{name = "privateer_security_escort_4", zoneName = "space_corellia", x = 5940, z = -5892, y = -4039, escortNumber = 4, radius = 150},
	},
}

registerScreenPlay("escort_corellia_privateer_3", true)

assassinate_corellia_privateer_tier1_4a = SpaceAssassinateScreenplay:new {
	className = "assassinate_corellia_privateer_tier1_4a",

	questType = "assassinate",
	questName = "corellia_privateer_tier1_4a",

	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",
}

registerScreenPlay("assassinate_corellia_privateer_tier1_4a", true)

--[[

	CorsecSquadronScreenplay

]]

CorsecSquadronScreenplay = ScreenPlay:new {
	screenplayName = "CorsecSquadronScreenplay",

	DEBUG_CORSEC = true, -- False before merge

	QUEST_STRING_1 = {type = "patrol", name = "corellia_privateer_1"},
	QUEST_STRING_1_SIDE = {type = "destroy_surpriseattack", name = "corellia_privateer_1"},
	QUEST_STRING_2 = {type = "destroy", name = "corellia_privateer_2"},
	QUEST_STRING_3 = {type = "patrol", name = "corellia_privateer_3"},
	QUEST_STRING_3_SIDE = {type = "escort", name = "corellia_privateer_3"},
	QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier1_4a"},
}

registerScreenPlay("CorsecSquadronScreenplay", false)

function CorsecSquadronScreenplay:start()
end

function CorsecSquadronScreenplay:resetRheaQuests(pPlayer)
	if (pPlayer == nil) then
		return
	end

	patrol_corellia_privateer_1:failQuest(pPlayer)
	destroy_surpriseattack_corellia_privateer_1:failQuest(pPlayer)
	destroy_corellia_privateer_2:failQuest(pPlayer)
	patrol_corellia_privateer_3:failQuest(pPlayer)
	--escort_corellia_privateer_3:failQuest(pPlayer)
	--assassinate_corellia_privateer_tier1_4a:failQuest(pPlayer)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 1)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 1)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, 1)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, 1)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, 1)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, 1)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, 1)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, 1)

	SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_4.type, self.QUEST_STRING_4.name, 1)
	SpaceHelpers:clearSpaceQuest(pPlayer, self.QUEST_STRING_4.type, self.QUEST_STRING_4.name, 1)

	if (self.DEBUG_CORSEC) then
		print("Testing - finished clearing Sgt Rhea Space Quests for Player: " .. SceneObject(pPlayer):getDisplayedName())
	end
end

function CorsecSquadronScreenplay:scheduleEscort(pPlayer)
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

	if (currentStep == self.ESCORT_3) then
		-- Send update message
		CreatureObject(pPlayer):sendSystemMessage("\\#pcontrast3CorSec Command: <\\#pcontrast1We have received a distress call from a Freighter, he's being chased by pirates. Help him out immediately!\\#pcontrast3>") -- "@spacequest/patrol/corellia_privateer_3:split_quest_alert")

		-- Active surpise attack side quest
		SpaceHelpers:activateSpaceQuest(pPlayer, nil, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, 1)
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, 0, 0)
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, 1, 0)

		--local attackShips = self.surpriseAttackShips.corellia_privateer_1

		-- Trigger surpise attack
		--SpaceHelpers:spawnSurpriseAttack(pPlayer, self.screenplayName, self.QUEST_STRING_1.name, attackShips)

		SpaceHelpers:clearQuestWaypoint(pPlayer)
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
		return 0
	end

	local pRootParent = SceneObject(pPlayer):getRootParent()

	if (pRootParent ~= nil and SceneObject(pRootParent):getObjectName() == "player_sorosuub_space_yacht") then
		return 0
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

	if (currentStep >= self.ACCEPTED_MISSION_3 and currentStep < self.FINISHED_MISSION_3) then
		-- Player is in the correct zone
		if (zoneNameHash == spaceCorelliaHash) then
			if (currentStep == self.ACCEPTED_MISSION_3) then
				-- Complete the quest task 1
				SpaceHelpers:completeSpaceQuestTask(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, 0, 0)

				-- Activate quest task 2
				SpaceHelpers:activateSpaceQuestTask(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, 2, 1)

				-- Update the players quest status
				setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_3_1)

				-- Add patrol point to the player
				local point1 = self.patrolPoints.corellia_privateer_3[1]
				local waypointID = PlayerObject(pGhost):addWaypoint(point1.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", point1.x, point1.z, point1.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

				local pWaypoint = getSceneObject(waypointID)

				if (pWaypoint ~= nil) then
					WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.QUEST_STRING_3.type .. "/" .. self.QUEST_STRING_3.name .. ":title_d")
				end

				setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)

				CreatureObject(pPlayer):sendSystemMessage("@space/quest:patrol_new_waypoint") -- "Patrol waypoint located."

				return 0

				-- Player failed the suprise attack, they have the chance to re-do the patrols and attack again
			elseif (currentStep == self.ESCORT_3) then
				-- Send update message
				CreatureObject(pPlayer):sendSystemMessage("@spacequest/escort/corellia_privateer_3:split_quest_alert_fail") -- "split_quest_alert_fail", "\\#pcontrast3 Sgt Rhea: < \\#pcontrast1 You appear to have hit a little snag out there Captain.  Get patched up and run the patrol route again. \\#pcontrast3 >");

				-- Set Quest failed
				SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, 1)

				-- Update the players quest status to start the patrols again
				setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_3_1)

				-- Add patrol point to the player
				local point1 = self.patrolPoints.corellia_privateer_3[1]
				local waypointID = PlayerObject(pGhost):addWaypoint(point1.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", point1.x, point1.z, point1.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

				local pWaypoint = getSceneObject(waypointID)

				if (pWaypoint ~= nil) then
					WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.QUEST_STRING_3.type .. "/" .. self.QUEST_STRING_3.name .. ":title_d")
				end

				setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)

				return 0
			end
		-- Player went to wrong zone, fail missions
		else
			-- Set Quest failed
			if (currentStep == self.ESCORT_3) then
				SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_3_SIDE.type, self.QUEST_STRING_3_SIDE.name, 0)
			end

			SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_3.type, self.QUEST_STRING_3.name, 1)

			-- Remove players quest status
			removeQuestStatus(playerID .. ":CorsecSquadron")

			-- Remove any patrol points
			SpaceHelpers:clearQuestWaypoint(pPlayer)

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

	local patrolPoint = {}
	local waypointID = 0
	local newQuestStatus = 0

	local questType = ""
	local questName = ""

	-- Quest 3 Patrol
	if (currentStep == self.PATROLLING_3_1) then
		-- Update the players quest status
		newQuestStatus = self.PATROLLING_3_2

		-- Add patrol point to the player
		patrolPoint = self.patrolPoints.corellia_privateer_3[2]
		waypointID = PlayerObject(pGhost):addWaypoint(patrolPoint.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", patrolPoint.x, patrolPoint.z, patrolPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

		questType = self.QUEST_STRING_3.type
		questName = self.QUEST_STRING_3.name

	elseif (currentStep == self.PATROLLING_3_2) then
		-- Update the players quest status
		newQuestStatus = self.ESCORT_3

		-- Add patrol point to the player
		patrolPoint = self.patrolPoints.corellia_privateer_3[3]
		waypointID = PlayerObject(pGhost):addWaypoint(patrolPoint.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", patrolPoint.x, patrolPoint.z, patrolPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

		questType = self.QUEST_STRING_3.type
		questName = self.QUEST_STRING_3.name

		-- Trigger Escort
		createEvent(20 * 1000, self.screenplayName, "scheduleEscort", pPilot, "")
	end

	if (waypointID > 0) then
		-- Update the players quest status
		setQuestStatus(playerID .. ":CorsecSquadron", newQuestStatus)

		-- Send Message for new patrol Point
		CreatureObject(pPilot):sendSystemMessage("@space/quest:patrol_new_waypoint") -- "Patrol waypoint located."

		local pWaypoint = getSceneObject(waypointID)

		if (pWaypoint ~= nil) then
			WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. questType .. "/" .. questName .. ":title_d")
		end

		setQuestStatus(playerID .. ":CorsecSquadron:waypointID", waypointID)
	end

	return 0
end
