PassiveTask = Task:new{
	name= "passive"
}
function PassiveTask:OnInitialize(luaAgent)
	addAction("flee")
	addSubTask("leash")
end
function PassiveTask:OnTerminate(luaAgent,status)
	-- forget targets
end
PassiveTask:register()