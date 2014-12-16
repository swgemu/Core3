selectattackpetc = {
	{"saroot", "CompositeCreaturePet", "none", SEQUENCEBEHAVIOR},
	{"attack0", "SelectWeaponCreaturePet", "saroot", BEHAVIOR},
	{"attack1", "SelectAttackCreaturePet", "saroot", BEHAVIOR},
}
selectattackpetd = {
	{"saroot", "CompositeDroidPet", "none", SEQUENCEBEHAVIOR},
	{"attack0", "SelectWeaponDroidPet", "saroot", BEHAVIOR},
	{"attack1", "SelectAttackDroidPet", "saroot", BEHAVIOR},
}
selectattackpetf = {
	{"saroot", "CompositeFactionPet", "none", SEQUENCEBEHAVIOR},
	{"attack0", "SelectWeaponFactionPet", "saroot", BEHAVIOR},
	{"attack1", "SelectAttackFactionPet", "saroot", BEHAVIOR},
}

addAiTemplate("selectattackpetc", selectattackpetc)
addAiTemplate("selectattackpetd", selectattackpetd)
addAiTemplate("selectattackpetf", selectattackpetf)