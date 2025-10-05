SpaceDutyDestroyScreenplay = SpaceQuestLogic:new {
	className = "SpaceDutyDestroyScreenplay",

	questName = "",
	questType = "",

	questZone = "",

	creditReward = 0,
	itemReward = {
		--{species = {}, item = ""},
	},

	DEBUG_SPACE_DUTY_DESTROY = false,

	dutyMission = false,

	sideQuest = false,
	sideQuestType = "",
	sideQuestPatrolStart = 0,
	sideQuestDelay = 0, -- Time in seconds to wait to trigger side quest

	parentQuest = "",
	parentQuestType = "", -- Quest type of parent quest, used for completing tasks

	-- Screenplay Specific Variables
	totalLevels = 0, -- Amount of levels a player has to complete to finish mission
	totalRounds = 0, -- Total Rounds for each of the levels
	totalWaves = 0, -- Total waves at each location

	minDistance = 2500, -- Minimum distance away for new location
	maxDistance = 5000, -- Maximum distance away for new location

	bossShip = "",

	-- Table of ship tables
	shipTypes = {
		{},
	},
}

registerScreenPlay("SpaceDutyDestroyScreenplay", false)

--[[
		Space Duty Destroy Quest Functions

		- Each Round has multiple waves. Defined as: totalWaves
		- Once all of the waves are eliminated, the round increments. Defined as: totalRounds
		- After all rounds are completed a boss ship is spawned.
		- Once the boss is killed, the level is complete and increments for the total amount of levels. Defined as: totalLevels
--]]

function SpaceDutyDestroyScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":startQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- This is a duty mission, if the player has complete the quest, clear it first
	if (SpaceHelpers:isSpaceQuestComplete(pPlayer, self.questType, self.questName)) then
		SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, false)
	end

	-- Activate the Journal Quest
	SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, self.questType, self.questName, false)

	local spaceQuestHash = getHashCode(self.questZone)
	local zoneName = SceneObject(pPlayer):getZoneName()
	local playerZoneHash = getHashCode(zoneName)
	local pRootParent = SceneObject(pPlayer):getRootParent()

	-- Check if the player is in the proper zone already
	if (playerZoneHash == spaceQuestHash and not SpaceHelpers:isInYacht(pPlayer)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, true)

		-- Quest Progress Update
		SpaceHelpers:sendQuestProgess(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":title")

		-- Find a target location
		self:getTargetLocation(pPlayer, "true")
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

	-- Remove any remaining ships
	self:removeAttackShips(pPlayer)

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end

	-- Remove any data
	deleteData(playerID .. ":" .. self.className .. ":CurrentWave:")
	deleteData(playerID .. ":" .. self.className .. ":CurrentRound:")
	deleteData(playerID .. ":" .. self.className .. ":CurrentLevel:")
	deleteData(playerID .. ":" .. self.className .. ":DestroyKillCount:")
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

	-- Complete the Journal Quest
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

	-- Remove any remaining ships
	self:removeAttackShips(pPlayer)

	-- Remove any data
	deleteData(playerID .. ":" .. self.className .. ":CurrentWave:")
	deleteData(playerID .. ":" .. self.className .. ":CurrentRound:")
	deleteData(playerID .. ":" .. self.className .. ":CurrentLevel:")
	deleteData(playerID .. ":" .. self.className .. ":DestroyKillCount:")

	-- Complete System Message
	CreatureObject(pPlayer):sendSystemMessage("@spacequest/destroy_duty/" .. self.questName .. ":complete")
end

