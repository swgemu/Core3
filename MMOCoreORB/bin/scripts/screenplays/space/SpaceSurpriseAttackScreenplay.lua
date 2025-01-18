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
	SpaceHelpers:completeSpaceQuest(pPlayer, self.questType, self.questName, 1)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.parentQuest, "enteredZone", pPlayer)

	if (self.completeParentTask) then
		-- Complete the parent quest task
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.parentQuestType, self.questName, self.parentTaskToComplete, 0)
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

				-- Set the player as ShipAgents Defender
				ShipAiAgent(pShipAgent):setDefender(pPilotShip)

				totalSpawned = totalSpawned + 1

				-- Store the quest owner
				writeData(SceneObject(pShipAgent):getObjectID() .. ":QuestOwner", pilotID)
			end
		end
	end

	if (totalSpawned > 0) then
		writeData(pilotID .. self.className .. ":Count", totalSpawned)
	end
end

--[[

		Observers

--]]

function SpaceSurpriseAttackScreenplay:notifyShipDestroyed(pShipAgent, pKillerShip)
	if (pShipAgent == nil) then
		return 1
	end

	local playerID = readData(SceneObject(pShipAgent):getObjectID() .. ":QuestOwner")
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

	-- Kill counter sent to player
	CreatureObject(pPlayer):sendSystemMessage(self.surpriseAttackShips.total - spawnCount .. " Killed") -- "@quest/groundquests:destroy_counter"

	if (spawnCount > 0) then
		-- Update the remaining count
		writeData(playerID .. self.className .. ":Count", spawnCount)
	else
		CreatureObject(pPlayer):sendSystemMessage("@spacequest/destroy_surpriseattack/" .. self.questName .. ":complete")

		-- Complete the quest
		self:completeQuest(pPlayer)
	end

	return 1
end
