idlewander = {
	{"idroot", "CompositeDefault", "none", SELECTORBEHAVIOR},
	{"move", "CompositeDefault", "idroot", SEQUENCEBEHAVIOR},
	{"patrol", "GeneratePatrolDefault", "idroot", BEHAVIOR},
	{"move0", "WalkDefault", "move", BEHAVIOR},
	{"move1", "Wait10Default", "move", BEHAVIOR},
}

addAiTemplate("idlewander", idlewander)

idlewanderpack = {
	{"idroot", "CompositePack", "none", SELECTORBEHAVIOR},
	{"move", "CompositePack", "idroot", SEQUENCEBEHAVIOR},
	{"patrol", "GeneratePatrolPack", "idroot", BEHAVIOR},
	{"move0", "WalkPack", "move", BEHAVIOR},
	{"move1", "Wait10Pack", "move", BEHAVIOR},
}

addAiTemplate("idlewanderpack", idlewanderpack)

idlewanderstatic = {
	{"idroot", "CompositeDefault", "none", SELECTORBEHAVIOR},
	{"move0", "WalkDefault", "idroot", BEHAVIOR},
	{"move1", "Wait10Default", "idroot", BEHAVIOR},
}

addAiTemplate("idlewanderstatic", idlewanderstatic)
