local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
require("utils.helpers")

FsReflex2GoBack = GoToLocation:new {
	-- Task properties
	taskName = "FsReflex2GoBack",
	-- GoToLocation properties
	waypointDescription = "@quest/quest_journal/fs_quests_reflex2:s_03",
	spawnPoint = { x = 5283, y = -4226 },
	spawnPlanet = "dathomir",
	spawnRadius = 8,
}

-- Event handler for the enter active area event.
-- The event will complete the task.
-- @param pCreatureObject pointer to the creature object of the player.
function FsReflex2GoBack:onEnteredActiveArea(pCreatureObject)
	if (pCreatureObject == nil) then
		return 1
	end

	self:finish(pCreatureObject)

	return 1
end

-- Event handler for the onSuccessfulSpawn.
-- The event will activate the quest.
-- @param pCreatureObject pointer to the creature object of the player.
function FsReflex2GoBack:onSuccessfulSpawn(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03)
end

function FsReflex2GoBack:onLoggedIn(pCreatureObject)
	if (not self:hasTaskStarted(pCreatureObject)) then
		return 1
	end

	if (VillageJediManagerTownship:getCurrentPhase() ~= 2) then
		FsReflex2:doPhaseChangeFail(pCreatureObject)
	else
		if (not QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)) then
			CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_quest_fail_phase_done"); -- No logged out error message in string files, using phase change error instead
			FsReflex2:failQuest(pCreatureObject)
		end
		self:finish(pCreatureObject)
	end

	return 1
end

return FsReflex2GoBack
