citypatrol = {
	{"root", "CompositeCityPatrol", "none", SEQUENCEBEHAVIOR},
	{"move0", "WalkCityPatrol", "root", BEHAVIOR},
	{"move1", "WaitCityPatrol", "root", BEHAVIOR},
}

addAiTemplate("citypatrol", citypatrol)

combatpatrol = {
	{"root", "CompositeCombatPatrol", "none", SELECTORBEHAVIOR},
	{"attack", "CompositeCombatPatrol", "root", SEQUENCEBEHAVIOR},
	{"move", "CompositeCombatPatrol", "root", SEQUENCEBEHAVIOR},
	{"move0", "WalkCombatPatrol", "root", BEHAVIOR},
	{"move1", "WaitCombatPatrol", "root", BEHAVIOR},
	{"attack0", "GetTargetCombatPatrol", "attack", BEHAVIOR},
	{"attack1", "SelectWeaponCombatPatrol", "attack", BEHAVIOR},
	{"attack2", "SelectAttackCombatPatrol", "attack", BEHAVIOR},
	{"attack3", "CombatMoveCombatPatrol", "attack", BEHAVIOR},
}

addAiTemplate("combatpatrol", combatpatrol)