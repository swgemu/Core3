followc = {
	{"root", "MoveCreaturePet", "none", BEHAVIOR},
}
followd = {
	{"root", "MoveDroidPet", "none", BEHAVIOR},
}
followf = {
	{"root", "MoveFactionPet", "none", BEHAVIOR},
}
follow = {
	{"root", "MoveCreaturePet", "none", BEHAVIOR},
}
escort = {
	{"root", "MoveEscort", "none", BEHAVIOR},
}

addAiTemplate("escort", escort)
addAiTemplate("follow", follow)
addAiTemplate("followc", followc)
addAiTemplate("followd", followd)
addAiTemplate("followf", followf)