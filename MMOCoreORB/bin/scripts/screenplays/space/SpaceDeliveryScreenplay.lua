SpaceDeliveryScreenplay = SpaceQuestLogic:new {
	className = "SpaceDeliveryScreenplay",

}

registerScreenPlay("SpaceDeliveryScreenplay", false)

--[[

		Space Recovery Quest Functions

--]]

function SpaceDeliveryScreenplay:start()
end

function SpaceDeliveryScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DELIVERY) then
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
	local pRootParent = SceneObject(pPlayer):getRootParent()

	-- Check if the player is in the proper zone already
	if (playerZoneHash == spaceQuestHash and not SpaceHelpers:isInYacht(pPlayer)) then
		-- Complete the quest task 0
		SpaceHelpers:completeSpaceQuestTask(pPlayer, self.questType, self.questName, 0, false)

		-- Activate quest task 1
		SpaceHelpers:activateSpaceQuestTask(pPlayer, self.questType, self.questName, 1, true)
	end

	-- Create inital observer for player entering Zone and to handle failing quest
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end

	-- REMOVE AFTER IMPLEMENTATION
	createEvent(500, self.className, "completeQuest", pPlayer, "true")
end

function SpaceDeliveryScreenplay:completeQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DELIVERY) then
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

	if (self.sideQuest and (self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.COMPLETION or self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.BIDIRECTIONAL)) then
		local alertMessage = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":split_quest_alert"

		-- Split Quest Alert
		createEvent(self.sideQuestDelay * 1000, "SpaceHelpers", "sendQuestAlert", pPlayer, alertMessage)

		-- Trigger Sidequest
		createEvent(self.sideQuestDelay * 1050, self.sideQuestType .. "_" .. self.sideQuestName, "startQuest", pPlayer, "")
	end
end

function SpaceDeliveryScreenplay:failQuest(pPlayer, notifyClient)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to failQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DELIVERY) then
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
		createEvent(200, self.parentQuestType .. "_" .. self.parentQuestName, "failQuest", pPlayer, "false")
	end

	-- Fail the side quest
	if (self.sideQuest and SpaceHelpers:isSpaceQuestActive(pPlayer, self.sideQuestType, self.sideQuestName)) then
		createEvent(200, self.sideQuestType .. "_" .. self.sideQuestName, "failQuest", pPlayer, "false")
	end

	if (self.sideQuest and (self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.FAILURE or self.sideQuestSplitType == self.SIDE_QUEST_SPLIT_TYPES.BIDIRECTIONAL)) then
		local alertMessage = "@spacequest/" .. self.questType .. "/" .. self.questName .. ":split_quest_alert"

		-- Split Quest Alert
		createEvent(self.sideQuestDelay * 1000, "SpaceHelpers", "sendQuestAlert", pPlayer, alertMessage)

		-- Trigger Sidequest
		createEvent(self.sideQuestDelay * 1050, self.sideFailQuestType .. "_" .. self.sideFailQuestName, "startQuest", pPlayer, "")
	end
end

function SpaceDeliveryScreenplay:resetQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log(self.questName .. " Type: " .. self.questType .. " -- Failed to resetQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.DEBUG_SPACE_DELIVERY) then
		print(self.className .. ":resetQuest called -- QuestType: " .. self.questType .. " Quest Name: " .. self.questName)
	end

	-- Set Quest failed
	SpaceHelpers:failSpaceQuest(pPlayer, self.questType, self.questName, false)

	-- Remove any patrol points
	SpaceHelpers:clearQuestWaypoint(pPlayer, self.className)

	-- Remove the zone entry observer
	dropObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)

	self:cleanUpQuestData(SceneObject(pPlayer):getObjectID())
end

function SpaceDeliveryScreenplay:cleanUpQuestData(playerID)
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
end

--[[

		Space Delivery Observers

--]]

function SpaceDeliveryScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
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

	local pRootParent = SceneObject(pPlayer):getRootParent()

	if (pRootParent ~= nil and SceneObject(pRootParent):getObjectName() == "player_sorosuub_space_yacht") then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local spaceQuestHash = getHashCode(self.questZone)




	return 1
end