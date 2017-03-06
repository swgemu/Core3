villageraider = {
	{"root", "CompositeVillageRaider", "none", SELECTORBEHAVIOR},
	{"attack", "CompositeVillageRaider", "root", SEQUENCEBEHAVIOR},
	{"move", "CompositeVillageRaider", "root", SEQUENCEBEHAVIOR},
	{"patrol", "GeneratePatrolVillageRaider", "root", BEHAVIOR},
	{"attack0", "GetTargetVillageRaider", "attack", BEHAVIOR},
	{"attack1", "SelectWeaponVillageRaider", "attack", BEHAVIOR},
	{"attack2", "SelectAttackVillageRaider", "attack", BEHAVIOR},
	{"attack3", "CombatMoveVillageRaider", "attack", BEHAVIOR},
	{"move0", "MoveVillageRaider", "move", BEHAVIOR},
	{"move1", "Wait10VillageRaider", "move", BEHAVIOR},
}

addAiTemplate("villageraider", villageraider)
