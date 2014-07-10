idlewander = {
	{"idroot", "Composite", "none", SELECTORBEHAVIOR},
	{"move", "Composite", "idroot", SEQUENCEBEHAVIOR},
	{"patrol", "GeneratePatrol", "idroot", BEHAVIOR},
	{"move0", "Walk", "move", BEHAVIOR},
	{"move1", "Wait10", "move", BEHAVIOR},
}

addAiTemplate("idlewander", idlewander)