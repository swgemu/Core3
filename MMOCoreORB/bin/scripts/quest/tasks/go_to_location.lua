-- This script is for going to a specified location on a planet.
local Task = require("quest.tasks.task")
local ObjectManager = require("managers.object.object_manager")

GoToLocation = Task:new {
	-- Task properties
	taskName = "",
	taskStart = function(pCreatureObject) GoToLocationPrivate.taskStart(pCreatureObject) end,
	taskFinish = function(pCreatureObject) GoToLocationPrivate.taskFinish(pCreatureObject) end,
	-- GoToLocation properties
	targetPlanet = nil,
	targetX = 0,
	targetY = 0
}

-- Handler for the event.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToLocation:handleEvent(pActiveArea, pCreatureObject)

	local movingObject = ObjectManager.withSceneObject(pCreatureObject)

	if (movingObject:isCreatureObject()) then
		local player = ObjectManager.withCreatureObject(pCreatureObject)
		local objectID = player:getObjectID()
		
		if (task.hasTaskStarted(pMovingObject)) then
			self:finish(pCreatureObject)
		end
	end
end

-- Generate an active area for observation.
-- @return an active area.
function GoToLocation:getActiveArea()

	if (not isZoneEnabled(self:targetPlanet)) then	
		return
	end

	--Height doesn't matter for active areas.
	local pActiveArea = spawnSceneObject(self:targetPlanet, "object/active_area.iff", self:targetX, 0, self:targetY, 0, 0, 0, 0, 0)

	if (pActiveArea ~= nil) then
		return pActiveArea
	end

end

-- Start the event.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToLocation:taskStart(pCreatureObject)

	local pActiveArea = self:getActiveArea()
	createObserver(ENTEREDAREA, self.taskName, "handleEvent", pActiveArea)
end

-- Finish the event.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToLocation:taskFinish(pCreatureObject)
	-- Should be overloaded by the module using this.
	-- error("taskFinish has not been overloaded for the go to location quest '" .. self:taskName .. "'.")
end

return GoToLocation
