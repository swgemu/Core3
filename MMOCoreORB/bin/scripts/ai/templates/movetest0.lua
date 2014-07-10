movetest0 = {
	{"root", "Composite", "none", SELECTORBEHAVIOR},
	{"move0", "Composite", "root", SEQUENCEBEHAVIOR},
	{"move1", "GeneratePatrol", "root", BEHAVIOR},
	{"move00", "Walk", "move0", BEHAVIOR},
	{"move01", "Wait10", "move0", BEHAVIOR}
	
}

addAiTemplate("movetest0", movetest0)