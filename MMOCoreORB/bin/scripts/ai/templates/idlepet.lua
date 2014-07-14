idlepet = {
	{"idroot", "CompositePet", "none", SELECTORBEHAVIOR},
	{"move", "MovePet", "idroot", BEHAVIOR},
	{"wait", "WaitPet", "idroot", BEHAVIOR},
}

addAiTemplate("idlepet", idlepet)