selectattacksimple = {
	{"saroot", "CompositeDefault", "none", SEQUENCEBEHAVIOR},
	{"attack0", "SelectWeapon", "saroot", BEHAVIOR},
	{"attack1", "SelectAttack", "saroot", BEHAVIOR},
}

addAiTemplate("selectattacksimple", selectattacksimple)
