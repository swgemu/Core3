local GoToLocation = require("quest.tasks.go_to_location")
local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
local FsReflex1Theater = require("managers.jedi.village.phase1.fs_reflex1_theater")
require("utils.helpers")

FsReflex1Goto = GoToLocation:new {
	-- Task properties
	taskName = "FsReflex1Goto",
	-- GoToLocation properties
	waypointDescription = "@quest/quest_journal/fs_quests_reflex1:s_01",
	randomLocation = true,
	randomMinDistance = 900,
	randomMaxDistance = 1100,
	spawnPlanet = "dathomir",
	spawnRadius = 8,
}

-- Event handler for the enter active area event.
-- The event will complete the task.
-- @param pCreatureObject pointer to the creature object of the player.
function FsReflex1Goto:onEnteredActiveArea(pCreatureObject)
	if (pCreatureObject == nil) then
		return 1
	end

	CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_01_find_theater_waypoint")
	self:finish(pCreatureObject)
	FsReflex1Theater:start(pCreatureObject)

	return 1
end

-- Event handler for the onSuccessfulSpawn.
-- The event will activate the quest.
-- @param pCreatureObject pointer to the creature object of the player.
function FsReflex1Goto:onSuccessfulSpawn(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01)
end

function FsReflex1Goto:onLoggedIn(pCreatureObject)
	if (not self:hasTaskStarted(pCreatureObject)) then
		return 1
	end

	CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_01_quest_fail_logout");
	self:finish(pCreatureObject)
	FsReflex1:failQuest(pCreatureObject)

	return 1
end

return FsReflex1Goto
