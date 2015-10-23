local ObjectManager = require("managers.object.object_manager")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")
local QuestManager = require("managers.quest.quest_manager")
local FsReflex1Goto = require("managers.jedi.village.phase1.fs_reflex1_goto")

FsReflex1 = Object:new {}

function FsReflex1:startQuest(pCreature)
	self:setRescueCount(pCreature, 0)
	QuestManager.activateQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00)
	FsReflex1Goto:start(pCreature)
end

function FsReflex1:startNextRescue(pCreature)
	self:resetEscortStatus(pCreature)
	FsReflex1Goto:start(pCreature)
end

function FsReflex1:restartQuest(pCreature)
	deleteData(SceneObject(pCreature):getObjectID() .. ":failedWhipPhase1")
	QuestManager.activateQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00)
	FsReflex1Goto:start(pCreature)
end

function FsReflex1:failQuest(pCreature)
	writeData(SceneObject(pCreature):getObjectID() .. ":failedWhipPhase1", 1)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)
end

function FsReflex1:resetEscortStatus(pCreature)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)
	QuestManager.resetQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)
end

function FsReflex1:completeVillagerEscort(pCreature)
	if (pCreature == nil) then
		return
	end

	local count = self:getRescueCount(pCreature) + 1

	self:setRescueCount(pCreature, count)
	self:resetEscortStatus(pCreature)

	QuestManager.completeQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03)
	QuestManager.completeQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)
	QuestManager.activateQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)

	if (count == 5) then
		CreatureObject(pCreature):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_01_quest_finished")
		VillageJediManagerCommon.unlockBranch(pCreature, "force_sensitive_enhanced_reflexes_survival")
		QuestManager.completeQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00)
		QuestManager.completeQuest(pCreature, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)

		local pInventory = SceneObject(pCreature):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pSculpture = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_sculpture_3.iff", -1, true)

			if (pSculpture == nil) then
				CreatureObject(pCreature):sendSystemMessage("Error: Unable to generate item.")
			end
		end

	else
		local messageString = LuaStringIdChatParameter("@quest/force_sensitive/fs_reflex:msg_phase_01_quest_continue")
		messageString:setDI(5 - count)
		CreatureObject(pCreature):sendSystemMessage(messageString:_getObject())
	end
end

function FsReflex1:getRescueCount(pCreature)
	local count = readScreenPlayData(pCreature, "VillageJediProgression", "FsReflex1Rescues")

	if (count == "") then
		count = 0
	end

	return tonumber(count)
end

function FsReflex1:setRescueCount(pCreature, count)
	writeScreenPlayData(pCreature, "VillageJediProgression", "FsReflex1Rescues", count)
end

return FsReflex1
