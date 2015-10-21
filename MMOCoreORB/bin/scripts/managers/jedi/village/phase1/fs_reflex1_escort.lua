local Escort = require("quest.tasks.escort")
local ObjectManager = require("managers.object.object_manager")
local FsReflex1 = require("managers.jedi.village.phase1.fs_reflex1")
local QuestManager = require("managers.quest.quest_manager")
local FsReflex1Theater = require("managers.jedi.village.phase1.fs_reflex1_theater")
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

function FsReflex1Escort:onEnteredActiveArea(pCreatureObject)
	self:completeReflexEscort(pCreatureObject)
end

function FsReflex1Escort:completeReflexEscort(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end
	FsReflex1Theater:finish(pCreatureObject)
	FsReflex1:completeVillagerEscort(pCreatureObject)
end

return FsReflex1Escort
