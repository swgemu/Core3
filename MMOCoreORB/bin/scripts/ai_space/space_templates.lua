includeFile("default.lua")

customMap = {
}

bitmaskLookup = {
	{NONE, {
		{NONESPACE, "rootDefault"},
		{SPACE, "awareDefault"},
		{IDLESPACE, "idleDefault"},
		{ATTACKSPACE, "attackDefault"},
		{TARGETSPACE, "targetDefault"},
		{MOVESPACE, "moveDefault"},
		{LOOKATSPACE, "lookDefault"},
		{AGGROSPACE, "aggroDefault"},
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
