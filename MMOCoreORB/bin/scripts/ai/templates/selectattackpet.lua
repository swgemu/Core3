selectattackpet = {
	{"saroot", "CompositePet", "none", SEQUENCEBEHAVIOR},
	{"attack0", "SelectWeaponPet", "saroot", BEHAVIOR},
	{"attack1", "SelectAttackPet", "saroot", BEHAVIOR},
}

addAiTemplate("selectattackpet", selectattackpet)