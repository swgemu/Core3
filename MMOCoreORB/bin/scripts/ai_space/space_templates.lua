includeFile("default.lua")
includeFile("escort.lua")
includeFile("spaceStations.lua")
includeFile("turretship.lua")

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

	{ESCORT, {
		{NONESPACE, "rootEscort"},
		{MOVESPACE, "moveEscort"},
		{IDLESPACE, "idleEscort"},
	}},

	{TURRETSHIP, {
		{ATTACKSPACE, "attackTurretship"},
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
