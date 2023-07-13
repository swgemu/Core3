includeFile("default.lua")

customMap = {
}

bitmaskLookup = {
	{NONE, {
		{NONE, "rootDefault"},
		{IDLE, "idleDefault"},
		{MOVE, "moveDefault"},
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
