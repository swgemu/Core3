local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
require("utils.helpers")

FsReflex2Goto = GoToLocation:new {
	-- Task properties
	taskName = "FsReflex2Goto",
	-- GoToLocation properties
	waypointDescription = "@quest/quest_journal/fs_quests_reflex2:s_01",
	spawnPoint = { x = 0, y = 0 },
	randomLocation = true,
	randomMinDistance = 900,
	randomMaxDistance = 1100,
	spawnPlanet = "endor",
	spawnRadius = 8,
}

-- Event handler for the enter active area event.
-- The event will complete the task.
-- @param pCreatureObject pointer to the creature object of the player.
function FsReflex2Goto:onEnteredActiveArea(pCreatureObject)
	if (pCreatureObject == nil) then
		return 1
	end

	CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_find_theater_waypoint")
	self:finish(pCreatureObject)
	FsReflex2Theater:start(pCreatureObject)

	return 1
end

-- Event handler for the onSuccessfulSpawn.
-- The event will activate the quest.
-- @param pCreatureObject pointer to the creature object of the player.
function FsReflex2Goto:onSuccessfulSpawn(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_REFLEX_FETCH_QUEST_01)
end

return FsReflex2Goto
