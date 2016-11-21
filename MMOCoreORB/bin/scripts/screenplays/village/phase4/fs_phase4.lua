local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsPhase4 = ScreenPlay:new {}

function FsPhase4:onLoggedIn(pPlayer)
	local currentPhase = VillageJediManagerTownship:getCurrentPhase()

	if (currentPhase ~= 4 or not VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		FsVillageDefense:doPhaseChangeFail(pPlayer)
	end
end
