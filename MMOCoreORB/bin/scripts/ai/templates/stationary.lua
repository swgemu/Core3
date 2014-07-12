stationary = {
	{"root", "Composite", "none", SELECTORBEHAVIOR},
	{"attack", "Composite", "root", SEQUENCEBEHAVIOR},
	{"idle", "CompositeDefault", "root", SEQUENCEBEHAVIOR},
	{"idle0", "MoveDefault", "root", BEHAVIOR},
	{"idle1", "WaitDefault", "root", BEHAVIOR},
	{"attack0", "GetTarget", "attack", BEHAVIOR},
	{"attack1", "SelectWeapon", "attack", BEHAVIOR},
	{"attack2", "SelectAttack", "attack", BEHAVIOR},
	{"attack3", "CombatMove", "attack", BEHAVIOR},
}

addAiTemplate("stationary", stationary)