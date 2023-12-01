local QuestManager = require("managers.quest.quest_manager")
local Logger = require("utils.logger")

EnoughQuest = ScreenPlay:new {
	ENABLE_SPACE = false,

	REBEL_CRC = QuestManager.questCRC.QUEST_C_SINK_REB,
	IMPERIAL_CRC = QuestManager.questCRC.QUEST_C_SINK_IMP,

	GO_TO_LOCATION = 0,
	TIMER = 1,
	ENCOUNTER = 2,
	WAIT_FOR_SIGNAL1 = 3,
	REWARD1 = 4,
	DESTROY_MULTI = 5,
	DESTROY_MULTI_AND_LOOT = 6,
	WAIT_FOR_SIGNAL2 = 7,
	WAIT_FOR_SIGNAL3 = 8,
	REWARD2 = 9,
	COMPLETE_QUEST = 10,

	questMobiles = {
		-- Quest Givers
		{"acun_solari", "corellia", 19.8, -0.9, -19.6, 0, 2625356},
		{"ceth_laike", "talus", -2178, 20.0, 2273, 0, 0},

		-- Flail Camp
		{"flail_cutthroat", "corellia", -4751, 28, -1508, 0, 0},
		{"flail_cutthroat", "corellia", -4751, 28, -1510, 0, 0},
		{"flail_executioner", "corellia", -4748, 27, -1524, 0, 0},
		{"flail_slayer", "corellia", -4751, 27, -1521, 0, 0},
		{"flail_enforcer", "corellia", -4736, 28, -1509, 0, 0},

		-- Binayre Pirate Camp
		{"binayre_pirate", "talus", -1631, 22, 617, 0, 0},
		{"binayre_pirate", "talus", -1629, 23, 615, 0, 0},
		{"binayre_pirate", "talus", -1615, 24, 619, 0, 0},
		{"binayre_pirate", "talus", -1623, 23, 620, 0, 0},
		{"binayre_pirate", "talus", -1620, 23, 620, 0, 0},
	},

	flailCrashMobiles = {"flail_cutthroat", "flail_enforcer", "flail_executioner", "flail_killer"},
	binayreCrashMobiles = {"binayre_pirate", "binayre_pirate", "binayre_smuggler", "binayre_ruffian"},
}

registerScreenPlay("EnoughQuest", true)

function EnoughQuest:start()
	self:spawnMobiles()

	self:spawnActiveAreas(EnoughQuest.REBEL_CRC)
	self:spawnActiveAreas(EnoughQuest.IMPERIAL_CRC)
end

function EnoughQuest:spawnMobiles()
	local mobiles = self.questMobiles

	-- Spawn quest mobiles
	for i = 1, #mobiles do
		local mobile = mobiles[i]

		if isZoneEnabled(mobile[2]) then
			spawnMobile(mobile[2], mobile[1], 300, mobile[3], mobile[4], mobile[5], mobile[6], mobile[7])
		end
	end
end

function EnoughQuest:spawnActiveAreas(questCrc)
	local pEnoughTasks = getQuestTasks(questCrc)

	if pEnoughTasks == nil then
		Logger:log("ERROR: Could not load Enough Quests correctly. Quest line will not function correctly.", LT_ERROR)
		return
	end

	local enoughTasks = LuaQuestTasks(pEnoughTasks)

	for taskIndex = 0, enoughTasks:getNumberOfTasks() - 1 do
		local pQuestTask = enoughTasks:getTask(taskIndex)

		if pQuestTask == nil then
			Logger:log("Enough Quest: pQuestTask is nil", LT_ERROR)
			return
		end

		local questTask = LuaQuestTask(pQuestTask)
		local taskName = questTask:getTaskName()

		if isZoneEnabled(questTask:getPlanetName()) and taskName == "gotocrash" then
			local cellid = 0

			local pQuestArea = spawnActiveArea(questTask:getPlanetName(), "object/active_area.iff", questTask:getLocationX(), questTask:getLocationY(), questTask:getLocationZ(), questTask:getRadius(), cellid)

			if pQuestArea == nil then
				Logger:log("Enough Quest: pQuestArea is nil.", LT_ERROR)
				return
			end

			ActiveArea(pQuestArea):setNoBuildArea(true)
			ActiveArea(pQuestArea):setNoSpawnArea(true)

			createObserver(ENTEREDAREA, "EnoughQuest", "notifyEnteredQuestArea", pQuestArea)

			local questAreaID = SceneObject(pQuestArea):getObjectID()

			writeData(questAreaID .. ":EnoughQuestCrc:", questCrc)
			writeData(questAreaID .. ":EnoughTaskIndex:", taskIndex)
		end
	end
end

function EnoughQuest:activeTask(ghost, questCrc, taskIndex)
	if ghost == nil then
		return false
	end

	return ghost:isJournalQuestActive(questCrc) and ghost:isJournalQuestTaskActive(questCrc, taskIndex) and
			not ghost:isJournalQuestComplete(questCrc) and not ghost:isJournalQuestTaskComplete(questCrc, taskIndex)
