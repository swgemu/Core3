local QuestManager = require("managers.quest.quest_manager")
local Logger = require("utils.logger")

DefectorQuest = ScreenPlay:new {
	ENABLE_SPACE = false,

	IMPERIAL_CRC = QuestManager.questCRC.QUEST_C_IMPDEFECTOR,
	REBEL_CRC = QuestManager.questCRC.QUEST_C_REBDEFECTOR,

	GO_TO_LOCATION = 0,
	WAIT_FOR_SIGNAL1 = 1,
	TIMER1 = 2,
	ENCOUNTER1 = 3,
	TIMER2 = 4,
	ENCOUNTER2 = 5,
	WAIT_FOR_SIGNAL2 = 6,
	REWARD1 = 7,
	REWARD2 = 8,
	COMPLETE_QUEST = 9,
	TIMER3 = 10,
	ENCOUNTER3 = 11,
	TIMER4 = 12,
	CLEAR_QUEST = 13,

	questMobiles = {
		-- Quest Givers
		{"jom_irimore", "corellia", -5520, 21, -2631, -100, 0},
		{"jaek_vercet", "naboo", -2.3, 1.1, -2.6, 81, 1717552},

		-- Quest Receivers
		{"teslo_tendoora", "corellia", -6485, 398, 6017, 0, 0},
		{"allard_lissara", "naboo", 2415, 292, -3948, 35, 0},

		-- Defectors
		{"imperial_defector", "corellia", -4296, 18, 3801, 0, 0},
		{"rebel_defector", "naboo", 4653, 0, -4412, 0, 0},
	},

	rebelAmbushMobiles = {"mercenary_hireling_reb"},
	imperialAmbushMobiles = {"mercenary_hireling_imp"},

	waypointNames = {
		"impQuestGiverWaypointID", "impDefectorWaypointID", "impQuestReceiverWaypointID",
		"rebQuestGiverWaypointID", "rebDefectorWaypointID", "rebQuestReceiverWaypointID"
	},
}

registerScreenPlay("DefectorQuest", true)

function DefectorQuest:start()
	self:spawnMobiles()

	self:spawnActiveAreas(DefectorQuest.REBEL_CRC)
	self:spawnActiveAreas(DefectorQuest.IMPERIAL_CRC)
end

function DefectorQuest:spawnMobiles()
	local mobiles = self.questMobiles

	-- Spawn quest mobiles
	for i = 1, #mobiles do
		local mobile = mobiles[i]

		if isZoneEnabled(mobile[2]) then
			spawnMobile(mobile[2], mobile[1], 300, mobile[3], mobile[4], mobile[5], mobile[6], mobile[7])
		end
	end
end

function DefectorQuest:spawnActiveAreas(questCrc)
	local pDefectorTasks = getQuestTasks(questCrc)

	if pDefectorTasks == nil then
		Logger:log("ERROR: Could not load Defector Quests correctly. Quest line will not function correctly.", LT_ERROR)
		return
	end

	local defectorTasks = LuaQuestTasks(pDefectorTasks)

	for taskIndex = 0, defectorTasks:getNumberOfTasks() - 1 do
		local pQuestTask = defectorTasks:getTask(taskIndex)

		if pQuestTask == nil then
			Logger:log("Defector Quest: pQuestTask is nil", LT_ERROR)
			return
		end

		local questTask = LuaQuestTask(pQuestTask)

		if isZoneEnabled(questTask:getPlanetName()) and taskIndex == 0 then
			local pQuestArea = spawnActiveArea(questTask:getPlanetName(), "object/active_area.iff", questTask:getLocationX(), questTask:getLocationY(), questTask:getLocationZ(), questTask:getRadius(), 0)

			if pQuestArea == nil then
				Logger:log("Defector Quest: pQuestArea is nil.", LT_ERROR)
				return
			end

			ActiveArea(pQuestArea):setNoBuildArea(true)
			ActiveArea(pQuestArea):setNoSpawnArea(true)

			createObserver(ENTEREDAREA, "DefectorQuest", "notifyEnteredQuestArea", pQuestArea)

			local questAreaID = SceneObject(pQuestArea):getObjectID()

			if questCrc == self.REBEL_CRC then
				writeData(questAreaID .. ":DefectorQuestRebelCrc:", questCrc)
			elseif questCrc == self.IMPERIAL_CRC then
				writeData(questAreaID .. ":DefectorQuestImperialCrc:", questCrc)
			end

			writeData(questAreaID .. ":DefectorTaskIndex:", taskIndex)
		end
	end
