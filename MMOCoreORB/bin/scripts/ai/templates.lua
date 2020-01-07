includeFile("default.lua")
includeFile("escort.lua")
includeFile("pet.lua")
includeFile("static.lua")
includeFile("test.lua")
includeFile("test.lua")
includeFile("deathWatch.lua")
includeFile("enclaveSentinel.lua")
includeFile("villageRaider.lua")
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

customMap = {
	{ "enclaveSentinel", {
		{AWARE, "awareEnclavesentinel"}
	}},

	{ "deathWatch", {
		{AWARE, "awareDeathwatch"}
	}},

	{ "villageRaider", {
		{AWARE, "awareVillageraider"}
	}},
}

bitmaskLookup = {
	{NONE, {
		{NONE, "rootDefault"},
		{AWARE, "awareDefault"},
		{IDLE, "wanderDefault"},
		{ATTACK, "attackDefault"},
		{EQUIP, "equipDefault"},
		{TARGET, "targetDefault"},
		{MOVE, "moveDefault"},
		{LOOKAT, "lookDefault"},
		{AGGRO, "aggroDefault"},
		{SCARE, "scareDefault"}
	}},

	{NPC, {
		{LOOKAT, "failTest"},
		{SCARE, "failTest"}
	}},

	{PET, {
		{IDLE, "idlePet"},
		{TARGET, "targetPet"},
		{MOVE, "movePet"}
	}},

	{FACTION_PET, {
		{IDLE, "idlePet"},
		{TARGET, "targetPet"},
		{MOVE, "movePet"}
	}},

	{DROID_PET, {
		{IDLE, "idlePet"},
		{TARGET, "targetPet"},
		{MOVE, "movePet"}
	}},

	{ESCORT, {
		{IDLE, "walkEscort"},
		{TARGET, "targetDefault"}
	}},

	{FOLLOW, {
		{IDLE, "runEscort"},
		{TARGET, "targetDefault"}
	}},

	{STATIC, {
		{IDLE, "wanderStatic"}
	}},

	{STATIONARY, {
		{IDLE, "idleStatic"}
	}},

	{NOAIAGGRO, {
		{NONE, "rootStatic"}
	}},

	{TEST, {
		{AWARE, "failTest"},
		{IDLE, "succeedTest"},
		{ATTACK, "failTest"},
		{EQUIP, "failTest"},
		{TARGET, "failTest"},
		{MOVE, "failTest"},
		{LOOKAT, "failTest"},
		{AGGRO, "failTest"},
		{SCARE, "failTest"}
	}}
}
