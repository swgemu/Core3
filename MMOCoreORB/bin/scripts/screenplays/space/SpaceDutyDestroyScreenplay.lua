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

		= new StringFile("spacequest/destroy_duty/corellia_privateer_6");
		"boss_detected", "\\#pcontrast3 Tactical Computer: < \\#pcontrast1 Vessel with veteran insignias on attack vector, weapon systems armed. \\#pcontrast3 >");
		"boss_title_1", "Russ Grimblade (Hidden Daggers Captain)");
		"boss_title_2", "Xopw Laow (Hidden Daggers Captain)");
		"boss_title_3", "Mori the Bastard (Hidden Daggers Captain)");
		"boss_title_4", "Owpa Awoz (Hidden Daggers Captain)");
		"boss_title_5", "Quixio the Rotten (Hidden Daggers Captain)");
		"complete", "Fantastic job pilot, we struck a huge blow to the Hidden Daggers today. Return to base for a well earned rest.");

		"duty_update", "CorSec Command: < %TO >");
		"found_loc", "New coordinates of pirate activity has been uploaded to your nav computer. Go get them!");
		"level_boss", "\\#pcontrast3 CorSec Command: < \\#pcontrast1 The Hidden Daggers has sent %TO to bring you down, proceed with caution. \\#pcontrast3 >");
		"level_boss_dead", "Amazing! The Hidden Daggers will not forget this day. Stand by for further orders.");
		"level_increase", "The Hidden Daggers are sending more reinforcements in responce to our attacks.");
		"Quest Log Data", "Text");
		"targets_behind", "\\#pcontrast3 Tactical Computer: < \\#pcontrast1 Be aware, vessels trying to target this ship with their weapon systems. Attack originating direction 180 degrees.\\#pcontrast3  >");
		"targets_detected", "\\#pcontrast3 Tactical Computer: < \\#pcontrast1 Vessels fitting hunted ship profile on attack vector, weapon systems armed. \\#pcontrast3 >");
		"title", "Corellia System: Duty: Strike a blow to the Hidden Daggers Leadership.");
		"title_d", "Hunt Down the Hidden Daggers Leaders");


		"space/quest"


		"destroy_duty", "Space: Destroy Duty");
		"destroy_duty_boss_dead", " \\#pcontrast3 Tactical Computer: < \\#00ff00 The enemy commander's wing has been eliminated! \\#pcontrast3 >");
		"destroy_duty_boss_detected", " \\#pcontrast3 > \\#ff0000 The enemy commander's wing is moving to attack! \\#pcontrast3 <");
		"destroy_duty_boss_reward", ">  \\#pcontrast1 Command wing elimination bonus: \\#pcontrast2 %DI \\#pcontrast1 credits. <");
		"destroy_duty_complete_reward", ">  \\#pcontrast1 Duty completion bonus: \\#pcontrast2 %DI \\#pcontrast1 credits. <");
		"destroy_duty_level_boss", " \\#pcontrast3 > \\#ff0000 An enemy commander has been dispatched to stop you! \\#pcontrast3 <");
		"destroy_duty_level_boss_dead", " \\#pcontrast3 > \\#00ff00 The enemy commander has been defeated! \\#pcontrast3 < \\#pcontrast3 > \\#ff0000 In response, more enemy ships have entered the sector! \\#pcontrast3 <");
		"destroy_duty_level_increase", " \\#pcontrast3 > \\#ff0000 Stronger enemy ships have entered the sector! \\#pcontrast3 <");
		"destroy_duty_round_reward", "\\#pcontrast3 > \\#pcontrast1 All waves eliminated. Reward: \\#pcontrast2 %DI \\#pcontrast1 credits. \\#pcontrast3 <");
		"destroy_duty_targets_dead", " \\#pcontrast3 Tactical Computer: < \\#ffff00All enemy targets destroyed. \\#pcontrast3 >");
		"destroy_duty_targets_remaining", " \\#pcontrast3 Tactical Computer: < \\#pcontrast1 Target destroyed. %DI target(s) remain. \\#pcontrast3 >");
		"destroy_duty_target_detected", " \\#pcontrast3 > \\#pcontrast1 Enemy targets are on an attack vector! \\#pcontrast3 <");
		"destroy_duty_target_located", " \\#pcontrast3 > \\#pcontrast1 Duty target located. A waypoint has been created. \\#pcontrast3 <");

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

	if (pPlayerShip == nil) then
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

	local x = SceneObject(pQuestArea):getPositionX()
	local z = SceneObject(pQuestArea):getPositionZ()
	local y = SceneObject(pQuestArea):getPositionY()

	local randomLocation = SpaceHelpers:getRandomPositionInSphere(x, z, y, 150, 400)

	local currentWave = readData(playerID .. ":" .. self.className .. ":currentWave:")

	local shipIDs = readStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")
	deleteStringVectorSharedMemory(playerID .. self.className .. ":attackShips:")

	-- Spawn Boss Wave
	if (currentWave >= self.totalWaves) then
		local pBossAgent = spawnShipAgent(self.bossMobile, self.questZone, randomLocation.x, randomLocation.z, randomLocation.y)

		if (pBossAgent == nil) then
			self:failQuest(pPlayer)
			return
		end

		local bossID = SceneObject(pBossAgent):getObjectID()

		writeData(bossID .. ":" .. self.className .. ":questOwnerID:", playerID)

		-- Add kill observer
		createObserver(OBJECTDESTRUCTION, self.className, "notifyAttackShipDestroyed", pBossAgent)

		-- Set as space mission object
		CreatureObject(pPlayer):addSpaceMissionObject(bossID, true)

		-- Add aggo and set the pPlayerShip as ShipAgents Defender
		ShipAiAgent(pBossAgent):engageShipTarget(pPlayerShip)

		-- Add to the list of shipIDs
		shipIDs[#shipIDs + 1] = bossIDs

		-- Schedule a taunt
		createEvent(2000, self.className, "tauntPlayer", pBossAgent, playerID)

	-- Spawn regular attack wave
	else
		local shipTable = self.shipTypes

		for i = 1, #shipTable, 1 do
			local pShipAgent = spawnShipAgent(shipTable[i], self.questZone, randomLocation.x, randomLocation.z, randomLocation.y)

			if (pShipAgent == nil) then
				goto continue
			end

			local agentID = SceneObject(pShipAgent):getObjectID()

			writeData(agentID .. ":" .. self.className .. ":questOwnerID:", playerID)

			-- Add kill observer
			createObserver(OBJECTDESTRUCTION, self.className, "notifyAttackShipDestroyed", pShipAgent)

			-- Set as space mission object
			CreatureObject(pPlayer):addSpaceMissionObject(agentID, (i == #shipTable))

			ShipAiAgent(pShipAgent):addAggro(pPlayer, 1)
			ShipAiAgent(pShipAgent):setDefender(pPlayer)

			-- Add aggo and set the pPlayerShip as ShipAgents Defender
			ShipAiAgent(pShipAgent):engageShipTarget(pPlayerShip)

			-- Add to the list of shipIDs
			shipIDs[#shipIDs + 1] = agentID

			if (i == #shipTable) then
				-- Schedule a taunt
				createEvent(2000, self.className, "tauntPlayer", pShipAgent, playerID)
			end

			::continue::
		end
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
		dropObserver(OBJECTDESTRUCTION, self.className, "notifyAttackShipDestroyed", pAttackShip)

		-- Make ship fly away first
		ShipObject(pAttackShip):setHyperspacing(true);

		SceneObject(pAttackShip):setPosition(8000, 8000, 8000)

		-- Remove the attack ship
		createEvent(2000, "SpaceHelpers", "delayedDestroyShipAgent", pAttackShip, "")

		::continue::
	end
end

function SpaceDutyDestroyScreenplay:tauntPlayer(pShipAgent, playerID)
	local pPlayer = getSceneObject(tonumber(playerID))

	if (pPlayer == nil or pShipAgent == nil) then
		return
	end

	local tauntString = ""

	if (isBoss) then
		tauntString = "dd_boss_taunt_" .. tostring(getRandomNumber(1, 5))
	else
		tauntString = "taunt_" .. tostring(getRandomNumber(1, 5))
	end

	ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, "@spacequest/destroy_duty/" .. self.questName .. ":" .. tauntString)
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

	writeData(playerID .. ":" .. self.className .. ":currentWave:", 1)

	-- Spawn wave
	createEvent(4000, self.className, "spawnAttackWave", pPilot, "")

	return 1
end

function SpaceDutyDestroyScreenplay:notifyAttackShipDestroyed(pShipAgent, pKillerShip)
	if (pShipAgent == nil) then
		return 1
	end

	local agentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(agentID .. ":" .. self.className .. ":questOwnerID:")

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

	local index = 0

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
	else
		-- Send attack over message
		CreatureObject(pPlayer):sendSystemMessage("@space/quest:destroy_duty_targets_dead")

		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_wave.cef", "")

		-- Increase wave count
		local currentWave = readData(playerID .. ":" .. self.className .. ":currentWave:")
		deleteData(playerID .. ":" .. self.className .. ":currentWave:")

		writeData(playerID .. ":" .. self.className .. ":currentWave:", currentWave + 1)
	end

	-- Increase kill count
	local totalKills = readData(playerID .. ":" .. self.className .. ":" .. ":EscortKillCount:")
	deleteData(playerID .. ":" .. self.className .. ":" .. ":EscortKillCount:")

	totalKills = totalKills + 1

	writeData(playerID .. ":" .. self.className .. ":" .. ":EscortKillCount:", totalKills)

	return 1
end