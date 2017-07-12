local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsPhase4 = ScreenPlay:new {}

function FsPhase4:onLoggedIn(pPlayer)
	local currentPhase = VillageJediManagerTownship:getCurrentPhase()

	if (currentPhase ~= 4 or not VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		FsVillageDefense:doPhaseChangeFail(pPlayer)
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_06) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_06)) then
		FsCrafting4:sendTooLateSui(pPlayer)
	end
end
