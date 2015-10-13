includeAiFile("example.lua")
--TODO: write templates, put them in the base ai directory and get rid of current ai script directory structure
--includeAiFile("templates/example.lua")
--includeAiFile("templates/stationary.lua")
--includeAiFile("templates/stationarynoleash.lua")
--includeAiFile("templates/follow.lua")
--includeAiFile("templates/wait.lua")
--includeAiFile("templates/idlewander.lua")
--includeAiFile("templates/idlewait.lua")
--includeAiFile("templates/idlepet.lua")
--includeAiFile("templates/gettargetreactive.lua")
--includeAiFile("templates/manualescort.lua")
--includeAiFile("templates/selectattacksimple.lua")
--includeAiFile("templates/combatmovesimple.lua")
--includeAiFile("templates/gettargetpet.lua")
--includeAiFile("templates/selectattackpet.lua")
--includeAiFile("templates/combatmovepet.lua")

bitmaskLookup = {
	{NONE, "example"},
}

-- These are unused, leave them in for reference now until the other
-- table has been fully populated and all templates have been replicated.
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
