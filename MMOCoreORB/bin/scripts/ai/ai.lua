package.path = package.path .. ";scripts/ai/actions/?.lua;scripts/ai/tasks/?.lua;scripts/ai/templates/?.lua;scripts/ai/?.lua"
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

function Ai:interrupt(pAgent, pObject, msg)
	if msg == STARTCOMBAT then
		self:terminate(pAgent)
		if (pAgent ~= nil) then
			local agent = LuaAiAgent(pAgent)
			agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
			agent:resetBehaviorList()
			agent:executeBehavior()
		end
	end
end
