local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
require("utils.helpers")

FsCrafting1Goto1 = GoToLocation:new {
	-- Task properties
	taskName = "FsCrafting1Goto1",
	-- GoToLocation properties
	waypointDescription = "@quest/quest_journal/fs_quests_craft1:s_01",
	spawnPoint = { x = 5419, y = -4119 },
	spawnPlanet = "dathomir",
	spawnRadius = 8,
}

-- Event handler for the enter active area event.
-- The event will complete the task.
-- @param pPlayer pointer to the creature object of the player.
function FsCrafting1Goto1:onEnteredActiveArea(pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_01)

	self:finish(pPlayer)
	FsCrafting1Goto2:start(pPlayer)

	return 1
end

-- Event handler for the onSuccessfulSpawn.
-- The event will activate the quest.
-- @param pPlayer pointer to the creature object of the player.
function FsCrafting1Goto1:onSuccessfulSpawn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_01)
end

function FsCrafting1Goto1:onLoggedIn(pPlayer)
	if (not self:hasTaskStarted(pPlayer)) then
		return 1
	end

	if (VillageJediManagerTownship:getCurrentPhase() ~= 1) then
		FsCrafting1:doPhaseChangeFail(pPlayer)
	end

	return 1
end

return FsCrafting1Goto1
