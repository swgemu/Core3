LeashTask = Task:new{
	name= "leash"
}
function LeashTask:OnInitialize(luaAgent)
end
function LeashTask:OnTerminate(luaAgent,status)
end
LeashTask:register()