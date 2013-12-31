HerdTask = Task:new{
	name= "herd"
}
function HerdTask:OnInitialize(luaAgent)
	addAction("call_for_help")
end
function HerdTask:OnTerminate(luaAgent,status)
	-- forget targets
end
HerdTask:register()