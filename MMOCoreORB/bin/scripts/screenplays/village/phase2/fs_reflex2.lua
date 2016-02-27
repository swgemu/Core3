local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsReflex2 = ScreenPlay:new {}

function FsReflex2:startQuest(pCreature)
	self:setFetchCount(pCreature, 0)
	QuestManager.activateQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00)
	FsReflex2Goto:start(pCreature)
end

function FsReflex2:startNextFetch(pCreature)
	self:resetFetchStatus(pCreature)
	FsReflex2Theater:finish(pCreature)
	FsReflex2Goto:start(pCreature)
end

function FsReflex2:restartQuest(pCreature)
	deleteData(SceneObject(pCreature):getObjectID() .. ":failedWhipPhase2")
	QuestManager.activateQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00)
	FsReflex2Theater:finish(pCreature)
	FsReflex2Goto:start(pCreature)
end

function FsReflex2:failQuest(pCreature)
	writeData(SceneObject(pCreature):getObjectID() .. ":failedWhipPhase2", 1)
	FsReflex2Theater:finish(pCreature)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_01)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_02)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03)
end

function FsReflex2:resetFetchStatus(pCreature)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_02)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03)
end

function FsReflex2:completeSupplyFetch(pCreature)
	if (pCreature == nil) then
		return
	end

	local count = self:getFetchCount(pCreature) + 1

	self:setFetchCount(pCreature, count)

	QuestManager.completeQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03)

	if (count == 5) then
		CreatureObject(pCreature):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_finished")
		VillageJediManagerCommon.unlockBranch(pCreature, "force_sensitive_enhanced_reflexes_vehicle_control")
		QuestManager.completeQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00)
		QuestManager.completeQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)
		VillageJediManagerCommon.setCompletedQuestThisPhase(pCreature)

		local pInventory = SceneObject(pCreature):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pSculpture = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_buff_item.iff", -1, true)

			if (pSculpture == nil) then
				CreatureObject(pCreature):sendSystemMessage("Error: Unable to generate item.")
			end
		end

	else
		local messageString = LuaStringIdChatParameter("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_continue")
		messageString:setDI(5 - count)
		CreatureObject(pCreature):sendSystemMessage(messageString:_getObject())
	end
end

function FsReflex2:getFetchCount(pCreature)
	local count = readScreenPlayData(pCreature, "VillageJediProgression", "FsReflex2Fetches")

	if (count == "") then
		count = 0
	end

	return tonumber(count)
end

function FsReflex2:setFetchCount(pCreature, count)
	writeScreenPlayData(pCreature, "VillageJediProgression", "FsReflex2Fetches", count)
end

function FsReflex2:doPhaseChangeFail(pCreature)
	if (QuestManager.hasCompletedQuest(pCreature, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)) then
		return
	end

	CreatureObject(pCreature):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_fail_phase_done");

	for i = 0, 6, 1 do
		local questName = "fs_reflex_fetch_quest_0" .. i
		local questID = getPlayerQuestID(questName)

		QuestManager.resetQuest(pCreature, questID)
	end

	FsReflex2Goto:finish(pCreature)
	FsReflex2GoBack:finish(pCreature)
	FsReflex2Theater:finish(pCreature)
	deleteData(SceneObject(pCreature):getObjectID() .. ":failedWhipPhase1")
end

return FsReflex2
