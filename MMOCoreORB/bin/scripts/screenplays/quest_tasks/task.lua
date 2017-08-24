-- Base module for all tasks.
local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

Task = ScreenPlay:new {
	taskName = "",
	taskStart = nil,
	taskFinish = nil,
	onLoggedIn = nil,
	onLoggedOut = nil,
}

-- Check if the task has been started for the player.
-- @param pPlayer pointer to the creature object of the player.
function Task:hasTaskStarted(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return readData(SceneObject(pPlayer):getObjectID() .. ":taskStarted:" .. self.taskName) == 1
end

-- Set the task started screen play state for the player.
-- @param pPlayer pointer to the creature object of the player.
function Task:setTaskStarted(pPlayer)
	writeData(SceneObject(pPlayer):getObjectID() .. ":taskStarted:" .. self.taskName, 1)
end

-- Set the task finished screen play state for the player.
-- @param pPlayer pointer to the creature object of the player.
function Task:setTaskFinished(pPlayer)
	deleteData(SceneObject(pPlayer):getObjectID() .. ":taskStarted:" .. self.taskName)
end

-- Call the supplied function with the argument if the function is not nil.
-- An error will be issued if the function is nil.
-- @param theFunction the function to call.
-- @param argument the argument to use for the function.
function Task:callFunctionIfNotNil(theFunction, returnIfNil, ...)
	if theFunction ~= nil then
		return theFunction(self, table.unpack({...}))
	else
		Logger:log("The function to call is nil in " .. Task.taskName .. ".", LT_INFO)
		return returnIfNil
	end
end

-- Start the task.
-- @param pPlayer pointer to the creature object of the player who should get the task started.
function Task:start(pPlayer, ...)
	if (pPlayer == nil) then
		return false
	end

	if not self:hasTaskStarted(pPlayer) then
		Logger:log("Starting task " .. self.taskName, LT_INFO)
		if self:callFunctionIfNotNil(self.taskStart, true, pPlayer, table.unpack({...})) then
			Logger:log(self.taskName .. " started.", LT_INFO)
			self:setTaskStarted(pPlayer)

			if self.onLoggedIn ~= nil then
				createObserver(LOGGEDIN, self.taskName, "onLoggedIn", pPlayer, 1)
			end
			if self.onLoggedOut ~= nil then
				createObserver(LOGGEDOUT, self.taskName, "onLoggedOut", pPlayer, 1)
			end
			
			return true
		end
	else
		Logger:log("Task " .. self.taskName .. " is already started.", LT_INFO)
	end
	
	return false
end

-- Finish the task.
-- @param pPlayer pointer to the creature object of the player who should get the task finished.
function Task:finish(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if self:hasTaskStarted(pPlayer) then
		Logger:log("Finishing task " .. self.taskName, LT_INFO)
		if self:callFunctionIfNotNil(self.taskFinish, true, pPlayer) then
			Logger:log(self.taskName .. " finished.", LT_INFO)
			self:setTaskFinished(pPlayer)

			dropObserver(LOGGEDIN, self.taskName, "onLoggedIn", pPlayer)
			dropObserver(LOGGEDIN, self.taskName, "onLoggedOut", pPlayer)
		end
	else
		Logger:log("Task " .. self.taskName .. " is not started.", LT_INFO)
	end
end

return Task
