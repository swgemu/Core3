idlewait = {
	{"idroot", "CompositeDefault", "none", SEQUENCEBEHAVIOR},
	{"move0", "MoveDefault", "idroot", BEHAVIOR},
	{"move1", "WaitDefault", "idroot", BEHAVIOR},
}

addAiTemplate("idlewait", idlewait)