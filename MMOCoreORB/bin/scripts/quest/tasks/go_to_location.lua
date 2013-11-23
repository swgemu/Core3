-- This script is for going to a specified location on a planet.
local Task = require("quest.tasks.task")
local ObjectManager = require("managers.object.object_manager")

GoToLocationPublicEventsAndObservers = {}
local GoToLocationPrivate = {}

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

-- Expose private functions for testing.
function GoToLocation.exposePrivateFunctions()
	if BUSTED_TEST then
		GoToLocation.private = GoToLocationPrivate
		GoToLocation.global = GoToLocationPublicEventsAndObservers
	end
end

-- Hide private functions.
function GoToLocation.hidePrivateFunctions()
	GoToLocation.private = {}
	GoToLocation.global = {}
end

-- Handler for the event.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToLocationPublicEventsAndObservers:handleEvent(pActiveArea, pCreatureObject)

	local movingObject = ObjectManager.withSceneObject(pCreatureObject)

	if (movingObject:isCreatureObject()) then
		local player = ObjectManager.withCreatureObject(pCreatureObject)
		local objectID = player:getObjectID()
		
		if (task.hasTaskStarted(pMovingObject) then
			GoToLocation.finish(pCreatureObject)
		end
	end
	GoToLocation.finish(pCreatureObject)
end

-- Generate an active area for observation.
-- @return an active area.
function GoToLocationPrivate.getActiveArea()

	if (not isZoneEnabled(GoToLocation.targetPlanet)) then	
		return
	end

	--Height doesn't matter for active areas.
	local pActiveArea = spawnSceneObject(GoToLocation.targetPlanet, "object/active_area.iff",  targetX, 0, targetY, 0, 0, 0, 0, 0)

	if (pActiveArea ~= nil then)
		return pActiveArea
	end

end

-- Start the event.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToLocationPrivate.taskStart(pCreatureObject)

	local pActiveArea = GoToLocationPrivate.getActiveArea()
	createObserver(ENTEREDAREA, "GoToLocationPublicEventsAndObservers", "handleEvent", pActiveArea)
end

-- Finish the event.
-- @param pCreatureObject pointer to the creature object of the player.
function GoToLocationPrivate.taskFinish(pCreatureObject)
	-- Should be overloaded by the module using this.
	error("taskFinish has not been overloaded for the persistent event '" .. PersistentEvent.taskName .. "'.")
end

return GoToLocation
