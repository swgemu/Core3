stationary = {
	{"root", "Composite", "none", SELECTORBEHAVIOR},
	{"attack", "Composite", "root", SEQUENCEBEHAVIOR},
	{"idle", "Composite", "root", SEQUENCEBEHAVIOR},
	{"idle0", "Move", "root", BEHAVIOR},
	{"idle1", "Wait", "root", BEHAVIOR},
	{"attack0", "GetTarget", "attack", BEHAVIOR},
	{"attack1", "SelectWeapon", "attack", BEHAVIOR},
	{"attack2", "SelectAttack", "attack", BEHAVIOR},
	{"attack3", "CombatMove", "attack", BEHAVIOR},
}

addAiTemplate("stationary", stationary)