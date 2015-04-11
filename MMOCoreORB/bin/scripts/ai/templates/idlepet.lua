idlepetc = {
	{"idroot", "CompositeCreaturePet", "none", SELECTORBEHAVIOR},
	{"patrol", "CompositeCreaturePet", "idroot", SEQUENCEBEHAVIOR},
	{"move", "MoveCreaturePet", "idroot", BEHAVIOR},
	{"wait", "WaitCreaturePet", "idroot", BEHAVIOR},
	{"patrol0", "WalkCreaturePet", "patrol", BEHAVIOR},
	{"patrol1", "Wait10CreaturePet", "patrol", BEHAVIOR},
}
idlepetd = {
	{"idroot", "CompositeDroidPet", "none", SELECTORBEHAVIOR},
	{"patrol", "CompositeDroidPet", "idroot", SEQUENCEBEHAVIOR},
	{"move", "MoveDroidPet", "idroot", BEHAVIOR},
	{"wait", "WaitDroidPet", "idroot", BEHAVIOR},
	{"patrol0", "WalkDroidPet", "patrol", BEHAVIOR},
	{"patrol1", "Wait10DroidPet", "patrol", BEHAVIOR},
}
idlepetf = {
	{"idroot", "CompositeFactionPet", "none", SELECTORBEHAVIOR},
	{"patrol", "CompositeFactionPet", "idroot", SEQUENCEBEHAVIOR},
	{"move", "MoveFactionPet", "idroot", BEHAVIOR},
	{"wait", "WaitFactionPet", "idroot", BEHAVIOR},
	{"patrol0", "WalkFactionPet", "patrol", BEHAVIOR},
	{"patrol1", "Wait10FactionPet", "patrol", BEHAVIOR},
}

addAiTemplate("idlepetc", idlepetc)
addAiTemplate("idlepetd", idlepetd)
addAiTemplate("idlepetf", idlepetf)
