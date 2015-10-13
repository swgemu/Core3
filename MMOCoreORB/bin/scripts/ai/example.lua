example = {
	{"root", "Selector", "none", ""},
	{"attack", "Sequence", "root", ""},
	{"wander", "Sequence", "root", ""},
	{"patrol", "GeneratePatrol", "root", "numPoints=5:distFromHome=10"},
	{"gettar0", "Selector", "attack", ""},
	{"gettar1", "Sequence", "gettar0", ""},
	{"gettar2", "ExitCombat", "gettar0", "clearDefenders=true"},
	{"gettar3", "Sequence", "gettar1", ""},
	{"gettar4", "AlwaysSucceed", "gettar1", ""},
	{"gettar5", "UntilSuccess", "gettar3", ""},
	{"gettar6", "Selector", "gettar3", ""},
	{"gettar7", "SetDefenderFromFollow", "gettar3", ""},
	{"gettar8", "Sequence", "gettar5", ""},
	{"gettar9", "AlwaysSucceed", "gettar6", ""},
	{"gettar10", "Selector", "gettar6", ""},
	{"gettar11", "Selector", "gettar7", ""},
	{"gettar12", "GetFollowFromThreatMap", "gettar9", ""},
	{"gettar13", "GetFollowFromDefenders", "gettar9", ""},
	{"gettar14", "Not", "gettar8", ""},
	{"gettar15", "Sequence", "gettar8", ""},
	{"gettar16", "AlwaysFail", "gettar8", ""},
	{"gettar17", "CheckHasFollow", "gettar12", ""},
	{"gettar18", "CheckFollowInRange", "gettar13", "condition=128"},
	{"gettar19", "CheckFollowAttackable", "gettar13", ""},
	{"gettar20", "Not", "gettar13", ""},
	{"gettar21", "Selector", "gettar18", ""},
	{"gettar22", "CheckFollowPosture", "gettar19", "condition=14"}, -- TODO: parse posture enums (DEAD)
	{"gettar23", "CheckFollowPosture", "gettar19", "condition=13"}, -- TODO: parse posture enums (INCAPACITATED)
	{"gettar25", "Sequence", "gettar14", ""},
	{"gettar26", "DropFollowFromDefenders", "gettar23", ""},
	{"gettar27", "RestoreFollow", "gettar23", ""},
	{"gettar28", "CheckHasFollow", "gettar6", ""},
	{"gettar29", "AlwaysFail", "gettar6", ""},
	{"gettar30", "RestoreFollow", "gettar29", ""},
	{"gettar31", "Sequence", "gettar4", ""},
	{"gettar32", "CheckFollowHasState", "gettar31", "condition=4"}, -- TODO: Need to parse PEACE and other enums
	{"gettar33", "CheckRandomLevel", "gettar31", "condition=1"},
	{"gettar34", "Not", "gettar31", ""},
	{"gettar35", "ExitCombat", "gettar31", "clearDefenders=true"},
	{"gettar36", "CheckFollowAggression", "gettar34", ""},
    {"selwep0", "ParallelSequence", "attack", ""},
    {"selwep1", "Sequence", "selwep0", ""},
    {"selwep2", "EraseBlackboard", "selwep0", "param=stagedWeapon"},
    {"selwep3", "EraseBlackboard", "selwep0", "param=followRange"},
    {"selwep4", "UpdateRangeToFollow", "selwep1", ""},
    {"selwep5", "Selector", "selwep1", ""},
    {"selwep6", "EquipStagedWeapon", "selwep1", ""},
    {"selwep7", "Sequence", "selwep5", ""},
    {"selwep8", "Sequence", "selwep5", ""},
    {"selwep9", "CheckFollowInWeaponRange", "selwep7", "condition=1"}, -- TODO: parse weapon enums (WEAPONRANGED)
    {"selwep10", "CheckFollowClosestIdealRange", "selwep7", "condition=1"}, -- TODO: parse weapon enums (WEAPONRANGED)
    {"selwep11", "StageWeapon", "selwep7", "condition=1"}, -- TODO: parse weapon enums (WEAPONRANGED)
    {"selwep12", "CheckFollowInWeaponRange", "selwep8", "condition=2"}, -- TODO: parse weapon enums (WEAPONDEFAULT)
    {"selwep13", "CheckFollowClosestIdealRange", "selwep8", "condition=2"}, -- TODO: parse weapon enums (WEAPONDEFAULT)
    {"selwep14", "StageWeapon", "selwep8", "condition=2"}, -- TODO: parse weapon enums (WEAPONDEFAULT)
	{"attack2", "SelectAttack", "attack", BEHAVIOR},
	{"attack3", "CombatMove", "attack", BEHAVIOR},
	{"wander0", "WalkDefault", "wander", BEHAVIOR},
	{"wander1", "Wait10Default", "wander", BEHAVIOR},
}

addAiTemplate("example", example)
