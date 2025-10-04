SpaceRecoveryScreenplay = SpaceQuestLogic:new {
	className = "SpaceRecoveryScreenplay",

	-- Screenplay Specific Variables

	DEBUG_SPACE_RECOVERY = true,

	arrivalDelay = 5, -- In Seconds

	recoverShip = "",

	escortPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	recoveryPoints = {
		--{zoneName = "space_corellia", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	escortSpeed = 20,
	testEscortSpeed = 40,

	attackDelay = 30, -- In Seconds
	attackShips = {},
}

registerScreenPlay("SpaceRecoveryScreenplay", false)

--[[

		Space Recovery Quest Functions

--]]

function SpaceRecoveryScreenplay:start()
end

function SpaceRecoveryScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
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

	-- Check if the player is in the proper zone already
	if (playerZoneHash == spaceQuestHash and not SpaceHelpers:isInYacht(pPlayer)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, true)

		createEvent(self.arrivalDelay * 1000, self.className, "setupRecover", pPlayer, "")
	end

	-- Create inital observer for player entering Zone and to handle failing quest
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

function SpaceRecoveryScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":completeQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	local notifyBool = true

	if (notifyClient == "false") then
		notifyBool = false
	end

	-- Complete the Journal Quest
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, notifyBool)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	self:cleanUpQuestData(SceneObject(pPlayer):getObjectID())
end

function SpaceRecoveryScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
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

	self:cleanUpQuestData(SceneObject(pPlayer):getObjectID())

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "false")
	end
end

function SpaceRecoveryScreenplay:cleanUpQuestData(playerID)




end

function SpaceEscortScreenplay:setupRecover(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to setupRecover due to pPlayer being nil.", LT_ERROR)
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Quest Progress update
	SpaceHelpers:sendQuestProgess(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":arrival_phase_1")

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":setupEscort called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Schedule the ship arrival
	createEvent(self.arrivalDelay * 1000, self.className, "spawnRecoveryShip", pPlayer, "")
end


function SpaceRecoveryScreenplay:spawnRecoveryShip(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to spawnRecoveryShip due to pPlayer being nil.", LT_ERROR)
		return
	end

	local pPlayerShip = SceneObject(pPlayer):getRootParent()

	if (pPlayerShip == nil or not SceneObject(pPlayerShip):isShipObject()) then
		Logger:log(self.className .. ":spawnRecoveryShip - pPlayerShip is nil.", LT_ERROR)
		return
	end
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local spawnLocation = ShipObject(pPlayerShip):getSpawnPointInFrontOfShip(50, 150)

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":spawnEscortShip called -- Recover Ship: " .. self.recoverShip .. " Space Zone: " .. self.questZone .. " X: " .. spawnLocation[1] .. " Z: " .. spawnLocation[2] .. " Y: " .. spawnLocation[3])
	end

	-- Spawn the ship to be recovered
	local pShipAgent = spawnShipAgent(self.recoverShip, self.questZone, spawnLocation[1], spawnLocation[2], spawnLocation[3], pPlayerShip)

	if (pShipAgent == nil) then
		self:failQuest(pPlayer, "true")

		CreatureObject(pPlayer):sendSystemMessage("Quest failed due to the recovery ship failing to spawn.")
		return
	end

	local agentID = SceneObject(pShipAgent):getObjectID()

	-- Set the agent as a mission object
	CreatureObject(pPlayer):addSpaceMissionObject(agentID, true)

	-- Set as a mission-specific ship locked to the mission holder
	ShipAiAgent(pShipAgent):setMissionOwner(pPlayer)

	-- Set Fixed Patrol and escort flags
	ShipAiAgent(pShipAgent):setFixedPatrol()
	ShipAiAgent(pShipAgent):setEscort()

	if (self.DEBUG_SPACE_ESCORT) then
		ShipAiAgent(pShipAgent):setEscortSpeed(self.testEscortSpeed)
	else
		ShipAiAgent(pShipAgent):setEscortSpeed(self.escortSpeed)
	end

	-- Set as same space faction
	ShipObject(pShipAgent):setShipFactionString(SpaceHelpers:getPlayerShipFactionString(pPlayer))

	local playerFactionHash = SpaceHelpers:getPlayerShipFactionHash(pPlayer)

	ShipAiAgent(pShipAgent):addSpaceFactionAlly(playerFactionHash)
	ShipAiAgent(pShipAgent):removeSpaceFactionEnemy(playerFactionHash)



	--[[
	-- Add kill observer
	createObserver(OBJECTDESTRUCTION, self.className, "notifyEscortShipDestroyed", pShipAgent)

	-- Assign the escort points
	createEvent(5 * 1000, self.className, "assignEscortPoints", pShipAgent, "")

	-- Write the playersID that is escorting
	writeData(agentID .. ":" .. self.className .. ":escorterID:", playerID)

	-- Write the starting point name
	writeStringData(agentID .. ":" .. self.className .. ":startingPoint:", self.escortPoints[randomStart].name)

	-- Write the ship agent that is being escorted by the player
	writeData(playerID .. ":" .. self.className .. ":escortID:", agentID)

	-- Write the escort ships progress
	writeData(agentID .. ":" .. self.className .. ":escortShipProgress:", #self.escortPoints)

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. " -- Escort Ship Spawned - Name: " .. ShipObject(pShipAgent):getShipName())
	end

	if (self.checkPlayerDistance) then
		-- Player needs to stay within 1000m. Members in group also count if they are in space as well
		createEvent(60 * 1000, self.className, "checkEscort", pShipAgent, "")
	end

	-- Player effect for player
	CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_spawn_escort.cef", "")

	-- Player escort arrival music
	CreatureObject(pPlayer):playMusicMessage("sound/mus_quest_escort_arrival.snd")

	-- Send Message to Players
	ShipAiAgent(pShipAgent):tauntPlayer(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":reason_" .. tostring(getRandomNumber(1, self.tauntData.tauntCount)))
	]]









end

--[[

		Space Escort Observers

--]]

function SpaceRecoveryScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
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

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":enteredZone called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Player Zone Hash: " .. zoneNameHash .. " questZone hash: " .. spaceQuestHash)
	end

	-- Player is in the correct zone
	if (zoneNameHash == spaceQuestHash and not SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, true)

		-- Spawn recovery ships for the player
		createEvent(4000, self.className, "setupRecover", pPlayer, "")

		return 0
	elseif (zoneNameHash ~= spaceQuestHash and SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, self.questType, self.questName, 0)) then
		createEvent(2000, self.className, "failQuest", pPlayer, "true")

		return 1
	end

	return 0
end

