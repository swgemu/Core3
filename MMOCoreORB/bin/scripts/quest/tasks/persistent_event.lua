-- Handling of persistent events.
local Task = require("quest.tasks.task")

PersistentEvent = Task:new {
	-- Task properties
	taskName = "",
	-- PersistentEvent properties
	minimumTimeUntilEvent = 0,
	maximumTimeUntilEvent = 0
}

-- Handler for the event.
-- @param pCreatureObject pointer to the creature object of the player.
function PersistentEvent:handleEvent(pCreatureObject)
	self:finish(pCreatureObject)
end

-- Generate a random time for the persistent event.
-- @return a time to schedule the event.
function PersistentEvent:getTime()
	local range = self.maximumTimeUntilEvent - self.minimumTimeUntilEvent
	if range > 0 then
		return self.minimumTimeUntilEvent + math.random(range)
	else
		return self.minimumTimeUntilEvent
	end
end

-- Start the event.
-- @param pCreatureObject pointer to the creature object of the player.
function PersistentEvent:taskStart(pCreatureObject)
	createEvent(true, self:getTime(), self.taskName, "handleEvent", pCreatureObject)
end

-- Finish the event.
-- @param pCreatureObject pointer to the creature object of the player.
function PersistentEvent:taskFinish(pCreatureObject)
	-- Should be overloaded by the module using this.
	--error("taskFinish has not been overloaded for the persistent event '" .. PersistentEvent.taskName .. "'.")
end

return PersistentEvent