end

function DefectorQuest:activeTask(ghost, questCrc, taskIndex)
	if ghost == nil then
		return false
	end

	return ghost:isJournalQuestActive(questCrc) and ghost:isJournalQuestTaskActive(questCrc, taskIndex) and
			not ghost:isJournalQuestComplete(questCrc) and not ghost:isJournalQuestTaskComplete(questCrc, taskIndex)
end

function DefectorQuest:startMissionTimer(pPlayer)

	-- 20-Minute Overall Mission Timer
	createEvent(20 * 60 * 1000, "DefectorQuest", "failMission", pPlayer, "")

end

function DefectorQuest:spawnAttack(pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)
	local playerID = SceneObject(pPlayer):getObjectID()

	local questCrc = self.REBEL_CRC
	local mobilesTable = self.imperialAmbushMobiles
	local numMobiles = 0

	if not (ghost:isJournalQuestActive(self.REBEL_CRC) or ghost:isJournalQuestActive(IMPERIAL_CRC)) then
		return
	end

	if ghost:isJournalQuestActive(self.IMPERIAL_CRC) then
		questCrc = self.IMPERIAL_CRC
		mobilesTable = self.rebelAmbushMobiles
	end

	-- Start encounter
	local pDefectorTasks = getQuestTasks(questCrc)

	if pDefectorTasks == nil then
		Logger:log("ERROR: Could not load Defector Quests correctly. Quest line will not function correctly.", LT_ERROR)
		return
	end

	local defectorTasks = LuaQuestTasks(pDefectorTasks)
	local pQuestTask = defectorTasks:getTask(self.ENCOUNTER3)

	if ghost:isJournalQuestTaskActive(questCrc, self.TIMER3) then
		ghost:completeJournalQuestTask(questCrc, self.TIMER3, false)
		ghost:activateJournalQuestTask(questCrc, self.ENCOUNTER3, true)

	elseif ghost:isJournalQuestTaskActive(questCrc, self.TIMER2) then
		ghost:completeJournalQuestTask(questCrc, self.TIMER2, false)
		ghost:activateJournalQuestTask(questCrc, self.ENCOUNTER2, true)
		pQuestTask = defectorTasks:getTask(self.ENCOUNTER2)

	elseif ghost:isJournalQuestTaskActive(questCrc, self.TIMER1) then
		ghost:completeJournalQuestTask(questCrc, self.TIMER1, false)
		ghost:activateJournalQuestTask(questCrc, self.ENCOUNTER1, true)
		pQuestTask = defectorTasks:getTask(self.ENCOUNTER1)

	end

	-- Spawn mobiles
	local playerX = SceneObject(pPlayer):getPositionX()
	local playerY = SceneObject(pPlayer):getPositionY()
	local zoneName = CreatureObject(pPlayer):getZoneName()

	local totalMobiles = 0

	if pQuestTask == nil then
		Logger:log("Defector Quest: pQuestTask is nil", LT_ERROR)
		return
	end

	local questTask = LuaQuestTask(pQuestTask)

	for i = 1, questTask:getCount(), 1 do
		local x = playerX + getRandomNumber(-10, 10)
		local y = playerY + getRandomNumber(-10, 10)

		local pMobile = spawnMobile(zoneName, mobilesTable[1], -1, x, getWorldFloor(x, y, zoneName), y, 0, 0)

		if (pMobile ~= nil) then
			-- add death observer
			createObserver(OBJECTDESTRUCTION, "DefectorQuest", "notifyAmbushMobileKilled", pMobile)

			-- Store owning player's ID on the mobile
			writeData(SceneObject(pMobile):getObjectID() .. ":DefectorQuest:ambushMobilePlayerID:", playerID)

			totalMobiles = totalMobiles + 1

			-- Attack the player
			AiAgent(pMobile):setDefender(pPlayer)
		end
	end

	writeData(playerID .. ":DefectorQuest:totalAmbushMobiles:", totalMobiles)
end

--[[

	Defector Quest Observers

--]]