function SpaceDutyDestroyScreenplay:getTargetLocation(pPlayer, initial)
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

	local minDistance = self.minDistance
	local maxDistance = self.maxDistance

	if (initial == "false" or self.DEBUG_SPACE_DUTY_DESTROY) then
		minDistance = 1500
		maxDistance = 2500
	end

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":getTargetLocation - Min Distance: " .. minDistance .. " Max Distance: " .. maxDistance .. " Initial: " .. initial)
	end

	local randomLocation = SpaceHelpers:getRandomPositionInSphere(x, z, y, minDistance, maxDistance)

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":getTargetLocation - Chosen Location -- X: " .. randomLocation.x .. ", Z: " .. randomLocation.z .. " Y: " .. randomLocation.y)
	end

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

	local messageString = LuaStringIdChatParameter("@spacequest/destroy_duty/" .. self.questName .. ":duty_update")
	messageString:setTO("@spacequest/destroy_duty/" .. self.questName .. ":found_loc")

	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

function SpaceDutyDestroyScreenplay:spawnAttackWave(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.className .. ":spawnAttackWave - pPlayer is nil.", LT_ERROR)
		return
	end

	local pPlayerShip = SceneObject(pPlayer):getRootParent()

	if (pPlayerShip == nil or not SceneObject(pPlayerShip):isShipObject()) then
		Logger:log(self.className .. ":spawnAttackWave - pPlayerShip is nil.", LT_ERROR)
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local questAreaID = readData(playerID .. ":" .. self.className .. ":targetArea:")

	local pQuestArea = getSceneObject(questAreaID)

	if (pQuestArea == nil) then
		self:failQuest(pPlayer)
		return
	end

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":spawnAttackWave called")
	end

	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
	local bossLevel = readData(playerID .. ":" .. self.className .. ":bossLevel:")
	local currentWave = readData(playerID .. ":" .. self.className .. ":CurrentWave:")
	local currentLevel = readData(playerID .. ":" .. self.className .. ":CurrentLevel:") + 1
	local playerFactionHash = SpaceHelpers:getPlayerShipFactionHash(pPlayer)

	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

	local shipTable = self.shipTypes

	-- Spawn Boss Wave
	if (bossLevel > 0) then
		deleteData(playerID .. ":" .. self.className .. ":bossLevel:")

		local spawnLocation = ShipObject(pPlayerShip):getSpawnPointInFrontOfShip(600, 1200)
		local bossSquadSize = currentLevel

		for i = 1, bossSquadSize, 1 do
			local shipAgentString = ""

			if (i == 1) then
				shipAgentString = self.bossShip
			else
				shipAgentString = shipTable[1][((i - 1) % #shipTable[1]) + 1]
			end

			if (self.DEBUG_SPACE_DUTY_DESTROY) then
				print(self.className .. ":spawnAttackWave -- Spawning Boss Level Ship: " .. shipAgentString)
			end

			local pBossLevelAgent = spawnShipAgent(shipAgentString, self.questZone, spawnLocation[1], spawnLocation[2], spawnLocation[3], pPlayerShip)

			if (pBossLevelAgent == nil) then
				self:failQuest(pPlayer)
				return
			end

			-- Set as a mission-specific ship locked to the mission holder
			ShipAiAgent(pBossLevelAgent):setMissionOwner(pPlayer)

			local bossID = SceneObject(pBossLevelAgent):getObjectID()

			writeData(bossID .. ":" .. self.className .. ":QuestOwnerID:", playerID)

			-- Add to the list of shipIDs
			shipIDs[#shipIDs + 1] = bossID

			-- Set as space mission object
			CreatureObject(pPlayer):addSpaceMissionObject(bossID, (i == bossSquadSize))

			-- Add kill observer
			createObserver(DESTROYEDSHIP, self.className, "notifyBossShipDestroyed", pBossLevelAgent)

			-- Add aggo and set the pPlayerShip as ShipAgents Defender
			ShipAiAgent(pBossLevelAgent):addSpaceFactionEnemy(playerFactionHash)
			ShipAiAgent(pBossLevelAgent):engageShipTarget(pPlayerShip)

			if (i == 1) then
				-- Taunt player
				self:tauntPlayer(pBossLevelAgent, pPlayer, true)

				-- Play effect for player
				CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_spawn_boss.cef", "")
				CreatureObject(pPlayer):playMusicMessage("sound/music_com_enter_battle.snd")

				-- Quest Message for Boss
				CreatureObject(pPlayer):sendSystemMessage("@spacequest/destroy_duty/" .. self.questName .. ":boss_detected")
			end
		end
	-- Spawn regular attack wave
	else
		local spawnLocation = {}

		if (getRandomNumber(1, 100) > 20) then
			spawnLocation = ShipObject(pPlayerShip):getSpawnPointInFrontOfShip(600, 1200)
			CreatureObject(pPlayer):sendSystemMessage("@spacequest/destroy_duty/" .. self.questName .. ":targets_detected")
		else
			spawnLocation = ShipObject(pPlayerShip):getSpawnPointBehindShip(600, 1200)
			CreatureObject(pPlayer):sendSystemMessage("@spacequest/destroy_duty/" .. self.questName .. ":targets_behind")
		end

		local fighterCount = currentWave + (currentLevel - 1)
		local shipTableSize = #shipTable
		local tableSet = 1

		for i = 1, fighterCount, 1 do
			local shipType = shipTable[tableSet][((i - 1) % #shipTable[tableSet]) + 1]

			if (self.DEBUG_SPACE_DUTY_DESTROY) then
				print(self.className .. ":spawnAttackWave -- Spawning Regular Attack Ship: " .. shipType)
			end

			local pShipAgent = spawnShipAgent(shipType, self.questZone, spawnLocation[1], spawnLocation[2], spawnLocation[3], pPlayerShip)

			if (pShipAgent == nil) then
				goto continue
			end

			-- Set as a mission-specific ship locked to the mission holder
			ShipAiAgent(pShipAgent):setMissionOwner(pPlayer)

			local agentID = SceneObject(pShipAgent):getObjectID()

			writeData(agentID .. ":" .. self.className .. ":QuestOwnerID:", playerID)

			-- Add kill observer
			createObserver(DESTROYEDSHIP, self.className, "notifyAttackShipDestroyed", pShipAgent)

			-- Set as space mission object
			CreatureObject(pPlayer):addSpaceMissionObject(agentID, (i == fighterCount))

			if (self.DEBUG_SPACE_DUTY_DESTROY) then
				local testLocation = ShipObject(pShipAgent):getSpawnPointInFrontOfShip(1500, 1700)

				drawClientPath(pShipAgent,spawnLocation[1], spawnLocation[2], spawnLocation[3], testLocation[1], testLocation[2], testLocation[3])
			end

			-- Add the players faction to the agents faction enemy vector
			ShipAiAgent(pShipAgent):addSpaceFactionEnemy(playerFactionHash)

			-- Engage the target ship, in this case pPlayerShip
			ShipAiAgent(pShipAgent):engageShipTarget(pPlayerShip)

			-- Add to the list of shipIDs
			shipIDs[#shipIDs + 1] = agentID

			if (i == fighterCount) then
				-- Send Taunt to player
				self:tauntPlayer(pShipAgent, pPlayer, false)
			-- Reset tableSet var
			elseif (tableSet >= shipTableSize) then
				tableSet = 1
			-- Increment tableSet if there are available tables
			elseif (shipTableSize > 1) then
				tableSet = tableSet + 1
			end

			::continue::
		end

		-- Play effect for player
		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_spawn_wave.cef", "")
		CreatureObject(pPlayer):playMusicMessage("sound/music_event_danger.snd")
	end

	-- Store the Spawned Attack Ships
	writeStringVectorSharedMemory(playerID .. self.className .. ":attackShips:", shipIDs)
end

function SpaceDutyDestroyScreenplay:removeAttackShips(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Remove from Attack Ships Vector
	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":removeAttackShips -- Ship Count: " .. #shipIDs)
	end

	for i = 1, #shipIDs, 1 do
		local attackAgentID = tonumber(shipIDs[i])

		-- Remove the attacking ship agent as a mission object
		CreatureObject(pPlayer):removeSpaceMissionObject(attackAgentID, false)

		-- Get pointer to attack ship
		local pAttackShip = getSceneObject(attackAgentID)

		if (pAttackShip == nil) then
			goto continue
		end

		-- Remove the kill observer
		dropObserver(DESTROYEDSHIP, self.className, "notifyAttackShipDestroyed", pAttackShip)

		-- Make ship fly away first
		ShipObject(pAttackShip):setHyperspacing(true);

		SceneObject(pAttackShip):setPosition(8000, 8000, 8000)

		-- Remove the attack ship
		createEvent(2000, "SpaceHelpers", "delayedDestroyShipAgent", pAttackShip, "")

		::continue::
	end
end

function SpaceDutyDestroyScreenplay:tauntPlayer(pShipAgent, pPlayer, isBoss)
	if (pPlayer == nil or pShipAgent == nil) then
		return
	end

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print("SpaceDutyDestroyScreenplay:tauntPlayer -- Quest Name: " .. self.questName)
	end

	local tauntString = "@spacequest/destroy_duty/" .. self.questName .. ":"

	if (isBoss) then
		tauntString = tauntString .. "dd_boss_taunt_" .. tostring(getRandomNumber(1, 5))
	else
		tauntString = tauntString .. "taunt_" .. tostring(getRandomNumber(1, 5))
	end

	ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, tauntString)
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
		createEvent(2000, self.className, "getTargetLocation", pPlayer, "true")
	elseif (zoneNameHash ~= spaceQuestHash and SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		createEvent(2000, self.className, "failQuest", pPlayer, "true")
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

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print("SpaceDutyDestroyScreenplay:notifyEnteredQuestArea -- Quest Name: " .. self.questName .. " Player Pilot: " .. SceneObject(pPilot):getDisplayedName())
	end

	writeData(playerID .. ":" .. self.className .. ":CurrentWave:", 1)

	-- Spawn wave
	createEvent(4000, self.className, "spawnAttackWave", pPilot, "")

	return 1
end

function SpaceDutyDestroyScreenplay:notifyBossShipDestroyed(pShipAgent, pBossShip)
	if (pShipAgent == nil) then
		return 1
	end

	local agentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(agentID .. ":" .. self.className .. ":QuestOwnerID:")

	deleteData(agentID .. ":" .. self.className .. ":QuestOwnerID:")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		Logger:log(self.className .. ":notifyBossShipDestroyed - Quest Owner is nil.", LT_ERROR)
		return 1
	end

	-- Remove as Mission Object
	CreatureObject(pPlayer):removeSpaceMissionObject(agentID, true)

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":notifyBossShipDestroyed - Boss Ship Destoyed: " .. SceneObject(pShipAgent):getDisplayedName() .. " Quest Owner Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	-- Destroy the area
	local playerAreaID = readData(playerID .. ":" .. self.className .. ":targetArea:")
	deleteData(playerID .. ":" .. self.className .. ":targetArea:", questAreaID)

	local pQuestArea = getSceneObject(questAreaID)

	if (pQuestArea ~= nil) then
		destroyObjectFromWorld(pQuestArea)
	end

	-- Remove from Attack Ships Vector
	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
	local newIDs = {}

	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

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

		if (self.DEBUG_SPACE_DUTY_DESTROY) then
			print(self.className .. ":notifyBossShipDestroyed - Boss Ships remaining: " .. #newIDs)
		end
	else
		-- Remove waypoint
		SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

		-- Boss killed message
		CreatureObject(pPlayer):sendSystemMessage("@space/quest:destroy_duty_boss_dead")

		-- read the current level
		local currentLevel = readData(playerID .. ":" .. self.className .. ":CurrentLevel:") + 1
		deleteData(playerID .. ":" .. self.className .. ":CurrentLevel:")

		-- Calculate Reward
		local rewardCredits = self.creditReward * 3

		-- Duty Mission is complete
		if (currentLevel == self.totalLevels) then
			if (self.DEBUG_SPACE_DUTY_DESTROY) then
				print(self.className .. ":notifyBossShipDestroyed - Duty Mission Complete")
			end

			-- Set Quest Complete
			self:completeQuest(pPlayer, true)

			-- Calculate reward
			rewardCredits = rewardCredits * 25

			-- Complete message
			local targetsMsg = LuaStringIdChatParameter("@space/quest:destroy_duty_complete_reward")
			targetsMsg:setDI(rewardCredits)

			CreatureObject(pPlayer):sendSystemMessage(targetsMsg:_getObject())

			-- Give completion reward credits
			SpaceHelpers:spaceCreditReward(pPlayer, rewardCredits)

		-- Start next level of rounds
		else
			if (self.DEBUG_SPACE_DUTY_DESTROY) then
				print(self.className .. ":notifyBossShipDestroyed - Duty Mission Level Finished, Starting Next Level -- Current Level: " .. currentLevel .. " out of " .. self.totalLevels .. " Total Levels.")
			end

			-- Update the level
			writeData(playerID .. ":" .. self.className .. ":CurrentLevel:", currentLevel)

			-- Remove waypoint
			SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

			-- Calculate reward
			rewardCredits = rewardCredits * 3

			-- Boss Reward message
			local targetsMsg = LuaStringIdChatParameter("@space/quest:destroy_duty_boss_reward")
			targetsMsg:setDI(rewardCredits)

			CreatureObject(pPlayer):sendSystemMessage(targetsMsg:_getObject())

			-- Give boss reward credits
			SpaceHelpers:spaceCreditReward(pPlayer, rewardCredits)

			-- Find the next target location
			createEvent(6000, self.className, "getTargetLocation", pPlayer, "false")

			-- "destroy_duty_level_boss_dead", " \\#pcontrast3 > \\#00ff00 The enemy commander has been defeated! \\#pcontrast3 < \\#pcontrast3 > \\#ff0000 In response, more enemy ships have entered the sector! \\#pcontrast3 <"
			createEvent(2000, "SpaceHelpers", "sendDelayedMessage", pPlayer, "@space/quest:destroy_duty_level_boss_dead")
		end
	end

	return 1
end

function SpaceDutyDestroyScreenplay:notifyAttackShipDestroyed(pShipAgent, pKillerShip)
	if (pShipAgent == nil) then
		return 1
	end

	local agentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(agentID .. ":" .. self.className .. ":QuestOwnerID:")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		Logger:log(self.className .. ":notifyAttackShipDestroyed - Quest Owner is nil.", LT_ERROR)
		return 1
	end

	if (self.DEBUG_SPACE_DUTY_DESTROY) then
		print(self.className .. ":notifyAttackShipDestroyed - Ship Destoyed: " .. SceneObject(pShipAgent):getDisplayedName() .. " Quest Owner Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	-- Remove as Mission Objects
	CreatureObject(pPlayer):removeSpaceMissionObject(agentID, true)

	-- Remove from Attack Ships Vector
	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
	local newIDs = {}

	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

	for i = 1, #shipIDs, 1 do
		local shipID = tonumber(shipIDs[i])

		if (agentID ~= shipID) then
			newIDs[#newIDs + 1] = shipID
		end
	end

	-- Increase kill count
	local totalKills = readData(playerID .. ":" .. self.className .. ":DestroyKillCount:")
	deleteData(playerID .. ":" .. self.className .. ":DestroyKillCount:")

	totalKills = totalKills + 1

	if (#newIDs > 0) then
		-- Store the Spawned Attack Ships
		writeStringVectorSharedMemory(playerID .. self.className .. ":attackShips:", newIDs)

		local messageString = LuaStringIdChatParameter("@space/quest:destroy_duty_targets_remaining")
		messageString:setDI(#newIDs)

		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

		writeData(playerID .. ":" .. self.className .. ":DestroyKillCount:", totalKills)

		if (self.DEBUG_SPACE_DUTY_DESTROY) then
			print(self.className .. ":notifyAttackShipDestroyed - Ships remaining: " .. #newIDs)
		end
	else
		-- Send attack over message
		CreatureObject(pPlayer):sendSystemMessage("@space/quest:destroy_duty_targets_dead")

		-- Check wave count
		local currentWave = readData(playerID .. ":" .. self.className .. ":CurrentWave:")
		deleteData(playerID .. ":" .. self.className .. ":CurrentWave:")

		-- Waves are not complete
		if (currentWave < self.totalWaves) then
			CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_wave.cef", "")

			writeData(playerID .. ":" .. self.className .. ":CurrentWave:", currentWave + 1)
			writeData(playerID .. ":" .. self.className .. ":DestroyKillCount:", totalKills)

			-- Spawn next wave
			createEvent(5000, self.className, "spawnAttackWave", pPlayer, "")

			if (self.DEBUG_SPACE_DUTY_DESTROY) then
				print(self.className .. ":notifyAttackShipDestroyed - Current Attack Wave: " .. currentWave .. " out of " .. self.totalWaves .. " Total Waves.")
			end

		-- All waves have been destroyed, update rounds
		else
			if (self.DEBUG_SPACE_DUTY_DESTROY) then
				print(self.className .. ":notifyAttackShipDestroyed - All waves destroyed.")
			end

			CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_all.cef", "")

			local currentRound = readData(playerID .. ":" .. self.className .. ":CurrentRound:") + 1
			deleteData(playerID .. ":" .. self.className .. ":CurrentRound:")

			-- Give Round Reward
			local rewardCredits = self.creditReward * totalKills

			local targetsMsg = LuaStringIdChatParameter("@space/quest:destroy_duty_round_reward")
			targetsMsg:setDI(rewardCredits)

			CreatureObject(pPlayer):sendSystemMessage(targetsMsg:_getObject())

			SpaceHelpers:spaceCreditReward(pPlayer, rewardCredits)

			-- Destroy the area
			local playerAreaID = readData(playerID .. ":" .. self.className .. ":targetArea:")
			deleteData(playerID .. ":" .. self.className .. ":targetArea:", questAreaID)

			local pQuestArea = getSceneObject(questAreaID)

			if (pQuestArea ~= nil) then
				destroyObjectFromWorld(pQuestArea)
			end

			-- Remove waypoint
			SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

			-- All of the rounds are complete, spawn boss
			if (currentRound > self.totalRounds) then
				if (self.DEBUG_SPACE_DUTY_DESTROY) then
					print(self.className .. ":notifyAttackShipDestroyed - Round has ended, spawning boss for end of level.")
				end

				CreatureObject(pPlayer):playMusicMessage("sound/music_combat_bfield_vict.snd")

				-- Set boss data
				writeData(playerID .. ":" .. self.className .. ":bossLevel:", 1)

				local currentLevel = readData(playerID .. ":" .. self.className .. ":CurrentLevel:") + 1

				local messageString = LuaStringIdChatParameter("@spacequest/destroy_duty/" .. self.questName .. ":level_boss")
				messageString:setTO("@spacequest/destroy_duty/" .. self.questName .. ":boss_title_" .. tostring(currentLevel))

				CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

				-- Find the boss target location
				createEvent(3000, self.className, "getTargetLocation", pPlayer, "false")

				-- Round is complete, give next location
			else
				if (self.DEBUG_SPACE_DUTY_DESTROY) then
					print(self.className .. ":notifyAttackShipDestroyed - Round not complete - " .. currentRound .. " of " .. self.totalRounds .. " Total Rounds.")
				end

				-- Find the next target location
				createEvent(6000, self.className, "getTargetLocation", pPlayer, "false")

				CreatureObject(pPlayer):playMusicMessage("sound/music_int_complete_neutral.snd")

				writeData(playerID .. ":" .. self.className .. ":CurrentRound:", currentRound)
			end
		end
	end

	return 1
end
