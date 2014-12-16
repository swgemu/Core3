idlepetc = {
	{"idroot", "CompositeCreaturePet", "none", SELECTORBEHAVIOR},
	{"move", "MoveCreaturePet", "idroot", BEHAVIOR},
	{"wait", "WaitCreaturePet", "idroot", BEHAVIOR},
}
idlepetd = {
	{"idroot", "CompositeDroidPet", "none", SELECTORBEHAVIOR},
	{"move", "MoveDroidPet", "idroot", BEHAVIOR},
	{"wait", "WaitDroidPet", "idroot", BEHAVIOR},
}
idlepetf = {
	{"idroot", "CompositeFactionPet", "none", SELECTORBEHAVIOR},
	{"move", "MoveFactionPet", "idroot", BEHAVIOR},
	{"wait", "WaitFactionPet", "idroot", BEHAVIOR},
}

addAiTemplate("idlepetc", idlepetc)
addAiTemplate("idlepetd", idlepetd)
addAiTemplate("idlepetf", idlepetf)