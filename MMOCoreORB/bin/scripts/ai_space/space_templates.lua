includeFile("default.lua")
includeFile("spaceStations.lua")

customMap = {
	{ "spaceStations", {
		{NONESPACE, "rootSpacestations"}
	}},
}

bitmaskLookup = {
	{NONE, {
		{NONESPACE, "rootDefault"},
		{AWARESPACE, "awareDefault"},
		{EVADESPACE, "evadeDefault"},
		{IDLESPACE, "idleDefault"},
		{ATTACKSPACE, "attackDefault"},
		{TARGETSPACE, "targetDefault"},
		{MOVESPACE, "moveDefault"},
		{LOOKATSPACE, "lookDefault"},
		{AGGROSPACE, "aggroDefault"}
	}},

	{TEST, {
		{AWARESPACE, "failTest"},
		{IDLESPACE, "succeedTest"},
		{ATTACKSPACE, "failTest"},
		{TARGETSPACE, "failTest"},
		{MOVESPACE, "failTest"},
		{LOOKATSPACE, "failTest"},
		{AGGROSPACE, "failTest"}
	}}
}
