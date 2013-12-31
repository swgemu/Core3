package.path = package.path .. ";scripts/ai/actions/?.lua;scripts/ai/tasks/?.lua;scripts/ai/templates/?.lua"

Ai = { 

}

function Ai:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

--[[
	start
	arguments: Pointer to Actor Object. Called from C++
	This method looks for an OnInitialize method passing in the wrapped pointer
--]]
function Ai:start(pActor)
	if self.OnInitialize then
		local agent = LuaAgent(pActor)
		self:OnInitialize(agent)
	end	
end

--[[
	terminate
	arguments: Pointer to Actor Object. 
	Status from the terminate 
	Called from C++
	This method looks for an OnTerminate method passing in the wrapped pointer
--]]
function Ai:terminate(pActor,status)
	if self.OnTerminate then
		local agent = LuaAgent(pActor)
		self:OnTerminate(agent,status)	
	end	
end

--[[
	upate
	arguments: Pointer to Actor Object. Called form C++
	This method looks for an OnUpdate method passing in the wrapped pointer
--]]
function Ai:update(pActor)
	if self.OnUpdate then
		local agent = LuaAgent(pActor)
		return self:OnUpdate(agent)
	else
		return BEHAVIOR_SUCCESS
	end
end

function Ai:remember(agent,key,value)
	writeAiMemory(string.format("%s:%s",agent:getObjectID(),key),value)
end

--[[
	Forget a fact
	arguments: agent, key
--]]
function Ai:forget(agent,key)
	deleteAiMemory(string.format("%s:%s",agent:getObjectID(),key))
end

--[[
	Recall a fact from memory
	arguments: agent,key
--]]
function Ai:recall(agent,key)
	readAiMemory(string.format("%s:%s",agent:getObjectID(),key))	
end


--[[ Action Object Base (C++ class LuaBehavior) ]]
Action = Ai:new {
	name = ""
}
function Action:register()
	registerAiAction(self.name)
end

--[[ Task Object Base (C++ class LuaSequence) ]]
Task = Ai:new {
	name = "",
	random = false
}
--[[ Task functions ]]--
function Task:register()
	registerAiAction(self.name)
end

function Task:addAction(a)
	addActionToTask(a,self.name)
end

function Task:addSubTask(a)
	addSubtask(a,self.name)
end

CreatureAiTemplate = {
	tasks = {},
	variables = {},
}

function CreatureAiTemplate:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

function CreatureAiTemplate:addCreatureAiTemplate(obj, file)
	if (obj == nil) then
		print("null template specified for " .. file)
	else
		addAiTemplate(file, obj)
	end
end

--[[ Load Templates, Actions and Tasks ]]
includeFile("actions/actions.lua")
includeFile("tasks/tasks.lua")
includeFile("templates/ai_templates.lua")

