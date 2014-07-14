includeAiFile("templates/example.lua")
includeAiFile("templates/stationary.lua")
includeAiFile("templates/follow.lua")
includeAiFile("templates/wait.lua")
includeAiFile("templates/idlewander.lua")
includeAiFile("templates/idlewait.lua")
includeAiFile("templates/idlepet.lua")
includeAiFile("templates/gettargetreactive.lua")
includeAiFile("templates/selectattacksimple.lua")
includeAiFile("templates/combatmovesimple.lua")
includeAiFile("templates/gettargetpet.lua")
includeAiFile("templates/selectattackpet.lua")
includeAiFile("templates/combatmovepet.lua")

getTarget = {
	{PET, "gettargetpet"},
	{NONE, "gettargetreactive"},
}

selectAttack = {
	{PET, "selectattackpet"},
	{NONE, "selectattacksimple"},
}

combatMove = {
	{PET, "combatmovepet"},
	{NONE, "combatmovesimple"},
}

idle = {
	{PET, "idlepet"},
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

addAiBehavior("CompositePet")
addAiBehavior("WaitPet")
addAiBehavior("MovePet")
addAiBehavior("CombatMovePet")
addAiBehavior("GetTargetPet")
addAiBehavior("SelectAttackPet")
addAiBehavior("SelectWeaponPet")