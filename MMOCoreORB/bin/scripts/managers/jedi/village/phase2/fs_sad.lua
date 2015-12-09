local ObjectManager = require("managers.object.object_manager")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")
local QuestManager = require("managers.quest.quest_manager")
local FsSadTheater1 = require("managers.jedi.village.phase2.fs_sad_1_theaters.fs_sad_1_theater_1")
local FsSadTheater2 = require("managers.jedi.village.phase2.fs_sad_1_theaters.fs_sad_1_theater_2")
local FsSadTheater3 = require("managers.jedi.village.phase2.fs_sad_1_theaters.fs_sad_1_theater_3")
local FsSadTheater4 = require("managers.jedi.village.phase2.fs_sad_1_theaters.fs_sad_1_theater_4")
local FsSadTheater5 = require("managers.jedi.village.phase2.fs_sad_1_theaters.fs_sad_1_theater_5")
local FsSadTheater6 = require("managers.jedi.village.phase2.fs_sad_1_theaters.fs_sad_1_theater_6")
local FsSadTheater7 = require("managers.jedi.village.phase2.fs_sad_1_theaters.fs_sad_1_theater_7")
local FsSadTheater8 = require("managers.jedi.village.phase2.fs_sad_1_theaters.fs_sad_1_theater_8")

FsSad = Object:new {
	--timePeriod = 24 * 60 * 60, -- 24 Hours
	timePeriod = 1 * 60 * 60, -- 1 hour for testing
	tasksPerPeriod = 3,
	theaterTable = { FsSadTheater1, FsSadTheater2, FsSadTheater3, FsSadTheater4, FsSadTheater5, FsSadTheater6, FsSadTheater7, FsSadTheater8 }
}

function FsSad:hasExceededLimit(pPlayer)
	local lastTimestamp = self:getLastTimestamp(pPlayer)
	local tasksSinceLast = self:getTasksSinceLastTimestamp(pPlayer)

	if ((os.difftime(os.time(), lastTimestamp) < self.timePeriod) and tasksSinceLast >= self.tasksPerPeriod) then
		return true
	end

	return false
end

function FsSad:updateLastTimestamp(pPlayer)
	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsSadLastLimitReset", os.time())
end

function FsSad:getLastTimestamp(pPlayer)
	local lastTimestamp = readScreenPlayData(pPlayer, "VillageJediProgression", "FsSadLastLimitReset")

	if (lastTimestamp == "") then
		self:updateLastTimestamp(pPlayer)
		return os.time()
	end

	return tonumber(lastTimestamp)
end

function FsSad:setTasksSinceLastTimestamp(pPlayer, count)
	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsSadTasksSinceLastTimestamp", count)
end

function FsSad:getTasksSinceLastTimestamp(pPlayer)
	local count = readScreenPlayData(pPlayer, "VillageJediProgression", "FsSadTasksSinceLastTimestamp")

	if (count == "") then
		count = 0
		self:setTasksSinceLastTimestamp(pPlayer, count)
	end

	return tonumber(count)
end

function FsSad:acceptNextTask(pPlayer)
	local lastTimestamp = self:getLastTimestamp(pPlayer)

	if (os.difftime(os.time(), lastTimestamp) > self.timePeriod) then
		self:updateLastTimestamp(pPlayer)
		self:setTasksSinceLastTimestamp(pPlayer, 1)
	else
		local tasksSinceLast = self:getTasksSinceLastTimestamp(pPlayer)
		self:setTasksSinceLastTimestamp(pPlayer, tasksSinceLast + 1)
	end

	if (not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_TASKS) and not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_TASKS)) then
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_TASKS)
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer)

		if (not SuiRadiationSensor:hasSensor(pPlayer)) then
			SuiRadiationSensor:giveSensor(pPlayer)
		end

		self:startTask(pPlayer, QuestManager.quests.FS_QUESTS_SAD_TASK1, 1)
	else
		for i = 1, 8, 1 do
			local questID = getPlayerQuestID("fs_quests_sad_return" .. i)

			if QuestManager.hasActiveQuest(pPlayer, questID) then
				QuestManager.completeQuest(pPlayer, questID)
				self:finishOldTask(pPlayer, i)

				if (i == 8) then
					self:completeSeries(pPlayer, questID)
				else
					local newQuestID = getPlayerQuestID("fs_quests_sad_task" .. i + 1)
					self:startTask(pPlayer, newQuestID, i + 1)
				end
			else
			end
		end
	end
end

function FsSad:completeSeries(pPlayer, questID)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_TASKS)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_FINISH)
	VillageJediManagerCommon.setCompletedQuestThisPhase(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_finished")
	VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_combat_prowess_melee_speed")
	SuiRadiationSensor:removeSensor(pPlayer)

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pPowerup = giveItem(pInventory, "object/tangible/powerup/weapon/fs_quest_sad/melee_speed_quest.iff", -1, true)

		if (pPowerup == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
		end
	end
end

function FsSad:doPhaseChangeFail(pPlayer)
	if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_TASKS) or QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_FINISH)) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/quest_journal/fs_quests_sad:wrong_phase")

	if QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_TASKS) or QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_TASKS) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD_TASKS)
	end

	for i = 1, 8, 1 do
		local questName = "fs_quests_sad_task" .. i
		local questID = getPlayerQuestID(questName)

		if QuestManager.hasCompletedQuest(pPlayer, questID) or QuestManager.hasActiveQuest(pPlayer, questID) then
			QuestManager.resetQuest(pPlayer, questID)
		end
	end
	
	SuiRadiationSensor:removeSensor(pPlayer)
end

function FsSad:finishOldTask(pPlayer, questNum)
	local FsSadTheater = self.theaterTable[questNum]

	FsSadTheater:finish(pPlayer)
end

function FsSad:startTask(pPlayer, questID, questNum)
	QuestManager.activateQuest(pPlayer, questID)

	local FsSadTheater = self.theaterTable[questNum]

	FsSadTheater:start(pPlayer)
end

function FsSad:hasActiveReturnTask(pPlayer)
	for i = 1, 8, 1 do
		local questID = getPlayerQuestID("fs_quests_sad_return" .. i)

		if QuestManager.hasActiveQuest(pPlayer, questID) then
			return true
		end
	end

	return false
end

function FsSad:hasActiveNonReturnTask(pPlayer)
	for i = 1, 8, 1 do
		local questID = getPlayerQuestID("fs_quests_sad_task" .. i)

		if QuestManager.hasActiveQuest(pPlayer, questID) then
			return true
		end
	end

	return false
end

function FsSad:hasFullInventory(pPlayer)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return true
	end

	return SceneObject(pInventory):isContainerFullRecursive()
end

return FsSad
