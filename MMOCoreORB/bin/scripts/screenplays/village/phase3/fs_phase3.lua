local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsPhase3 = ScreenPlay:new {}

function FsPhase3:onLoggedIn(pPlayer)
	local currentPhase = VillageJediManagerTownship:getCurrentPhase()

	if (currentPhase == 3 and VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		self:failActiveTasks(pPlayer, true)
	else
		self:doPhaseChangeFails(pPlayer)
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN) and not VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_01)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_02)
	end
end

function FsPhase3:failActiveTasks(pPlayer, loggingIn)
	if (FsSad2:hasActiveNonReturnTask(pPlayer)) then
		FsSad2:despawnCamp(pPlayer)

		if (not FsSad2:hasExceededLimit(pPlayer) and loggingIn) then
			FsSad2:recreateCampIfDespawned(pPlayer)
		end
	end
end

function FsPhase3:doPhaseChangeFails(pPlayer)
	FsSad2:doPhaseChangeFail(pPlayer)
end

function FsPhase3:onLoggedOut(pPlayer)
	self:failActiveTasks(pPlayer, false)
end
