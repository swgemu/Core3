includeAiFile("templates/sequencetest0.lua")
includeAiFile("templates/selectortest0.lua")
includeAiFile("templates/selectortest1.lua")
includeAiFile("templates/parallelsequencetest0.lua")
includeAiFile("templates/parallelselectortest0.lua")
includeAiFile("templates/nondeterministicsequencetest0.lua")
includeAiFile("templates/nondeterministicselectortest0.lua")
includeAiFile("templates/movetest0.lua")
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
	{NONE, "idlewander"},
	{STATIC, "idlewait"},
}

addAiBehavior("Composite")
addAiBehavior("None")
addAiBehavior("Wait")
addAiBehavior("Wait10")
addAiBehavior("Move")
addAiBehavior("Walk")
addAiBehavior("CombatMove")
addAiBehavior("GeneratePatrol")
addAiBehavior("GetTarget")
addAiBehavior("SelectAttack")
addAiBehavior("SelectWeapon")

addAiBehavior("NonDeterministicSelector")
addAiBehavior("NonDeterministicSequence")
addAiBehavior("ParallelSelector")
addAiBehavior("ParallelSequence")
addAiBehavior("Selector")
addAiBehavior("Sequence")
addAiBehavior("Failure")
addAiBehavior("Succeed")