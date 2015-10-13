example = {
    {"root", "Selector", "none", ""},
    {"attack", "Sequence", "root", ""},
    {"wander", "Sequence", "root", ""},
	{"wander0", "Sequence", "wander", ""}, -- add an extra level here for runningChain tests
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
    {"gettar9", "AlwaysSucceed", "gettar8", ""},
    {"gettar10", "Selector", "gettar8", ""},
    {"gettar11", "Selector", "gettar9", ""},
    {"gettar12", "GetFollowFromThreatMap", "gettar11", ""},
    {"gettar13", "GetFollowFromDefenders", "gettar11", ""},
    {"gettar14", "Not", "gettar10", ""},
    {"gettar15", "Sequence", "gettar10", ""},
    {"gettar16", "AlwaysFail", "gettar10", ""},
    {"gettar17", "CheckHasFollow", "gettar14", ""},
    {"gettar18", "CheckFollowInRange", "gettar15", "condition=128"},
    {"gettar19", "CheckFollowAttackable", "gettar15", ""},
    {"gettar20", "Not", "gettar15", ""},
    {"gettar21", "Selector", "gettar20", ""},
    {"gettar22", "CheckFollowPosture", "gettar21", "condition=14"}, -- TODO: parse posture enums (DEAD)
    {"gettar23", "CheckFollowPosture", "gettar21", "condition=13"}, -- TODO: parse posture enums (INCAPACITATED)
    {"gettar25", "Sequence", "gettar16", ""},
    {"gettar26", "DropFollowFromDefenders", "gettar25", ""},
    {"gettar27", "RestoreFollow", "gettar25", ""},
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
    {"selwep11", "StageWeapon", "selwep7", "weaponType=1"}, -- TODO: parse weapon enums (WEAPONRANGED)
    {"selwep12", "CheckFollowInWeaponRange", "selwep8", "condition=2"}, -- TODO: parse weapon enums (WEAPONMELEE)
    {"selwep13", "CheckFollowClosestIdealRange", "selwep8", "condition=2"}, -- TODO: parse weapon enums (WEAPONMELEE)
    {"selwep14", "StageWeapon", "selwep8", "weaponType=2"}, -- TODO: parse weapon enums (WEAPONMELEE)
    {"selatt0", "Sequence", "attack", ""},
    {"selatt1", "NonDeterministicSelector", "selatt0", ""},
    {"selatt2", "Selector", "selatt0", ""},
    {"selatt3", "SelectAttack", "selatt1", "attackNum=-2"}, -- TODO: -2 means default attack, is there a better arg?
    {"selatt4", "SelectAttack", "selatt1", "attackNum=-1"},
    {"selatt5", "SelectAttack", "selatt1", "attackNum=-1"},
    {"selatt6", "SelectAttack", "selatt1", "attackNum=-1"},
    {"selatt7", "SelectAttack", "selatt1", "attackNum=-1"},
    {"selatt8", "Sequence", "selatt2", ""},
    {"selatt9", "SelectAttack", "selatt2", "attackNum=-2"},
    {"selatt10", "CheckAttackInRange", "selatt8", ""},
    {"selatt11", "CheckAttackIsValid", "selatt8", ""},
    {"commove0", "Selector", "attack", ""}, -- TODO: the move logic can be moved more into the btrees...
    {"commove1", "Not", "commove0", ""},
    {"commove2", "Sequence", "commove0", ""},
    {"commove3", "AlwaysFail", "commove0", ""},
    {"commove4", "FindNextPosition", "commove0", "mode=run"},
    {"commove5", "Sequence", "commove1", ""},
    {"commove6", "CheckRetreat", "commove2", "condition=256"},
    {"commove7", "Leash", "commove2", ""},
    {"commove8", "Sequence", "commove3", ""},
    {"commove9", "CheckPosture", "commove5", "condition=0"}, -- TODO: parse posture enums (UPRIGHT)
    {"commove10", "CheckDestination", "commove5", "condition=0"},
    {"commove11", "CheckSpeed", "commove8", "condition=0"},
    {"commove12", "CompleteMove", "commove8", ""},
    {"walkmove0", "Selector", "wander0", ""}, -- TODO: the move logic can be moved more into the btrees...
    {"walkmove1", "Not", "walkmove0", ""},
    {"walkmove2", "Sequence", "walkmove0", ""},
    {"walkmove3", "AlwaysFail", "walkmove0", ""},
    {"walkmove4", "FindNextPosition", "walkmove0", "mode=walk"},
    {"walkmove5", "Sequence", "walkmove1", ""},
    {"walkmove6", "CheckRetreat", "walkmove2", "condition=256"},
    {"walkmove7", "Leash", "walkmove2", ""},
    {"walkmove8", "Sequence", "walkmove3", ""},
    {"walkmove9", "CheckPosture", "walkmove5", "condition=0"}, -- TODO: parse posture enums (UPRIGHT)
    {"walkmove10", "CheckDestination", "walkmove5", "condition=0"},
    {"walkmove11", "CheckSpeed", "walkmove8", "condition=0"},
    {"walkmove12", "CompleteMove", "walkmove8", ""},
    {"wait0", "Wait", "wander0", "duration=10"},
}

addAiTemplate("example", example)
