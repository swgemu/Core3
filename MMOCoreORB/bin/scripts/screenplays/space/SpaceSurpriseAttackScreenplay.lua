SpaceSurpriseAttackScreenplay = SpaceQuestLogic:new {
	className = "SpaceSurpriseAttackScreenplay",

	DEBUG_SPACE_SURPRISE_ATTACK = false,
}

function SpaceSurpriseAttackScreenplay:start()
end

function SpaceSurpriseAttackScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	-- Activate Space Quest
	SpaceHelpers:activateSpaceQuest(pPlayer, nil, self.questType, self.questName, 1)

	-- Trigger surpise attack
	self:spawnSurpriseAttack(pPlayer)
end

function SpaceSurpriseAttackScreenplay:completeQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	-- Remove parent quest waypoint
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.parentQuest)

	-- Complete quest for surprise attack
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, false)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.parentQuest, "enteredZone", pPlayer)

	if (self.completeParent) then
		-- Complete the parent quest
		createEvent(100, self.parentQuestType .. "_" .. self.questName, "completeQuest", pPlayer, "")
	end
end

function SpaceSurpriseAttackScreenplay:failQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, 1)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Clear kill count off the player
	deleteData(SceneObject(pPlayer):getObjectID() .. self.className .. ":Count")

	-- Fail the parent quest
	if (self.parentQuestType ~= "") then
		createEvent(200, self.parentQuestType .. "_" .. self.questName, "failQuest", pPlayer, "")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.questName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.questName, "failQuest", pPlayer, "")
	end
end

function SpaceSurpriseAttackScreenplay:spawnSurpriseAttack(pPilot)
	if (pPilot == nil) then
		return
	end

	local pPilotShip = SceneObject(pPilot):getRootParent()

	if (pPilotShip == nil or not SceneObject(pPilotShip):isShipObject()) then
		return 0
	end

	local x = SceneObject(pPilotShip):getPositionX()
	local z = SceneObject(pPilotShip):getPositionZ()
	local y = SceneObject(pPilotShip):getPositionY()

	if (self.DEBUG_SPACE_SURPRISE_ATTACK) then
		print(self.className .. ":spawnSurpriseAttack - Space Quest: " .. self.questName)
	end

	local attackShips = self.surpriseAttackShips
	local spawnZone = attackShips.zone
	local shipsTable = attackShips.spawns
	local pilotID = SceneObject(pPilot):getObjectID()

	if (self.DEBUG_SPACE_SURPRISE_ATTACK) then
		print("spawnSurpriseAttack -- spawnZone: " .. spawnZone .. " shipsTable size: " .. #shipsTable)
	end

	local totalSpawned = 0
	local shipIDs = {}

	for i = 1, #shipsTable, 1 do
		local count = shipsTable[i].count
		local shipName = shipsTable[i].shipName

		if (self.DEBUG_SPACE_SURPRISE_ATTACK) then
			print("spawnSurpriseAttack -- spawning ship: " .. shipName .. " Spawn Count: " .. count)
		end

		for j = 1, count, 1 do
			local pShipAgent = spawnShipAgent(shipName, spawnZone, x + (getRandomNumber(50, 250) - getRandomNumber(50, 250)), z  + (getRandomNumber(50, 250) - getRandomNumber(50, 250)), y  + (getRandomNumber(50, 250) - getRandomNumber(50, 250)))

			if (pShipAgent ~= nil) then
				-- Setup the patrol
				ShipAiAgent(pShipAgent):setMinimumGuardPatrol(200)
				ShipAiAgent(pShipAgent):setMaximumGuardPatrol(1000)

				ShipAiAgent(pShipAgent):setGuardPatrol()

				-- Make sure the extra mobs are despawned if all players leaves the area
				ShipAiAgent(pShipAgent):setDespawnOnNoPlayerInRange(true)

				-- Add kill observer
				createObserver(OBJECTDESTRUCTION, self.className, "notifyShipDestroyed", pShipAgent)

				-- Zone Removal Observer
				--createObserver(OBJECTREMOVEDFROMZONE, self.className, "attackShipRemovedFromZone", pShipAgent)

				local agentID = SceneObject(pShipAgent):getObjectID()

				shipIDs[#shipIDs + 1] = agentID

				--CreatureObject(pPilot):addSpaceMissionObject(agentID, true)

				-- Set the player as ShipAgents Defender
				ShipAiAgent(pShipAgent):addAggro(pPilotShip, 1)
				ShipAiAgent(pShipAgent):setDefender(pPilotShip)

				totalSpawned = totalSpawned + 1

				-- Store the quest owner
				writeData(agentID .. ":QuestOwner", pilotID)
			end
		end
	end

	for i = 1, #shipIDs, 1 do
		-- Set as Mission Objects
		CreatureObject(pPilot):addSpaceMissionObject(shipIDs[i], (i == #shipIDs))
	end

	if (totalSpawned > 0) then
		writeData(pilotID .. self.className .. ":Count", totalSpawned)
	end

	-- Player effect for player
	CreatureObject(pPilot):playEffect("clienteffect/ui_quest_spawn_wave.cef", "")

	-- Attack update message
	SpaceHelpers:sendQuestUpdate(pPilot, totalSpawned .. " ships have entered the area and are closing to attack!") -- "destroy_surprise_attack"

	-- Send Quest Progress Message
	SpaceHelpers:sendQuestProgess(pPilot, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":title")
end

--[[

		Observers

--]]

function SpaceSurpriseAttackScreenplay:notifyShipDestroyed(pShipAgent, pKillerShip)
	if (pShipAgent == nil) then
		return 1
	end

	local agentID = SceneObject(pShipAgent):getObjectID()
	local playerID = readData(agentID .. ":QuestOwner")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		Logger:log(self.className .. ":notifyShipDestroyed - Quest Owner is nil.", LT_ERROR)
		return 1
	end

	if (self.DEBUG_SPACE_SURPRISE_ATTACK) then
		print(self.className .. ":notifyShipDestroyed - Ship Destoyed: " .. SceneObject(pShipAgent):getDisplayedName() .. " Quest Owner Name: " .. SceneObject(pPlayer):getDisplayedName())
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 1
	end

	local spawnCount = readData(playerID .. self.className .. ":Count")
	spawnCount = spawnCount - 1

	-- Clear the old kill count off the player
	deleteData(playerID .. self.className .. ":Count")

	-- Remove Ship as Mission Critical Object
	CreatureObject(pPlayer):removeSpaceMissionObject(agentID, false)

	if (spawnCount > 0) then
		-- Kill counter sent to player
		SpaceHelpers:sendQuestUpdate(pPlayer, spawnCount .. " targets remaining to be destroyed.") -- "destroy_remainder_update"

		-- Update the remaining count
		writeData(playerID .. self.className .. ":Count", spawnCount)
	else
		-- Player effect for player
		CreatureObject(pPlayer):playEffect("clienteffect/ui_quest_destroyed_wave.cef", "")

		CreatureObject(pPlayer):sendSystemMessage("@spacequest/destroy_surpriseattack/" .. self.questName .. ":complete")

		-- Complete the quest
		self:completeQuest(pPlayer)
	end

	return 1
end

function SpaceSurpriseAttackScreenplay:attackShipRemovedFromZone(pShipAgent)
	if (pShipAgent == nil) then
		return 1
	end

	local agentID = SceneObject(pShipAgent):getObjectID()







	return 1
end
