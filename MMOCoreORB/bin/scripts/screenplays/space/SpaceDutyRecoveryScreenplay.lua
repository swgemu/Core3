SpaceDutyRecoveryScreenplay = SpaceRecoveryScreenplay:new {
	className = "SpaceDutyRecoveryScreenplay",

	-- Screenplay Specific Variables

	DEBUG_SPACE_DUTY_RECOVERY = false,

	arrivalDelay = 5, -- In Seconds

	recoverShip = "",
	recoveryConversationMobile = "",

	preRecoveryPoints = {
		--{patrolPointName = "", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	recoveryPoints = {
		--{patrolPointName = "", x = -4381, z = -4943, y = -7262, patrolNumber = 1, radius = 150},
	},

	escortSpeed = 20,
	testEscortSpeed = 60,

	attackDelay = 30, -- In Seconds

	attackShips = {
		{},
	},

	recoveryDelay = 5,

	tauntData = {
		panicCount = 5,
		thanksCount = 5,
	},

	killReward = 0,
}

registerScreenPlay("SpaceDutyRecoveryScreenplay", false)

--[[

		Space Duty Recovery Quest Functions

--]]

function SpaceDutyRecoveryScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":startQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	if (pNpc == "") then
		pNpc = nil
	end

	-- Reset the Duty Mission
	self:resetDutyMission(pPlayer)

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

function SpaceDutyRecoveryScreenplay:resetDutyMission(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to resetQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":resetQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Despawn Any ships
	self:despawnShips(pPlayer)

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, false)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()

	local failedType = readData(playerID .. self.className .. ":failedType:")
	deleteData(playerID .. self.className .. ":failedType:")

	-- Clean Up data last
	self:cleanUpQuestData(playerID)
end

function SpaceDutyRecoveryScreenplay:grantDutyReward(pPlayer, killsString)
	if (pPlayer == nil) then
		return
	end

	local creditReward = self.creditReward
	local totalKills = tonumber(killsString)

	creditReward = creditReward + (totalKills * self.killReward)

	local dutyReward = LuaStringIdChatParameter("@space/quest:recovery_reward")
	dutyReward:setDI(creditReward)

	CreatureObject(pPlayer):sendSystemMessage(dutyReward:_getObject())

	-- Give completion reward credits
	CreatureObject(pPlayer):addBankCredits(creditReward, true)
end

--[[

		Space Escort Observers

--]]

function SpaceDutyRecoveryScreenplay:notifyEnteredQuestArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil)) then
		return 0
	end

	if (not SceneObject(pShip):isShipAiAgent()) then
		return 0
	end

	local shipAgentID = SceneObject(pShip):getObjectID()
	local missionOwnerID = ShipAiAgent(pShip):getMissionOwnerID()
	local recoveryShipID = readData(missionOwnerID .. self.className .. ":recoveryShip:")

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyEnteredQuestArea - Ship ID: " .. shipAgentID .. " Recovery Ship ID: " .. recoveryShipID .. " Mission Owner ID: " .. missionOwnerID)
	end

	-- Prevent attacking ships triggering escort progress
	if (recoveryShipID ~= shipAgentID) then
		return 0
	end

	local pPlayer = getSceneObject(missionOwnerID)

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	if (not SceneObject(pPlayer):isPlayerCreature() or not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
		createEvent(1000, self.className, "failQuest", pPlayer, "false")
		return 0
	end

	local shipProgress = readData(shipAgentID .. ":" .. self.className .. ":recoveryShipProgress:")
	deleteData(shipAgentID .. ":" .. self.className .. ":recoveryShipProgress:")

	shipProgress = shipProgress - 1

	if (self.DEBUG_SPACE_RECOVERY) then
		print(self.className .. ":notifyEnteredQuestArea - Recovery Ship: " .. SceneObject(pShip):getDisplayedName() .. " Player Escorting: " .. SceneObject(pPlayer):getDisplayedName() .. " Recovery Progress: " .. shipProgress)
	end

	-- Escort is not complete
	if (shipProgress > 0) then
		-- Write the escort ships progress
		writeData(shipAgentID .. ":" .. self.className .. ":recoveryShipProgress:", shipProgress)

		return 0
	end

	-- Complete the quest final task 3
	SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 3, false)

	local questUpdate = LuaStringIdChatParameter("@spacequest/" .. self.questType .. "/" .. self.questName .. ":quest_update")
	questUpdate:setTO("@spacequest/" .. self.questType .. "/" .. self.questName .. ":recovery_success")

	CreatureObject(pPlayer):sendSystemMessage(questUpdate:_getObject())

	-- Send Complete Message to Player & Group
	ShipAiAgent(pShip):tauntPlayer(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":complete")

	-- Complete quest
	createEvent(1000, self.className, "completeQuest", pPlayer, "true")

	local totalKills = readData(missionOwnerID .. self.className .. ":killCount:")

	-- Grant Reward
	createEvent(2000, self.className, "grantDutyReward", pPlayer, totalKills)

	local spaceQuestHash = getHashCode(self.questZone)
	local zoneName = SceneObject(pPlayer):getZoneName()
	local playerZoneHash = getHashCode(zoneName)

	if (spaceQuestHash == playerZoneHash) then
		-- Call Start to reset duty mission
		createEvent(10 * 1000, self.className, "startQuest", pPlayer, "true")
	end

	return 0
end
