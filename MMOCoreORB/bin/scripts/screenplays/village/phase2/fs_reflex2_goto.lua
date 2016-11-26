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
-- @param pPlayer pointer to the creature object of the player.
function FsReflex2Goto:onEnteredActiveArea(pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_02_find_theater_waypoint")
	self:finish(pPlayer)
	FsReflex2Theater:start(pPlayer)

	return 1
end

-- Event handler for the onSuccessfulSpawn.
-- The event will activate the quest.
-- @param pPlayer pointer to the creature object of the player.
function FsReflex2Goto:onSuccessfulSpawn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_01)
end

return FsReflex2Goto
