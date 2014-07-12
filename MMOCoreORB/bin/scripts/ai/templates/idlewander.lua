idlewander = {
	{"idroot", "CompositeDefault", "none", SELECTORBEHAVIOR},
	{"move", "CompositeDefault", "idroot", SEQUENCEBEHAVIOR},
	{"patrol", "GeneratePatrolDefault", "idroot", BEHAVIOR},
	{"move0", "WalkDefault", "move", BEHAVIOR},
	{"move1", "Wait10Default", "move", BEHAVIOR},
}

addAiTemplate("idlewander", idlewander)