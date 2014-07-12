example = {
	{"root", "Composite", "none", SELECTORBEHAVIOR},
	{"attack", "Composite", "root", SEQUENCEBEHAVIOR},
	{"wander", "CompositeDefault", "root", SEQUENCEBEHAVIOR},
	{"patrol", "GeneratePatrolDefault", "root", BEHAVIOR},
	{"attack0", "GetTarget", "attack", BEHAVIOR},
	{"attack1", "SelectWeapon", "attack", BEHAVIOR},
	{"attack2", "SelectAttack", "attack", BEHAVIOR},
	{"attack3", "CombatMove", "attack", BEHAVIOR},
	{"wander0", "WalkDefault", "wander", BEHAVIOR},
	{"wander1", "Wait10Default", "wander", BEHAVIOR},
}

addAiTemplate("example", example)