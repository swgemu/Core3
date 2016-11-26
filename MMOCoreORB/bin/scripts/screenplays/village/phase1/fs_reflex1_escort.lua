local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local Logger = require("utils.logger")

FsReflex1Escort = Escort:new {
	-- Task properties
	taskName = "FsReflex1Escort",
	-- GoToLocation properties
	waypointDescription = "@quest/quest_journal/fs_quests_reflex1:s_04",
	returnPoint = { x = 5283, y = -4226 },
	returnPlanet = "dathomir",

	areaRadius = 16,
}

function FsReflex1Escort:onEnteredActiveArea(pPlayer)
	self:completeReflexEscort(pPlayer)
end

function FsReflex1Escort:completeReflexEscort(pPlayer)
	if (pPlayer == nil) then
		return
	end
	FsReflex1Theater:finish(pPlayer)
	FsReflex1:completeVillagerEscort(pPlayer)
end

return FsReflex1Escort
