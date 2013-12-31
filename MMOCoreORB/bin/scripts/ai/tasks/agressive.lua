AgressiveTask = Task:new{
	name= "agressive"
}
function AgressiveTask:OnInitialize(luaAgent)
	addAction("find_target")
	addAction("attack")	
	addAction("chase")
end
function AgressiveTask:OnTerminate(luaAgent,status)
	-- forget targets
end
AgressiveTask:register()