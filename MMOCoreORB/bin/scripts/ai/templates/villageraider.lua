villageraider = {
	{"root", "CompositeVillageRaider", "none", SELECTORBEHAVIOR},
	{"attack", "CompositeVillageRaider", "root", SEQUENCEBEHAVIOR},
	{"idle", "CompositeVillageRaider", "root", SEQUENCEBEHAVIOR},
	{"idle0", "MoveVillageRaider", "root", BEHAVIOR},
	{"idle1", "WaitVillageRaider", "root", BEHAVIOR},
	{"attack0", "GetTargetVillageRaider", "attack", BEHAVIOR},
	{"attack1", "SelectWeaponVillageRaider", "attack", BEHAVIOR},
	{"attack2", "SelectAttackVillageRaider", "attack", BEHAVIOR},
	{"attack3", "CombatMoveVillageRaider", "attack", BEHAVIOR},
}

addAiTemplate("villageraider", villageraider)
