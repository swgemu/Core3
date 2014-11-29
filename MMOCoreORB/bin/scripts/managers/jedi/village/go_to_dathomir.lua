local GoToLocation = require("quest.tasks.go_to_location")
local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
require("utils.helpers")

GoToDathomir = GoToLocation:new {
	-- Task properties
	taskName = "GoToDathomir",
	-- GoToLocation properties
	waypointDescription = "@quest/force_sensitive/intro:goto_dath_sum",
	spawnPoint = { x = 5306, y = -4145 },
	spawnPlanet = "dathomir",
	spawnRadius = 128,
    onFailedSpawn = nil,
    onSuccessfulSpawn = nil,
    onEnteredActiveArea = nil
}

-- Event handler for the enter active area event.
-- The event will complete the task.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToDathomir:onEnteredActiveArea(pCreatureObject)
    QuestManager.completeQuest(pCreatureObject, QuestManager.quests.FS_VILLAGE_ELDER)
    self:taskFinish(pCreatureObject)
end

-- Event handler for the onSuccessfulSpawn.
-- The event will activate the quest.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToDathomir:onSuccessfulSpawn(pCreatureObject)
    QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_VILLAGE_ELDER)
end

return GoToDathomir
