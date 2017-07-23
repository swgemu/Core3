deathwatchdefender = {
	{"root", "CompositeDeathWatchDefender", "none", SELECTORBEHAVIOR},
	{"attack", "CompositeDeathWatchDefender", "root", SEQUENCEBEHAVIOR},
	{"move", "CompositeDeathWatchDefender", "root", SEQUENCEBEHAVIOR},
	{"idle0", "MoveDeathWatchDefender", "root", BEHAVIOR},
	{"idle1", "WaitDeathWatchDefender", "root", BEHAVIOR},
	{"attack0", "GetTargetDeathWatchDefender", "attack", BEHAVIOR},
	{"attack1", "SelectWeaponDeathWatchDefender", "attack", BEHAVIOR},
	{"attack2", "SelectAttackDeathWatchDefender", "attack", BEHAVIOR},
	{"attack3", "CombatMoveDeathWatchDefender", "attack", BEHAVIOR},
}

addAiTemplate("deathwatchdefender", deathwatchdefender)
