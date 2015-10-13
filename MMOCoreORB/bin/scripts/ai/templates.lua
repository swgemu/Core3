includeAiFile("templates/example.lua")
includeAiFile("templates/stationary.lua")
includeAiFile("templates/stationarynoleash.lua")
includeAiFile("templates/follow.lua")
includeAiFile("templates/wait.lua")
includeAiFile("templates/idlewander.lua")
includeAiFile("templates/idlewait.lua")
includeAiFile("templates/idlepet.lua")
includeAiFile("templates/gettargetreactive.lua")
includeAiFile("templates/manualescort.lua")
includeAiFile("templates/selectattacksimple.lua")
includeAiFile("templates/combatmovesimple.lua")
includeAiFile("templates/gettargetpet.lua")
includeAiFile("templates/selectattackpet.lua")
includeAiFile("templates/combatmovepet.lua")

getTarget = {
	{CREATURE_PET, "gettargetpetc"},
	{DROID_PET, "gettargetpetd"},
	{FACTION_PET, "gettargetpetf"},
	{NONE, "gettargetreactive"},
}

selectAttack = {
	{CREATURE_PET, "selectattackpetc"},
	{DROID_PET, "selectattackpetd"},
	{FACTION_PET, "selectattackpetf"},
	{NONE, "selectattacksimple"},
}

combatMove = {
	{CREATURE_PET, "combatmovepetc"},
	{DROID_PET, "combatmovepetd"},
	{FACTION_PET, "combatmovepetf"},
	{NONE, "combatmovesimple"},
}

idle = {
	{CREATURE_PET, "idlepetc"},
	{DROID_PET, "idlepetd"},
	{FACTION_PET, "idlepetf"},
	{STATIC + WANDER, "idlewanderstatic"},
	{STATIC, "idlewait"},
	{PACK, "idlewanderpack"},
	{NONE, "idlewander"},
}
