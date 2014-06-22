idlewander = {
	{"root", "Composite", "none", SELECTORBEHAVIOR},
	{"move", "Composite", "root", SEQUENCEBEHAVIOR},
	{"patrol", "GeneratePatrol", "root", BEHAVIOR},
	{"move0", "Walk", "move", BEHAVIOR},
	{"move1", "Wait10", "move", BEHAVIOR},
}

addAiTemplate("idlewander", idlewander)