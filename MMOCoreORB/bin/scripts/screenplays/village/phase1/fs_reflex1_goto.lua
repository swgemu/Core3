local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
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
-- @param pPlayer pointer to the creature object of the player.
function FsReflex1Goto:onEnteredActiveArea(pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_reflex:msg_phase_01_find_theater_waypoint")
	self:finish(pPlayer)
	FsReflex1Theater:start(pPlayer)

	return 1
end

-- Event handler for the onSuccessfulSpawn.
-- The event will activate the quest.
-- @param pPlayer pointer to the creature object of the player.
function FsReflex1Goto:onSuccessfulSpawn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01)
end

return FsReflex1Goto
