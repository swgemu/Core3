local Logger = require("utils.logger")

--[[

	Corsec Squadron Quests

]]

--[[

patrol_corellia_privateer_1 = SpacePatrolScreenplay:new {
	questName = "corellia_privateer_1",
	questType = "patrol",

	questScreenplay = "CorsecSquadronScreenplay",
	questZone = "space_corellia",

	sideQuest = true,
	sideQuestType = "destroy_surpriseattack",

	patrolPoints = {
		{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
		{zoneName = "space_corellia", x = -4540, z = -6023, y = -6111, patrolNumber = 2, radius = 150},
		{zoneName = "space_corellia", x = -2907, z = -4914, y = -5085, patrolNumber = 3, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_privateer_1", false)

destroy_surpriseattack_corellia_privateer_1 = SpaceSurpriseAttackScreenplay:new {
	questName = "corellia_privateer_1",
	questType = "destroy_surpriseattack",

	questScreenplay = "CorsecSquadronScreenplay",
	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",
}

registerScreenPlay("destroy_surpriseattack_corellia_privateer_1", false)

destroy_corellia_privateer_2 = SpaceDestroyScreenplay:new {
	questName = "corellia_privateer_2",
	questType = "destroy",

	questScreenplay = "CorsecSquadronScreenplay",
	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",
}

registerScreenPlay("destroy_corellia_privateer_2", false)

patrol_corellia_privateer_3 = SpacePatrolScreenplay:new {
	questName = "corellia_privateer_3",
	questType = "patrol",

	questScreenplay = "CorsecSquadronScreenplay",
	questZone = "space_corellia",

	sideQuest = true,
	sideQuestType = "escort",

	patrolPoints = {
		{zoneName = "space_corellia", x = 5549, z = -6501, y = -2720, patrolNumber = 1, radius = 150},
		{zoneName = "space_corellia", x = 1325, z = -6577, y = -3409, patrolNumber = 2, radius = 150},
		{zoneName = "space_corellia", x = -1514, z = -6488, y = -3864, patrolNumber = 3, radius = 150},
		{zoneName = "space_corellia", x = -5687, z = -6381, y = -4872, patrolNumber = 4, radius = 150},
	},
}

registerScreenPlay("patrol_corellia_privateer_3", false)

escort_corellia_privateer_3 = SpaceEscortScreenplay:new {
	questName = "corellia_privateer_3",
	questType = "patrol",

	questScreenplay = "CorsecSquadronScreenplay",
	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",
}

registerScreenPlay("escort_corellia_privateer_3", false)

assassinate_corellia_privateer_tier1_4a = SpaceAssassinateScreenplay:new {
	questType = "assassinate",
	questName = "corellia_privateer_tier1_4a",

	questScreenplay = "CorsecSquadronScreenplay",
	questZone = "space_corellia",

	sideQuest = false,
	sideQuestType = "",
}

registerScreenPlay("assassinate_corellia_privateer_tier1_4a", false)

]]

--[[

	CorsecSquadronScreenplay

]]

CorsecSquadronScreenplay = ScreenPlay:new {
	screenplayName = "CorsecSquadronScreenplay",

	DEBUG_CORSEC = false, -- False before merge

	QUEST_STRING_1 = {type = "patrol", name = "corellia_privateer_1"},
	QUEST_STRING_1_SIDE = {type = "destroy_surpriseattack", name = "corellia_privateer_1"},
	QUEST_STRING_2 = {type = "destroy", name = "corellia_privateer_2"},
	QUEST_STRING_3 = {type = "patrol", name = "corellia_privateer_3"},
	QUEST_STRING_3_SIDE = {type = "escort", name = "corellia_privateer_3"},
	QUEST_STRING_4 = {type = "assassinate", name = "corellia_privateer_tier1_4a"},

	-- Quest Steps
	ACCEPTED_MISSION_1 = 1, -- corellia_privateer_1 -- Player needs to enter Corellia Space
	PATROLLING_1_1 = 2, -- Player is in Corellia Space and given first patrol waypoint
	PATROLLING_1_2 = 3, -- Player arrived at first point and is given second patrol waypoint
	PATROLLING_1_3 = 4, -- Player arrived at second point and is given third patrol waypoint
	ATTACK_1 = 5, -- Player enters side quest and is attacked by pirates, destroying them all completes patrol and side quest.
	FINISHED_MISSION_1 = 6, -- Player has finished side quest by killing pirates and is ready to return to Sgt Rhea.
	ACCEPTED_MISSION_2 = 7, -- corellia_privateer_2 -- Player needs to enter Corellia Space
	LOCATIONS_GIVEN_2 = 8, -- Player is in Corellia Space and given target location
	FINISHED_MISSION_2 = 9, -- Targets Destroyed
	ACCEPTED_MISSION_3 = 10, -- corellia_privateer_3 -- Player needs to enter Corellia Space
	PATROLLING_3_1 = 11, -- Player is in Corellia Space and given first patrol waypoint
	PATROLLING_3_2 = 12, -- Player arrived at first point and is given second patrol waypoint
	ESCORT_3 = 13, -- Player arrived at second point and is setup to escort a ship

	MISSION_2_KILLS = 4,

	-- Patrol Points
	patrolPoints = {
		corellia_privateer_1 = {
			{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, questStep = 2, radius = 150},
			{zoneName = "space_corellia", x = -4540, z = -6023, y = -6111, questStep = 3, radius = 150},
			{zoneName = "space_corellia", x = -2907, z = -4914, y = -5085, questStep = 4, radius = 150},
		},
		corellia_privateer_3 = {
			{zoneName = "space_corellia", x = 5549, z = -6501, y = -2720, questStep = 11, radius = 150},
			{zoneName = "space_corellia", x = 1325, z = -6577, y = -3409, questStep = 12, radius = 150},
			{zoneName = "space_corellia", x = -1514, z = -6488, y = -3864, questStep = 13, radius = 150},
			{zoneName = "space_corellia", x = -5687, z = -6381, y = -4872, questStep = 14, radius = 150},
		},
	},

	-- Surpise Attack Ships
	surpriseAttackShips = {
		corellia_privateer_1 = {zone = "space_corellia", spawns = {{count = 1, shipName = "blacksun_fighter_s02_tier1"}, {count = 3, shipName = "blacksun_fighter_s01_tier1"}}, total = 4},
	},

	locationsMission2 = {
		{name = "black_sun_asteroid_1", x = 590, z = -3500, y = -6000},
		{name = "blacksun_asteroid_three_spawner", x = -6420, z = 6215, y = 6292},
		{name = "blacksun_asteroid_two_spawner", x = -5209, z = 6681, y = 6765},
		{name = "blacksun_deep_one_spawner", x = -5175, z = 5404, y = 6138},
		{name = "blacksun_fighter_five_spawner", x = -1894, z = 3873, y = 3360},
	},

	shipsMission2 = {
		"blacksun_ace_s04_tier1", "blacksun_ace_s04_tier2", "blacksun_aggressor_tier1", "blacksun_aggressor_tier2", "blacksun_bomber_ace_s04_tier1", "blacksun_bomber_ace_s04_tier2",
		"blacksun_bomber_s01_tier1", "blacksun_bomber_s01_tier2", "blacksun_bomber_s02_tier1", "blacksun_bomber_s02_tier2", "blacksun_bomber_s03_tier1", "blacksun_bomber_s03_tier2",
		"blacksun_fighter_s01_tier1", "blacksun_fighter_s01_tier2", "blacksun_fighter_s02_tier1", "blacksun_fighter_s02_tier2", "blacksun_fighter_s03_tier1", "blacksun_fighter_s03_tier2",
		"blacksun_gunship_tier1", "blacksun_gunship_tier2", "blacksun_marauder_tier1", "blacksun_marauder_tier2", "blacksun_vehement_tier1", "blacksun_vehement_tier2", "blacksun_yt1300_tier1",
		"blacksun_yt1300_tier2", "blacksun_bomber_ace_tier3_dantooine", "blacksun_bomber_s01_tier2_tatooine", "blacksun_bomber_s02_tier3_dantooine", "blacksun_fighter_s01_tier2_tatooine",
		"blacksun_fighter_s02_tier3_dantooine",
	},
}

registerScreenPlay("CorsecSquadronScreenplay", false)

function CorsecSquadronScreenplay:start()

end

function CorsecSquadronScreenplay:clearQuestWaypoint(pPlayer)
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

function CorsecSquadronScreenplay:clearQuestWaypoints(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local waypointTable = readStringVectorSharedMemory(playerID .. ":CorsecSquadron:waypointVector:")

	for i = 1, #waypointTable, 1 do
		local waypointID = tonumber(waypointTable[i])

		-- Clear the waypoint from the player object
		PlayerObject(pGhost):removeWaypoint(waypointID, true)
	end

	-- Clear the waypointID vector
	deleteStringVectorSharedMemory(playerID .. ":CorsecSquadron:waypointVector:")
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
	self:clearQuestWaypoint(pPlayer)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, "CorsecSquadronScreenplay", "enteredZone", pPlayer)

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
		CreatureObject(pPlayer):sendSystemMessage("\\#pcontrast3 Tactical Computer: <\\#pcontrast1Pirate wing detected.  They are moving to attack!\\#pcontrast3") -- "@spacequest/patrol/corellia_privateer_1:split_quest_alert")

		local surpriseAttackName = self.QUEST_STRING_1_SIDE.name

		-- Active surpise attack side quest
		SpaceHelpers:activateSpaceQuest(pPlayer, nil, self.QUEST_STRING_1_SIDE.type, surpriseAttackName, 1)

		local attackShips = self.surpriseAttackShips.corellia_privateer_1

		-- Trigger surpise attack
		SpaceHelpers:spawnSurpriseAttack(pPlayer, self.screenplayName, self.QUEST_STRING_1.name, attackShips)
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

		self.clearQuestWaypoint(pPlayer)
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

	-- First Quest - Patrol
	if (currentStep >= self.ACCEPTED_MISSION_1 and currentStep < self.FINISHED_MISSION_1) then
		-- Player is in the correct zone
		if (zoneNameHash == spaceCorelliaHash) then
			if (currentStep == self.ACCEPTED_MISSION_1) then
				-- Complete the quest task 1
				SpaceHelpers:completeSpaceQuestTask(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 0, 0)

				-- Activate quest task 2
				SpaceHelpers:activateSpaceQuestTask(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 2, 1)

				-- Update the players quest status
				setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_1_1)

				-- Add patrol point to the player
				local point1 = self.patrolPoints.corellia_privateer_1[1]
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
				setQuestStatus(playerID .. ":CorsecSquadron", self.PATROLLING_1_1)

				-- Add patrol point to the player
				local point1 = self.patrolPoints.corellia_privateer_1[1]
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
			self:clearQuestWaypoint(pPlayer)

			return 1
		end
	elseif (currentStep >= self.ACCEPTED_MISSION_2 and currentStep < self.FINISHED_MISSION_2) then
		if (zoneNameHash == spaceCorelliaHash and currentStep == self.ACCEPTED_MISSION_2) then
			-- Complete the quest task 0
			SpaceHelpers:completeSpaceQuestTask(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, 0, 0)

			-- Activate quest task 1
			SpaceHelpers:activateSpaceQuestTask(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, 1, 1)

			-- Remove players quest status
			setQuestStatus(playerID .. ":CorsecSquadron", self.LOCATIONS_GIVEN_2)

			-- Create Ship Destruction observer
			createObserver(DESTROYEDSHIP, "CorsecSquadronScreenplay", "notifyDestroyedShip", pPlayer, 1)

			-- Give Waypoints for Spawns
			local waypointTable = self.locationsMission2
			local waypointIDs = {}

			if (self.DEBUG_CORSEC) then
				print("Waypoint table size: " .. #waypointTable)
			end

			for i = 1, #waypointTable, 1 do
				local point = waypointTable[i]

				local waypointID = PlayerObject(pGhost):addWaypoint("space_corellia", "@spacequest/destroy/corellia_privateer_2:quest_destroy_t", "", point.x, point.z, point.y, WAYPOINT_SPACE, true, true, 0)

				if (waypointID > 0) then
					waypointIDs[#waypointIDs + 1] = tostring(waypointID)

					if (self.DEBUG_CORSEC) then
						print("Waypoint Added #" .. i .. " ID: " .. waypointID)
					end

					local pWaypoint = getSceneObject(waypointID)

					if (pWaypoint ~= nil) then
						WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.QUEST_STRING_2.type .. "/" .. self.QUEST_STRING_2.name .. ":title_d")
					end
				end
			end

			writeStringVectorSharedMemory(playerID .. ":CorsecSquadron:waypointVector:", waypointIDs)

			return 0
		-- Fail mission
		else
			SpaceHelpers:failSpaceQuest(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, 1)

			-- Remove players quest status
			setQuestStatus(playerID .. ":CorsecSquadron", self.ACCEPTED_MISSION_2)

			-- Remove any patrol points
			self:clearQuestWaypoints(pPlayer)

			-- Remove the zone entry observer
			dropObserver(DESTROYEDSHIP, "CorsecSquadronScreenplay", "notifyDestroyedShip", pPlayer)

			return 1
		end
	elseif (currentStep >= self.ACCEPTED_MISSION_3 and currentStep < self.FINISHED_MISSION_3) then
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
			self:clearQuestWaypoint(pPlayer)

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

	-- 1st Patrol point
	if (currentStep == self.PATROLLING_1_1) then
		-- Update the players quest status
		newQuestStatus = self.PATROLLING_1_2

		-- Add patrol point to the player
		patrolPoint = self.patrolPoints.corellia_privateer_1[2]
		waypointID = PlayerObject(pGhost):addWaypoint(patrolPoint.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", patrolPoint.x, patrolPoint.z, patrolPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

		questType = self.QUEST_STRING_1.type
		questName = self.QUEST_STRING_1.name
	-- 2nd Patrol Point
	elseif (currentStep == self.PATROLLING_1_2) then
		-- Update the players quest status
		newQuestStatus = self.ATTACK_1

		-- Add 3rd patrol point to the player
		patrolPoint = self.patrolPoints.corellia_privateer_1[3]
		waypointID = PlayerObject(pGhost):addWaypoint(patrolPoint.zoneName, "@spacequest/patrol/corellia_privateer_3:quest_patrol_t", "", patrolPoint.x, patrolPoint.z, patrolPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

		questType = self.QUEST_STRING_1.type
		questName = self.QUEST_STRING_1.name

		-- Trigger Surpise attack
		createEvent(20 * 1000, self.screenplayName, "schedulePatrolAttack", pPilot, "")

	-- 3rd/Final Patrol Point
	--elseif (currentStep == self.PATROLLING_1_3) then
		-- Player never hits patrol 3
	-- Quest 3 Patrol
	elseif (currentStep == self.PATROLLING_3_1) then
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

function CorsecSquadronScreenplay:notifyShipDestroyed(pShipAgent, pKillerShip)
	if (pShipAgent == nil) then
		return 1
	end

	local playerID = readData(SceneObject(pShipAgent):getObjectID() .. ":QuestOwner")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		Logger:log("CorsecSquadronScreenplay:notifyShipDestroyed - Quest Owner is nil.", LT_ERROR)
		return 1
	end

	if (self.DEBUG_CORSEC) then
		print("notifyShipDestroyed - Ship Destoyed: " .. SceneObject(pShipAgent):getDisplayedName() .. " Quest Owner Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 1
	end

	local stepString = getQuestStatus(playerID .. ":CorsecSquadron")

	if (stepString == nil) then
		return 1
	end

	local currentStep = tonumber(stepString)

	if (self.DEBUG_CORSEC) then
		print("notifyShipDestroyed - Player Quest Step: " .. currentStep)
	end

	-- Quest 1 Surprise attack
	if (currentStep == self.ATTACK_1) then
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
			self:clearQuestWaypoint(pPlayer)

			-- Complete quest for surprise attack
			SpaceHelpers:completeSpaceQuest(pPlayer, self.QUEST_STRING_1_SIDE.type, self.QUEST_STRING_1_SIDE.name, 1)

			-- Complete the patrol quest task 2
			SpaceHelpers:completeSpaceQuestTask(pPlayer, self.QUEST_STRING_1.type, self.QUEST_STRING_1.name, 2, 0)

			-- Update the players quest status
			setQuestStatus(playerID .. ":CorsecSquadron", self.FINISHED_MISSION_1)

			-- Remove the zone entry observer
			dropObserver(ZONESWITCHED, "CorsecSquadronScreenplay", "enteredZone", pPlayer)

			CreatureObject(pPlayer):sendSystemMessage("@spacequest/destroy_surpriseattack/corellia_privateer_1:complete") -- "\\#pcontrast3 CorSec Command: < \\#pcontrast1 Well done! Return to your superior for your next assignment by travelling to the Corellian Space Station and using /comm. \\#pcontrast3 >"
		end
	end

	return 1
end

function CorsecSquadronScreenplay:notifyDestroyedShip(pPlayer, pShipAgent)
	if (pShipAgent == nil or not SceneObject(pShipAgent):isShipAiAgent()) then
		return 0
	end

	if (self.DEBUG_CORSEC) then
		print("CorsecSquadronScreenplay:notifyDestroyedShip -- Called for Destructed ShipAgent Object: " .. ShipObject(pShipAgent):getShipName() .. " Destructor: " .. SceneObject(pPlayer):getDisplayedName())
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local stepString = getQuestStatus(playerID .. ":CorsecSquadron")

	if (stepString == nil) then
		return 1
	end

	local currentStep = tonumber(stepString)

	if (self.DEBUG_CORSEC) then
		print("notifyDestroyedShip -- Current Quest Step: " .. currentStep)
	end

	if (currentStep == self.LOCATIONS_GIVEN_2) then
		local shipTempName = ShipAiAgent(pShipAgent):getShipAgentTemplateName()
		local checkShips = self.shipsMission2
		local isValid = false

		if (self.DEBUG_CORSEC) then
			print("notifyDestroyedShip -- Destructed Ship Template Name: " .. shipTempName)
		end

		for i = 1, #checkShips, 1 do
			if (shipTempName == checkShips[i]) then
				isValid = true
			end
		end

		local killCount = readData(playerID .. ":CorsecSquadron:killCount")

		if (isValid) then
			killCount = killCount + 1
		end

		-- Kill counter sent to player
		CreatureObject(pPlayer):sendSystemMessage(killCount .. " Killed") -- "@quest/groundquests:destroy_counter"

		-- Check if player has enough kills
		if (killCount >= self.MISSION_2_KILLS) then
			-- Update the players quest status
			setQuestStatus(playerID .. ":CorsecSquadron", self.FINISHED_MISSION_2)

			-- Complete Task
			SpaceHelpers:completeSpaceQuestTask(pPlayer, self.QUEST_STRING_2.type, self.QUEST_STRING_2.name, 1, 1)

			-- Remove
			deleteData(playerID .. ":CorsecSquadron:killCount")

			-- Drop the zone observer
			dropObserver(ZONESWITCHED, "CorsecSquadronScreenplay", "enteredZone", pPlayer)

			-- Clear Quest Waypoints
			self:clearQuestWaypoints(pPlayer)

			return 1
		else
			writeData(playerID .. ":CorsecSquadron:killCount", killCount)

			return 0
		end
	end

	return 1
end