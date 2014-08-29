-- Handling of persistent events.
-- The module ensures that only one event can be scheduled per creature object at the same time.
-- The event will be scheduled at a random time between the specified interval.
--
-- Usage:
-- Set the minimum and maximum time to the wanted values.
-- Set the handler name and function.
-- The handler should as last step always call finish on the persistent event.

local Task = require("quest.tasks.task")
local Logger = require("utils.logger")

PersistentEvent = Task:new {
	-- Task properties
	taskName = "",
	-- PersistentEvent properties
	minimumTimeUntilEvent = 0,
	maximumTimeUntilEvent = 0,
	handlerName = "PersistentEvent",
	handlerFunction = "handleEvent"
}

-- Default handler for the event. Generates error if triggered.
function PersistentEvent:handleEvent(pCreatureObject)
	error("No event handler for the persistent event " .. self.taskName .. " has been specified.")
end

-- Generate a random time for the persistent event.
-- @return a time to schedule the event.
function PersistentEvent:getTime()
	local range = self.maximumTimeUntilEvent - self.minimumTimeUntilEvent
	if range > 0 then
		return self.minimumTimeUntilEvent + getRandomNumber(0, range)
	else
		return self.minimumTimeUntilEvent
	end
end

-- Start the event.
-- @param pCreatureObject pointer to the creature object of the player.
function PersistentEvent:taskStart(pCreatureObject)
	local time = self:getTime()
	Logger:log("Creating event with scheduled execution time in " .. time .. " for task " .. self.taskName, LT_INFO)
	createEvent(true, time, self.handlerName, self.handlerFunction, pCreatureObject)
	return true
end

return PersistentEvent
