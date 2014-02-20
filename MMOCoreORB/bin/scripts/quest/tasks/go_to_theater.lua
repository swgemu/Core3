-- This module handles the go_to_theater script for the quests.
-- It spawns a theater and a set of mobiles in the world and keeps track of them.

local Task = require("quest.tasks.task")
local ObjectManager = require("managers.object.object_manager")

GoToTheater = Task:new {
	-- Task properties
	taskName = "",
	-- GoToTheater properties
	minimumDistance = 0,
	maximumDistance = 0
}

-- Start the GoToTheater.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToTheater:taskStart(pCreatureObject)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		local spawnPoint = getSpawnPoint(pCreatureObject, creatureObject:getWorldPositionX(), creatureObject:getWorldPositionY(), self.minimumDistance, self.maximumDistance)
	end)
end

return GoToTheater
