local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsPhase2 = ScreenPlay:new {}

function FsPhase2:onLoggedIn(pPlayer)
	local currentPhase = VillageJediManagerTownship:getCurrentPhase()

	if (currentPhase == 2 and VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		self:failActiveTasks(pPlayer, true)
	else
		self:doPhaseChangeFails(pPlayer)
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN) and not VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_01)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_02)
	end

end

function FsPhase2:failActiveTasks(pPlayer, loggingIn)
	if (FsReflex2:hasActiveFetch(pPlayer)) then
		FsReflex2:resetTasks(pPlayer)
		FsReflex2:failQuest(pPlayer)
	end

	if (FsSad:hasActiveNonReturnTask(pPlayer)) then
		FsSad:despawnCamp(pPlayer)

		if (not FsSad:hasExceededLimit(pPlayer) and loggingIn) then
			FsSad:recreateCampIfDespawned(pPlayer)
		end
	end
end

function FsPhase2:doPhaseChangeFails(pPlayer)
	FsReflex2:doPhaseChangeFail(pPlayer)
	FsSad:doPhaseChangeFail(pPlayer)
end

function FsPhase2:onLoggedOut(pPlayer)
	self:failActiveTasks(pPlayer, false)
end
