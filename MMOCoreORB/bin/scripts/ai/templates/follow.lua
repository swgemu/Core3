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
	{"root", "MoveDefault", "none", BEHAVIOR},
}

addAiTemplate("follow", follow)
addAiTemplate("followc", followc)
addAiTemplate("followd", followd)
addAiTemplate("followf", followf)