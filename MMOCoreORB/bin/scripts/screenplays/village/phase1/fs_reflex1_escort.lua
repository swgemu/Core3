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

function FsReflex1Escort:onLoggedIn(pCreatureObject)
	if (not self:hasTaskStarted(pCreatureObject)) then
		return 1
	end

	if (VillageJediManagerTownship:getCurrentPhase() ~= 1) then
		FsReflex1:doPhaseChangeFail(pCreatureObject)
	else
		CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_01_quest_fail_logout");
		FsReflex1Theater:finish(pCreatureObject)
		self:finish(pCreatureObject)
		FsReflex1:failQuest(pCreatureObject)
	end
	return 1
end

return FsReflex1Escort
