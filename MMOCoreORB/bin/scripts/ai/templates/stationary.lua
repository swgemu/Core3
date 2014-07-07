stationary = {
	{"root", "Composite", "none", SELECTORBEHAVIOR},
	{"attack", "Composite", "root", SEQUENCEBEHAVIOR},
	{"wait", "Wait", "root", BEHAVIOR},
	{"attack0", "GetTarget", "attack", BEHAVIOR},
	{"attack1", "SelectWeapon", "attack", BEHAVIOR},
	{"attack2", "SelectAttack", "attack", BEHAVIOR},
	{"attack3", "Move", "attack", BEHAVIOR},
}

addAiTemplate("stationary", stationary)