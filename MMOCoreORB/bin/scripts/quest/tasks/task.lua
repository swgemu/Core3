-- Base module for all tasks.
local ObjectManager = require("managers.object.object_manager")

local Task = Object:new {
	taskName = "",
	taskStart = nil,
	taskFinish = nil
}
TaskPublicEventsAndObservers = {}
local TaskPrivate = {}

-- Expose private functions for testing.
function Task.exposePrivateFunctions()
	if BUSTED_TEST then
		Task.private = TaskPrivate
		Task.global = TaskPublicEventsAndObservers
	end
end

-- Hide private functions.
function Task.hidePrivateFunctions()
	Task.private = {}
	Task.global = {}
end

local TASK_STARTED = 0xABCD

-- Check if the task has been started for the player.
-- @param pCreatureObject pointer to the creature object of the player.
function TaskPrivate.hasTaskStarted(pCreatureObject)
	return ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return creatureObject:getScreenPlayState(Task.taskName) == TASK_STARTED
	end) == true
end

-- Set the task started screen play state for the player.
-- @param pCreatureObject pointer to the creature object of the player.
function TaskPrivate.setTaskStarted(pCreatureObject)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:setScreenPlayState(TASK_STARTED, Task.taskName)
	end)
end

-- Set the task finished screen play state for the player.
-- @param pCreatureObject pointer to the creature object of the player.
function TaskPrivate.setTaskFinished(pCreatureObject)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:removeScreenPlayState(TASK_STARTED, Task.taskName)
	end)
end

-- Call the supplied function with the argument if the function is not nil.
-- An error will be issued if the function is nil.
-- @param theFunction the function to call.
-- @param argument the argument to use for the function.
function TaskPrivate.callFunctionIfNotNil(theFunction, argument)
	if theFunction ~= nil then
		theFunction(argument)
	else
		error("The function to call is nil in " .. Task.taskName .. ".", 2)
	end
end

-- Start the task.
-- @param pCreatureObject pointer to the creature object of the player who should get the task started.
function Task.start(pCreatureObject)
	if not TaskPrivate.hasTaskStarted(pCreatureObject) then
		TaskPrivate.setTaskStarted(pCreatureObject)
		TaskPrivate.callFunctionIfNotNil(Task.taskStart, pCreatureObject)
	end
end

-- Finish the task.
-- @param pCreatureObject pointer to the creature object of the player who should get the task finished.
function Task.finish(pCreatureObject)
	if TaskPrivate.hasTaskStarted(pCreatureObject) then
		TaskPrivate.callFunctionIfNotNil(Task.taskFinish, pCreatureObject)
		TaskPrivate.setTaskFinished(pCreatureObject)
	end
end

return Task
