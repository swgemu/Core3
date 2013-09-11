package.path = package.path .. ";scripts/ai/actions/?.lua;scripts/ai/tasks/?.lua"

Ai = { 

}

function Ai:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

function Ai:start()

end

function Ai:terminate()

end

function Ai:update()

end

--[[
	Remember a fact 
--]]
function Ai:remember(key,value)
end

--[[
	Forget a fact
--]]
function Ai:forget(key)
end

--[[
	Recall a fact from memory
--]]
function Ai:recall(key)
end


--[[ Behavior Object ]]
Behavior = Ai:new {}
--[[ Sequence Object ]]
Sequence = Ai:new {}

--[[ Selector Object ]]
Selector = Ai:new {}

--[[ NonDeterministic Object ]]
NonDeterministicSequence = Ai:new {}

--[[ Load Actions and Tasks ]]
includeFile("actions/actions.lua")
includeFile("tasks/tasks.lua")
