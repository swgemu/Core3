enclavesentinel = {
	{"root", "CompositeEnclaveSentinel", "none", SELECTORBEHAVIOR},
	{"attack", "CompositeEnclaveSentinel", "root", SEQUENCEBEHAVIOR},
	{"idle", "CompositeEnclaveSentinel", "root", SEQUENCEBEHAVIOR},
	{"idle0", "MoveEnclaveSentinel", "root", BEHAVIOR},
	{"idle1", "WaitEnclaveSentinel", "root", BEHAVIOR},
	{"attack0", "GetTargetEnclaveSentinel", "attack", BEHAVIOR},
	{"attack1", "SelectWeaponEnclaveSentinel", "attack", BEHAVIOR},
	{"attack2", "SelectAttackEnclaveSentinel", "attack", BEHAVIOR},
	{"attack3", "CombatMoveEnclaveSentinel", "attack", BEHAVIOR},
}

addAiTemplate("enclavesentinel", enclavesentinel)
