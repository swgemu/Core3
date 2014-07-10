example = {
	{"root", "Composite", "none", SELECTORBEHAVIOR},
	{"attack", "Composite", "root", SEQUENCEBEHAVIOR},
	{"wander", "Composite", "root", SEQUENCEBEHAVIOR},
	{"patrol", "GeneratePatrol", "root", BEHAVIOR},
	{"attack0", "GetTarget", "attack", BEHAVIOR},
	{"attack1", "SelectWeapon", "attack", BEHAVIOR},
	{"attack2", "SelectAttack", "attack", BEHAVIOR},
	{"attack3", "CombatMove", "attack", BEHAVIOR},
	{"wander0", "Walk", "wander", BEHAVIOR},
	{"wander1", "Wait10", "wander", BEHAVIOR},
}

addAiTemplate("example", example)