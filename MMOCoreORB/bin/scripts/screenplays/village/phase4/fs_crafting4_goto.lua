local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")
require("utils.helpers")

FsCrafting4Goto = GoToLocation:new {
	-- Task properties
	taskName = "FsCrafting4Goto",
	-- GoToLocation properties
	waypointDescription = "Downed Satellite",
	spawnPlanet = "", -- Setting to "" uses current player planet
	randomLocation = true,
	randomMinDistance = 900,
	randomMaxDistance = 1800,
	spawnRadius = 32,
}

-- Event handler for the enter active area event.
-- The event will complete the task.
-- @param pPlayer pointer to the creature object of the player.
function FsCrafting4Goto:onEnteredActiveArea(pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_device_target_updated")
	self:finish(pPlayer)
	FsCrafting4Theater:start(pPlayer)

	return 1
end

function FsCrafting4Goto:onSuccessfulSpawn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_device_target_located")
end

return FsCrafting4Goto
