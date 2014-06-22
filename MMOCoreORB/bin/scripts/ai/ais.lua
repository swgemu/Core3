--[[ Load Actions and Tasks ]]
includeAiFile("ai.lua")
includeAiFile("actions/actions.lua")
includeAiFile("tasks/tasks.lua")
includeAiFile("templates/templates.lua")

getTarget = {
	{NONE, "gettargetreactive"},
}

selectAttack = {
	{NONE, "selectattacksimple"},
}

combatMove = {
	{NONE, "combatmovesimple"},
}

idle = {
	{NONE, "idlewander"},
}