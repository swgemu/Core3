local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsPhase1 = ScreenPlay:new {}

function FsPhase1:onLoggedIn(pPlayer)
	local currentPhase = VillageJediManagerTownship:getCurrentPhase()

	if (currentPhase == 1 and VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		self:failActiveTasks(pPlayer)
	else
		self:doPhaseChangeFails(pPlayer)
	end
end

function FsPhase1:failActiveTasks(pPlayer)
	if (FsPatrol:hasTaskStarted(pPlayer)) then
		FsPatrol:failPatrol(pPlayer)
		FsPatrol:finish(pPlayer)
	end

	if (FsReflex1:hasActiveRescue(pPlayer)) then
		FsReflex1:resetTasks(pPlayer)
		FsReflex1:failQuest(pPlayer, "@quest/force_sensitive/fs_reflex:msg_phase_01_quest_failed")
	end
end

function FsPhase1:doPhaseChangeFails(pPlayer)
	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01) or QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02) or
		QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03)) then
		FsMedicPuzzle:doPhaseChange(pPlayer)
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00)) then
		FsCrafting1:doPhaseChangeFail(pPlayer)
	end

	FsPatrol:doPhaseChangeFail(pPlayer)
	FsReflex1:doPhaseChangeFail(pPlayer)
end

function FsPhase1:onLoggedOut(pPlayer)
	self:failActiveTasks(pPlayer)
end