end

function EnoughQuest:spawnAttack(pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local ghost = LuaPlayerObject(pGhost)

	local questCrc = self.REBEL_CRC
	local mobilesTable = self.flailCrashMobiles

	if CreatureObject(pPlayer):getFaction() == FACTIONIMPERIAL then
		questCrc = self.IMPERIAL_CRC
		mobilesTable = self.binayreCrashMobiles
	end

	-- Complete Timer and start encounter
	ghost:completeJournalQuestTask(questCrc, self.TIMER, false)
	ghost:activateJournalQuestTask(questCrc, self.ENCOUNTER, false)

	local playerX = SceneObject(pPlayer):getPositionX()
	local playerY = SceneObject(pPlayer):getPositionY()
	local zoneName = CreatureObject(pPlayer):getZoneName()

	local totalMobiles = 0
	local playerID = SceneObject(pPlayer):getObjectID()

	for i = 1, #mobilesTable, 1 do
		local x = playerX + getRandomNumber(-25, 25)
		local y = playerY + getRandomNumber(-25, 25)

		local pMobile = spawnMobile(zoneName, mobilesTable[i], -1, x, getWorldFloor(x, y, zoneName), y, 0, 0)

		if (pMobile ~= nil) then
			-- add death observer
			createObserver(OBJECTDESTRUCTION, "EnoughQuest", "notifyCrashMobileKilled", pMobile)

			-- Store owning players ID on the mobile
			writeData(SceneObject(pMobile):getObjectID() .. ":EnoughQuest:crashMobilePlayerID:", playerID)

			totalMobiles = totalMobiles + 1

			-- Attack the player
			AiAgent(pMobile):setDefender(pPlayer)
		end
	end

	writeData(playerID .. ":EnoughQuest:totalCrashMobiles:", totalMobiles)
end

--[[

	Enough Quest Observers

]]

function EnoughQuest:notifyEnteredQuestArea(pActiveArea, pPlayer)
	if (pActiveArea == nil) or (pPlayer == nil) then
		return 0
	end

	if not SceneObject(pActiveArea):isActiveArea() or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local activeAreaID = SceneObject(pActiveArea):getObjectID()
	local questCrc = readData(activeAreaID .. ":EnoughQuestCrc:")
	local taskIndex = readData(activeAreaID .. ":EnoughTaskIndex:")

	local pEnoughTasks = getQuestTasks(questCrc)

	if pEnoughTasks == nil then
		Logger:log("ERROR: Could not load Enough Quests correctly. Quest line will not function correctly.", LT_ERROR)
		return
	end

	local enoughTasks = LuaQuestTasks(pEnoughTasks)

	local creature = LuaCreatureObject(pPlayer)
	local pGhost = creature:getPlayerObject()

	if pGhost == nil then
		return 0
	end

	local ghost = LuaPlayerObject(pGhost)

	if self:activeTask(ghost, questCrc, taskIndex) then
		ghost:completeJournalQuestTask(questCrc, self.GO_TO_LOCATION, true)
		ghost:activateJournalQuestTask(questCrc, self.TIMER, false)

		createEvent(5000, "EnoughQuest", "spawnAttack", pPlayer, "")
	end

	return 0
end

function EnoughQuest:notifyCrashMobileKilled(pMobile, pKiller)
	if (pMobile == nil) then
		return 1
	end

	local mobileID = SceneObject(pMobile):getObjectID()

	local playerID = readData(mobileID .. ":EnoughQuest:crashMobilePlayerID:")
	local totalMobiles = readData(playerID .. ":EnoughQuest:totalCrashMobiles:")

	deleteData(mobileID .. ":EnoughQuest:crashMobilePlayerID:")

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

		if CreatureObject(pPlayer):getFaction() == FACTIONIMPERIAL then
			questCrc = self.IMPERIAL_CRC
		end

		-- Complete Go to location and Encounter then start wait for signal 1
		ghost:completeJournalQuestTask(questCrc, self.GO_TO_LOCATION, true)
		ghost:completeJournalQuestTask(questCrc, self.ENCOUNTER, true)

		ghost:activateJournalQuestTask(questCrc, self.WAIT_FOR_SIGNAL1, true)

		-- Delete the flail mobiles count
		deleteData(playerID .. ":EnoughQuest:totalCrashMobiles:")

		-- Remove the waypoint from the player of the pilot
		local waypointID = tonumber(readScreenPlayData(pPlayer, "EnoughQuest", "PilotWaypointID"))
		ghost:removeWaypoint(waypointID, true)

		deleteScreenPlayData(pPlayer, "EnoughQuest", "PilotWaypointID")

		return 1
	end

	writeData(playerID .. ":EnoughQuest:totalCrashMobiles:", totalMobiles)

	return 0
end

function EnoughQuest:notifyKilledCreature(pPlayer, pVictim)
	if (pPlayer == nil or pVictim == nil or not SceneObject(pVictim):isAiAgent()) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local victimName = SceneObject(pVictim):getObjectName()

	local questCrc = self.REBEL_CRC

	if CreatureObject(pPlayer):getFaction() == FACTIONIMPERIAL then
		questCrc = self.IMPERIAL_CRC
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return 0
	end

	local ghost = LuaPlayerObject(pGhost)
	local taskIndex = -1

	if self:activeTask(ghost, questCrc, self.DESTROY_MULTI) then
		taskIndex = self.DESTROY_MULTI
	elseif self:activeTask(ghost, questCrc, self.DESTROY_MULTI_AND_LOOT) then
		taskIndex = self.DESTROY_MULTI_AND_LOOT
	else
		return 0
	end

	local pEnoughTasks = getQuestTasks(questCrc)

	if pEnoughTasks == nil then
		Logger:log("ERROR: Could not load Enough Quest Tasks.", LT_ERROR)
		return 0
	end

	local enoughTasks = LuaQuestTasks(pEnoughTasks)
	local pQuestTask = enoughTasks:getTask(taskIndex)

	if (pQuestTask == nil) then
		Logger:log("ERROR: Could not load Enough Quest Task - DESTROY_MULTI.", LT_ERROR)
		return 0
	end

	local questTask = LuaQuestTask(pQuestTask)
	local victimSocialGroup = AiAgent(pVictim):getSocialGroup()

	if victimSocialGroup ~= questTask:getSocialGroup() then
		return 0
	end

	if (taskIndex == self.DESTROY_MULTI) then
		local killCount = getQuestStatus(playerID .. ":EnoughQuest:DestroyMultiCount:")

		if (killCount == nil) then
			killCount = 1
		else
			killCount = tonumber(killCount) + 1
		end

		CreatureObject(pPlayer):sendSystemMessage("Killed: " .. killCount) -- ("destroy_counter", "Killed");
		setQuestStatus(playerID .. ":EnoughQuest:DestroyMultiCount:", killCount)

		-- Kill 15 Flails
		if killCount >= questTask:getCount() then
			PlayerObject(pGhost):completeJournalQuestTask(questCrc, self.DESTROY_MULTI, true)
			PlayerObject(pGhost):activateJournalQuestTask(questCrc, self.DESTROY_MULTI_AND_LOOT, true)

			local waypointID = 0

			if (questCrc == self.REBEL_CRC) then
				waypointID = tonumber(readScreenPlayData(pPlayer, "EnoughQuest", "KilllWaypointID"))
			else
				waypointID = tonumber(readScreenPlayData(pPlayer, "EnoughQuest", "KilllWaypointID"))
			end

			PlayerObject(pGhost):removeWaypoint(waypointID, true)

			deleteScreenPlayData(pPlayer, "EnoughQuest", "KilllWaypointID")

			-- Do not remove observer, needed for next task
		end
	elseif (taskIndex == self.DESTROY_MULTI_AND_LOOT) then
		local roll = getRandomNumber(1, 101)

		if (questTask:getLootDropPercent() < roll) then
			return 0
		end

		local gangSymbols = getQuestStatus(playerID .. ":EnoughQuest:DestroyMultiLootCount:")
		local symbolsNeeded = questTask:getLootItemsRequired()

		if (gangSymbols == nil) then
			gangSymbols = 1
		else
			gangSymbols = tonumber(gangSymbols) + 1
		end

		-- Update Quest status for amount looted
		setQuestStatus(playerID .. ":EnoughQuest:DestroyMultiLootCount:", gangSymbols)

		local fullMsg = LuaStringIdChatParameter("@quest/groundquests:retrieve_item_success") -- "Item found. %DI remaining."
		fullMsg:setDI(symbolsNeeded - gangSymbols)

		CreatureObject(pPlayer):sendSystemMessage("Retrieved: " .. questTask:getLootItemName()) -- ("retrieve_item_counter", "Retrieved");
		CreatureObject(pPlayer):sendSystemMessage(fullMsg:_getObject())

		if gangSymbols >= symbolsNeeded then
			-- Update Quest Journal
			PlayerObject(pGhost):completeJournalQuestTask(questCrc, self.DESTROY_MULTI_AND_LOOT, true)
			PlayerObject(pGhost):activateJournalQuestTask(questCrc, self.WAIT_FOR_SIGNAL2, true)

			-- Remove Binayre camp waypoint
			local waypointID = tonumber(readScreenPlayData(pPlayer, "EnoughQuest", "LootWaypointID"))
			PlayerObject(pGhost):removeWaypoint(waypointID, true)

			deleteScreenPlayData(pPlayer, "EnoughQuest", "LootWaypointID")

			return 1
		end
	end

	return 0
end