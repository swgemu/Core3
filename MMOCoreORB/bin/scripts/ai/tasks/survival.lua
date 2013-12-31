SurvivalTask = Task:new{
	name= "survival"
}
function SurvivalTask:OnInitialize(luaAgent)
	addAction("lowhealth")
	addAction("flee")	
end
SurvivalTask:register()