blah = {
	{"root", "Composite", "none", SELECTORBEHAVIOR},
	{"wander", "Composite", "root", SEQUENCEBEHAVIOR},
	{"wander1", "Wait10Default", "wander", BEHAVIOR},
	{"wander0", "WalkDefault", "wander", BEHAVIOR},
	{"patrol", "GeneratePatrolDefault", "root", BEHAVIOR},
	{"attack", "Composite", "root", SEQUENCEBEHAVIOR},
	{"attack3", "CombatMove", "attack", BEHAVIOR},
	{"attack2", "SelectAttack", "attack", BEHAVIOR},
	{"attack1", "SelectWeapon", "attack", BEHAVIOR},
	{"attack0", "GetTarget", "attack", BEHAVIOR},
}

addAiTemplate("blah", blah)