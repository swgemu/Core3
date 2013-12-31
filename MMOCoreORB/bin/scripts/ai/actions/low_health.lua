LowHealthAction = Action:new{
	name= "low_health"
}
function LowHealthAction:OnInitialize(luaAgent)
end
function LowHealthAction:OnTerminate(luaAgent,status)
end
function LowHealthAction:OnUpdate(luaAgent)
end
LowHealthAction:register()