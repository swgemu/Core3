includeAiFile("templates/example.lua")
includeAiFile("templates/stationary.lua")
includeAiFile("templates/follow.lua")
includeAiFile("templates/idlewander.lua")
includeAiFile("templates/idlewait.lua")
includeAiFile("templates/gettargetreactive.lua")
includeAiFile("templates/selectattacksimple.lua")
includeAiFile("templates/combatmovesimple.lua")

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
	{STATIC, "idlewait"},
	{PACK, "idlewanderpack"},
	{NONE, "idlewander"},
}

addAiBehavior("Composite")
addAiBehavior("Wait")
addAiBehavior("Wait10")
addAiBehavior("Move")
addAiBehavior("Walk")
addAiBehavior("CombatMove")
addAiBehavior("GeneratePatrol")
addAiBehavior("GetTarget")
addAiBehavior("SelectAttack")
addAiBehavior("SelectWeapon")

addAiBehavior("CompositeDefault")
addAiBehavior("WaitDefault")
addAiBehavior("Wait10Default")
addAiBehavior("MoveDefault")
addAiBehavior("WalkDefault")
addAiBehavior("GeneratePatrolDefault")

addAiBehavior("CompositePack")
addAiBehavior("WaitPack")
addAiBehavior("Wait10Pack")
addAiBehavior("MovePack")
addAiBehavior("WalkPack")
addAiBehavior("GeneratePatrolPack")