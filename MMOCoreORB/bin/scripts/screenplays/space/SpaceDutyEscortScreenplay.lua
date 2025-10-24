SpaceDutyEscortScreenplay = SpaceEscortScreenplay:new {
	className = "SpaceDutyEscortScreenplay",

}

registerScreenPlay("SpaceDutyEscortScreenplay", false)

--[[

		Space Escort Duty Quest Functions

--]]

function SpaceDutyEscortScreenplay:resetDutyMission(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":resetDutyMission called")
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Delete the stored escorted ship ID
	deleteData(playerID .. ":" .. self.className .. ":escortID:")

	-- Delete player location data
	deleteData(playerID .. ":" .. self.className .. ":location:")

	-- Delete Start point
	deleteData(playerID .. self.className .. ":startPoint:")

	-- Delete the distance warnings
	deleteData(playerID .. ":" .. self.className .. ":distanceWarnings:")

	-- Kill Count Tracking
	deleteData(playerID .. ":" .. self.className .. ":" .. ":EscortKillCount:")

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	-- Clear the quest tasks
	SpaceHelpers:clearSpaceQuestTask(pPlayer, self.questType, self.questName, 2, false)
	SpaceHelpers:clearSpaceQuestTask(pPlayer, self.questType, self.questName, 1, false)

	-- Activate quest task 1 again
	SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, false)

	-- Setup the next duty escort for the player
	local randomStart = getRandomNumber(1, #self.escortPoints)
	writeData(playerID .. self.className .. ":startPoint:", randomStart)

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":resetDutyMission called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Escort Point # Selected: " .. randomStart)
	end

	-- Add escort point to the player
	local escortPoint = self.escortPoints[randomStart]
	local waypointID = PlayerObject(pGhost):addWaypoint(escortPoint.zoneName, "Escort Rendevous", "Escort Rendevous", escortPoint.x, escortPoint.z, escortPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
	end

	-- Store the waypointID on the player
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	local dutyUpdate = LuaStringIdChatParameter("@spacequest/" .. self.questType .. "/" .. self.questName .. ":duty_update")
	dutyUpdate:setTO("@spacequest/" .. self.questType .. "/" .. self.questName .. ":found_loc")

	CreatureObject(pPlayer):sendSystemMessage(dutyUpdate:_getObject())
end

function SpaceDutyEscortScreenplay:setupEscort(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to setupEscort due to pPlayer being nil.", LT_ERROR)
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	-- Quest Progress update
	SpaceHelpers:sendQuestProgess(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":title")

	local randomStart = getRandomNumber(1, #self.escortPoints)
	writeData(playerID .. self.className .. ":startPoint:", randomStart)

	if (self.DEBUG_SPACE_ESCORT) then
		print(self.className .. ":setupEscort called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName .. " Escort Point # Selected: " .. randomStart)
	end

	-- Add escort point to the player
	local escortPoint = self.escortPoints[randomStart]
	local waypointID = PlayerObject(pGhost):addWaypoint(escortPoint.zoneName, "Escort Rendevous", "Escort Rendevous", escortPoint.x, escortPoint.z, escortPoint.y, WAYPOINT_SPACE, true, true, WAYPOINTQUESTTASK)

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint ~= nil) then
		WaypointObject(pWaypoint):setQuestDetails("@spacequest/" .. self.questType .. "/" .. self.questName .. ":title_d")
	end

	-- Store the waypointID on the player
	setQuestStatus(playerID .. ":" .. self.className .. ":waypointID", waypointID)

	local dutyUpdate = LuaStringIdChatParameter("@spacequest/" .. self.questType .. "/" .. self.questName .. ":duty_update")
	dutyUpdate:setTO("@spacequest/" .. self.questType .. "/" .. self.questName .. ":found_loc")

	CreatureObject(pPlayer):sendSystemMessage(dutyUpdate:_getObject())
end

--[[

		Space Escort Observers

--]]

function SpaceDutyEscortScreenplay:notifyEnteredQuestArea(pActiveArea, pShip)
	if ((pActiveArea == nil) or (pShip == nil)) then
		return 0
	end

	if (SceneObject(pShip):isPlayerShip()) then
		local pPilot = ShipObject(pShip):getPilot()

		if (pPilot == nil or not SceneObject(pPilot):isPlayerCreature()) then
			return 0
		end

		-- Player is not actively on this quest task
		if (not SpaceHelpers:isSpaceQuestTaskActive(pPilot, self.questType, self.questName, 1)) then
			return 0
		end

		local playerID = SceneObject(pPilot):getObjectID()
		local playerLocation = readData(playerID .. ":" .. self.className .. ":location:")

		-- Check if player is at the correct starting waypoint
		local assignedStart = readData(playerID .. self.className .. ":startPoint:")
		local activeAreaID = SceneObject(pActiveArea):getObjectID()
		local areaEscortNumber = readData(activeAreaID .. ":" .. self.className)

		if (areaEscortNumber ~= assignedStart) then
			return 0
		end

		-- Check to see if player needs to be updated
		if (playerLocation > 1) then
			return 0
		end

		if (self.DEBUG_SPACE_ESCORT) then
			print(self.className .. ":notifyEnteredQuestArea - Player Ship: " .. SceneObject(pShip):getDisplayedName())
		end

		-- Update player count
		writeData(playerID .. ":" .. self.className .. ":location:", 2)

		-- Complete the quest task 1
		SpaceHelpers:completeSpaceQuestTask(pPilot, self.questType, self.questName, 1, false)

		-- Activate quest task 2
		SpaceHelpers:activateSpaceQuestTask(pPilot, self.questType, self.questName, 2, false)

		local dutyUpdate = LuaStringIdChatParameter("@spacequest/" .. self.questType .. "/" .. self.questName .. ":duty_update")
		dutyUpdate:setTO("@spacequest/" .. self.questType .. "/" .. self.questName .. ":arrived_at_loc")

		CreatureObject(pPilot):sendSystemMessage(dutyUpdate:_getObject())

		-- Schedule escort ship spawning
		createEvent(getRandomNumber(5, 11) * 1000, self.className, "spawnEscortShip", pPilot, "")
	elseif (SceneObject(pShip):isShipAiAgent()) then
		local shipAgentID = SceneObject(pShip):getObjectID()
		local playerID = readData(shipAgentID .. ":" .. self.className .. ":escorterID:")

		-- The escort ship will be inside one of the active areas before it can be assigned the data to track its escorting player
		if (playerID == 0) then
			if (self.DEBUG_SPACE_ESCORT) then
				print(self.className .. ":notifyEnteredQuestArea - Escort Ship: " .. SceneObject(pShip):getDisplayedName() .. " owning playerID is 0.")
			end

			return 0
		end

		local escortID = readData(playerID .. ":" .. self.className .. ":escortID:")

		-- Prevent attacking ships triggering escort progress
		if (escortID ~= shipAgentID) then
			if (self.DEBUG_SPACE_ESCORT) then
				print(self.className .. ":notifyEnteredQuestArea - Escort ship does not match the entering shipAgent.")
			end

			return 0
		end

		local pPlayer = getSceneObject(playerID)

		if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() or not SpaceHelpers:isSpaceQuestActive(pPlayer, self.questType, self.questName)) then
			createEvent(1000, self.className, "removeEscortShip", pShip, "")
			return 0
		end

		local shipProgress = readData(shipAgentID .. ":" .. self.className .. ":escortShipProgress:")
		deleteData(shipAgentID .. ":" .. self.className .. ":escortShipProgress:")

		shipProgress = shipProgress - 1

		if (self.DEBUG_SPACE_ESCORT) then
			print(self.className .. ":notifyEnteredQuestArea - Escort Ship: " .. SceneObject(pShip):getDisplayedName() .. " Player Escorting: " .. SceneObject(pPlayer):getDisplayedName() .. " Escort Progress: " .. shipProgress)
		end

		-- Escort is complete
		if (shipProgress <= 0) then
			-- Send Thanks Message to Player
			ShipAiAgent(pShip):tauntPlayer(pPlayer, "@spacequest/" .. self.questType .. "/" .. self.questName .. ":goodbye_" .. tostring(getRandomNumber(1, self.tauntData.goodbyeCount)))

			-- Complete the quest final task 2
			SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 2, false)

			-- Hyperspace out escort ship with thanks message
			createEvent(500, self.className, "removeEscortShip", pShip, "")

			local questUpdate = LuaStringIdChatParameter("@spacequest/" .. self.questType .. "/" .. self.questName .. ":duty_update")
			questUpdate:setTO("@spacequest/" .. self.questType .. "/" .. self.questName .. ":complete")

			CreatureObject(pPlayer):sendSystemMessage(questUpdate:_getObject())

			-- Credit Reward
			local amount = self.creditReward
			local creditKillBonus = self.creditKillBonus
			local totalKills = readData(playerID .. ":" .. self.className .. ":" .. ":EscortKillCount:")

			if (totalKills > 0) then
				amount = amount + (creditKillBonus * totalKills)
			end

			local messageString = LuaStringIdChatParameter("@space/quest:escort_reward")
			messageString:setDI(amount)

			CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject()) -- "\\#pcontrast3 > \\#pcontrast1 Escort complete. Reward: \\#pcontrast2 %DI \\#pcontrast1 credits. \\#pcontrast3 <"

			-- Give the Credits to bank
			CreatureObject(pPlayer):addBankCredits(amount, true)

			-- Reset the duty mission for the next escort
			createEvent(10000, self.className, "resetDutyMission", pPlayer, "")

			return 0
		end

		-- Write the escort ships progress
		writeData(shipAgentID .. ":" .. self.className .. ":escortShipProgress:", shipProgress)

		return 0
	end

	return 0
end