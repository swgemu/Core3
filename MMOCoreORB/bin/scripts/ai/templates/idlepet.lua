idlepetc = {
	{"idroot", "CompositeCreaturePet", "none", SELECTORBEHAVIOR},
	{"move", "CompositeCreaturePet", "idroot", SEQUENCEBEHAVIOR},
	{"wait", "WaitCreaturePet", "idroot", BEHAVIOR},
	{"move0", "MoveCreaturePet", "move", BEHAVIOR},
	{"move1", "Wait10CreaturePet", "move", BEHAVIOR},
}
idlepetd = {
	{"idroot", "CompositeDroidPet", "none", SELECTORBEHAVIOR},
	{"move", "CompositeDroidPet", "idroot", SEQUENCEBEHAVIOR},
	{"wait", "WaitDroidPet", "idroot", BEHAVIOR},
	{"move0", "MoveDroidPet", "move", BEHAVIOR},
	{"move1", "Wait10DroidPet", "move", BEHAVIOR},
}
idlepetf = {
	{"idroot", "CompositeFactionPet", "none", SELECTORBEHAVIOR},
	{"move", "CompositeFactionPet", "idroot", SEQUENCEBEHAVIOR},
	{"wait", "WaitFactionPet", "idroot", BEHAVIOR},
	{"move0", "MoveFactionPet", "move", BEHAVIOR},
	{"move1", "Wait10FactionPet", "move", BEHAVIOR},
}

addAiTemplate("idlepetc", idlepetc)
addAiTemplate("idlepetd", idlepetd)
addAiTemplate("idlepetf", idlepetf)
