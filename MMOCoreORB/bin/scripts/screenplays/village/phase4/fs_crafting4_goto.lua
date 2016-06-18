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
-- @param pCreatureObject pointer to the creature object of the player.
function FsCrafting4Goto:onEnteredActiveArea(pCreatureObject)
	if (pCreatureObject == nil) then
		return 1
	end

	CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_device_target_updated")
	self:finish(pCreatureObject)
	FsCrafting4Theater:start(pCreatureObject)

	return 1
end

function FsCrafting4Goto:onSuccessfulSpawn(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	CreatureObject(pCreatureObject):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_device_target_located")
end

return FsCrafting4Goto