function DefectorQuest:notifyEnteredQuestArea(pActiveArea, pPlayer)
	if (pActiveArea == nil) or (pPlayer == nil) then
		return 0
	end

	if not SceneObject(pActiveArea):isActiveArea() or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return 0
	end

	local ghost = LuaPlayerObject(pGhost)
	local activeAreaID = SceneObject(pActiveArea):getObjectID()
	local taskIndex = readData(activeAreaID .. ":DefectorTaskIndex:")
	local questCrc = nil

	if ghost:isJournalQuestActive(self.REBEL_CRC) then
		questCrc = readData(activeAreaID .. ":DefectorQuestRebelCrc:")
	elseif ghost:isJournalQuestActive(self.IMPERIAL_CRC) then
		questCrc = readData(activeAreaID .. ":DefectorQuestImperialCrc:")
	end

	local pDefectorTasks = getQuestTasks(questCrc)

	if pDefectorTasks == nil then
		Logger:log("ERROR: Could not load Defector Quests correctly. Quest line will not function correctly.", LT_ERROR)
		return
	end

	local defectorTasks = LuaQuestTasks(pDefectorTasks)

	local pQuestTask = defectorTasks:getTask(taskIndex)

	if pQuestTask == nil then
		Logger:log("Defector Quest: pQuestTask is nil", LT_ERROR)
		return
	end

	if self:activeTask(ghost, questCrc, taskIndex) then
		ghost:completeJournalQuestTask(questCrc, self.GO_TO_LOCATION, true)
		ghost:activateJournalQuestTask(questCrc, self.WAIT_FOR_SIGNAL1, true)
	end

	return 0
end

function DefectorQuest:failMission(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)
	local questCrc = self.REBEL_CRC

	if ghost:isJournalQuestActive(self.IMPERIAL_CRC) then
		questCrc = self.IMPERIAL_CRC
	end

	ghost:clearJournalQuest(questCrc, true)

	-- Remove waypoints from the player
	local waypoints = self.waypointNames

	for i = 1, #waypoints do
		local waypointID = readScreenPlayData(pPlayer, "DefectorQuest", waypoints[i])
		ghost:removeWaypoint(waypointID, true)

		deleteScreenPlayData(pPlayer, "DefectorQuest", waypointID)
	end

	-- Drop observers and cancel spawn events
	dropObserver(ENTEREDAREA, "DefectorQuest", "notifyEnteredQuestArea", pQuestArea)
	dropObserver(OBJECTDESTRUCTION, "DefectorQuest", "notifyAmbushMobileKilled", pMobile)

end

function DefectorQuest:notifyAmbushMobileKilled(pMobile, pKiller)
	if (pMobile == nil) then
		return 1
	end

	local mobileID = SceneObject(pMobile):getObjectID()

	local playerID = readData(mobileID .. ":DefectorQuest:ambushMobilePlayerID:")
	local totalMobiles = readData(playerID .. ":DefectorQuest:totalAmbushMobiles:")

	deleteData(mobileID .. ":DefectorQuest:ambushMobilePlayerID:")

	totalMobiles = totalMobiles - 1

	if (totalMobiles <= 0) then
		local pPlayer = getSceneObject(playerID)

		if (pPlayer == nil or not SceneObject(pPlayer):isCreatureObject()) then
			return 0
		end

		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if pGhost == nil then
			return 0
		end

		local ghost = LuaPlayerObject(pGhost)
		local questCrc = self.REBEL_CRC

		if ghost:isJournalQuestActive(self.IMPERIAL_CRC) then
			questCrc = self.IMPERIAL_CRC
		end

		-- Complete Encounter
		if ghost:isJournalQuestTaskActive(questCrc, self.ENCOUNTER3) then
			ghost:completeJournalQuestTask(questCrc, self.ENCOUNTER3, true)
			ghost:activateJournalQuestTask(questCrc, self.TIMER2, false)
			createEvent(getRandomNumber(190, 230) * 1000, "DefectorQuest", "spawnAttack", pPlayer, "")

		elseif ghost:isJournalQuestTaskActive(questCrc, self.ENCOUNTER2) then
			ghost:completeJournalQuestTask(questCrc, self.ENCOUNTER2, true)
			ghost:activateJournalQuestTask(questCrc, self.TIMER1, false)
			createEvent(getRandomNumber(410, 470) * 1000, "DefectorQuest", "spawnAttack", pPlayer, "")

		elseif ghost:isJournalQuestTaskActive(questCrc, self.ENCOUNTER1) then
			ghost:completeJournalQuestTask(questCrc, self.ENCOUNTER1, true)

		end

		-- Delete the ambush mobiles count
		deleteData(playerID .. ":DefectorQuest:totalAmbushMobiles:")

		return 1
	end

	writeData(playerID .. ":DefectorQuest:totalAmbushMobiles:", totalMobiles)

	return 0
end
