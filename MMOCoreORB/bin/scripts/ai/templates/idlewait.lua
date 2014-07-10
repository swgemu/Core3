idlewait = {
	{"idroot", "Composite", "none", SEQUENCEBEHAVIOR},
	{"move0", "Move", "idroot", BEHAVIOR},
	{"move1", "Wait", "idroot", BEHAVIOR},
}

addAiTemplate("idlewait", idlewait)