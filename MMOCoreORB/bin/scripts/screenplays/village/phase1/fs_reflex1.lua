local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsReflex1 = ScreenPlay:new {}

function FsReflex1:startQuest(pPlayer)
	self:setRescueCount(pPlayer, 0)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00)
	FsReflex1Goto:start(pPlayer)
end

function FsReflex1:startNextRescue(pPlayer)
	self:resetEscortStatus(pPlayer)
	FsReflex1Goto:start(pPlayer)
end

function FsReflex1:restartQuest(pPlayer)
	deleteData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase1")

	self:resetTasks(pPlayer)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00)
	FsReflex1Goto:start(pPlayer)
end

function FsReflex1:resetTasks(pPlayer)
	if (FsReflex1Goto:hasTaskStarted(pPlayer)) then
		FsReflex1Goto:finish(pPlayer)
	end
	if (FsReflex1Escort:hasTaskStarted(pPlayer)) then
		FsReflex1Escort:finish(pPlayer)
	end
	if (FsReflex1Theater:hasTaskStarted(pPlayer)) then
		FsReflex1Theater:finish(pPlayer)
	end

	dropObserver(OBJECTDESTRUCTION, "FsReflex1Theater", "onPlayerKilled", pPlayer)
end

function FsReflex1:hasActiveRescue(pPlayer)
	return (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)) and not
		QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)
end

function FsReflex1:failQuest(pPlayer, failMsg)
	writeData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase1", 1)
	CreatureObject(pPlayer):sendSystemMessage(failMsg)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)

	dropObserver(OBJECTDESTRUCTION, "FsReflex1Theater", "onPlayerKilled", pPlayer)
end

function FsReflex1:resetEscortStatus(pPlayer)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)
end

function FsReflex1:doPhaseChangeFail(pPlayer)
	if (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00) or not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00)) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_01_quest_fail_phase_done");

	for i = 0, 7, 1 do
		local questName = "fs_reflex_rescue_quest_0" .. i
		local questID = getPlayerQuestID(questName)

		if QuestManager.hasCompletedQuest(pPlayer, questID) or QuestManager.hasActiveQuest(pPlayer, questID) then
			QuestManager.resetQuest(pPlayer, questID)
		end
	end

	FsReflex1:resetTasks(pPlayer)
	deleteData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase1")
end

function FsReflex1:completeVillagerEscort(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local count = self:getRescueCount(pPlayer) + 1

	self:setRescueCount(pPlayer, count)

	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)
	
	self:resetTasks(pPlayer)

	if (count == 5) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_01_quest_finished")
		VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_enhanced_reflexes_survival")
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00)
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)
		VillageJediManagerCommon.setCompletedQuestThisPhase(pPlayer)

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pSculpture = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_sculpture_3.iff", -1, true)

			if (pSculpture == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
			end
		end

	else
		local messageString = LuaStringIdChatParameter("@quest/force_sensitive/fs_reflex:msg_phase_01_quest_continue")
		messageString:setDI(5 - count)
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	end
end

function FsReflex1:getRescueCount(pPlayer)
	local count = readScreenPlayData(pPlayer, "VillageJediProgression", "FsReflex1Rescues")

	if (count == "") then
		count = 0
	end

	return tonumber(count)
end

function FsReflex1:setRescueCount(pPlayer, count)
	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsReflex1Rescues", count)
end

return FsReflex1
