manualescort = {
	{"idroot", "CompositeDefault", "none", SEQUENCEBEHAVIOR},
	{"move0", "MoveDefault", "idroot", BEHAVIOR},
	{"move1", "WaitDefault", "idroot", BEHAVIOR},
}

manualescortwalk = {
	{"idroot", "CompositeDefault", "none", SEQUENCEBEHAVIOR},
	{"move0", "WalkDefault", "idroot", BEHAVIOR},
	{"move1", "WaitDefault", "idroot", BEHAVIOR},
}

addAiTemplate("manualescort", manualescort)
addAiTemplate("manualescortwalk", manualescortwalk)