package.path = package.path .. ";scripts/ai/?.lua"
local ObjectManager = require("managers.object.object_manager")
Ai = { }

function Ai:new (o)
	o = o or { }
	setmetatable(o, self)
	self.__index = self
	return o
end

function Ai:checkConditions(pAgent)
	return true
end

function Ai:start(pAgent)
	return 0
end

function Ai:terminate(pAgent)
	return 0
end

function Ai:doAction(pAgent)
	return BEHAVIOR_SUCCESS
end

--[[ Load Actions and Tasks ]]
includeAiFile("actions/actions.lua")
includeAiFile("tasks/tasks.lua")
includeAiFile("templates/templates.lua")
