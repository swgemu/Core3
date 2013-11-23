-- Handling of persistent events.
local Task = require("quest.tasks.task")

PersistentEventPublicEventsAndObservers = {}
local PersistentEventPrivate = {}

local PersistentEvent = Task:new {
	-- Task properties
	taskName = "",
	taskStart = function(pCreatureObject) PersistentEventPrivate.taskStart(pCreatureObject) end,
	taskFinish = function(pCreatureObject) PersistentEventPrivate.taskFinish(pCreatureObject) end,
	-- PersistentEvent properties
	minimumTimeUntilEvent = 0,
	maximumTimeUntilEvent = 0
}

-- Expose private functions for testing.
function PersistentEvent.exposePrivateFunctions()
	if BUSTED_TEST then
		PersistentEvent.private = PersistentEventPrivate
		PersistentEvent.global = PersistentEventPublicEventsAndObservers
	end
end

-- Hide private functions.
function PersistentEvent.hidePrivateFunctions()
	PersistentEvent.private = {}
	PersistentEvent.global = {}
end

-- Handler for the event.
-- @param pCreatureObject pointer to the creature object of the player.
function PersistentEventPublicEventsAndObservers:handleEvent(pCreatureObject)
	PersistentEvent.finish(pCreatureObject)
end

-- Generate a random time for the persistent event.
-- @return a time to schedule the event.
function PersistentEventPrivate.getTime()
	local range = PersistentEvent.maximumTimeUntilEncounter - PersistentEvent.minimumTimeUntilEncounter
	if range > 0 then
		return PersistentEvent.minimumTimeUntilEncounter + math.random(range)
	else
		return PersistentEvent.minimumTimeUntilEncounter
	end
end

-- Start the event.
-- @param pCreatureObject pointer to the creature object of the player.
function PersistentEventPrivate.taskStart(pCreatureObject)
	createEvent(true, PersistentEventPrivate.getTime(), "PersistentEventPublicEventsAndObservers", "handleEvent", pCreatureObject)
end

-- Finish the event.
-- @param pCreatureObject pointer to the creature object of the player.
function PersistentEventPrivate.taskFinish(pCreatureObject)
	-- Should be overloaded by the module using this.
	error("taskFinish has not been overloaded for the persistent event '" .. PersistentEvent.taskName .. "'.")
end

return PersistentEvent
