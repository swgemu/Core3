example = {
	defaultState = "SpawnStateComponent",
	transitions = {
		{"SpawnStateComponent", FINISHED, "StandingStateComponent"},
		{"StandingStateComponent", UNFINISHED, "StandingStateComponent"},
		{"StandingStateComponent", FINISHED, "WanderingStateComponent"},
		{"StandingStateComponent", ATTACKED, "AttackStateComponent"},
		{"StandingStateComponent", INTERESTED, "AlertStateComponent"},
		{"StandingStateComponent", DEAD, "DeathStateComponent"},
		{"WanderingStateComponent", UNFINISHED, "WanderingStateComponent"},
		{"WanderingStateComponent", FINISHED, "StandingStateComponent"},
		{"WanderingStateComponent", ATTACKED, "AttackStateComponent"},
		{"WanderingStateComponent", INTERESTED, "AlertStateComponent"},
		{"WanderingStateComponent", DEAD, "DeathStateComponent"},
		{"AlertStateComponent", INTERESTED, "AlertStateComponent"},
		{"AlertStateComponent", FORGOT, "StandingStateComponent"},
		{"AlertStateComponent", ATTACKED, "AttackStateComponent"},
		{"AlertStateComponent", DEAD, "DeathStateComponent"},
		{"AlertStateComponent", SCARED, "FleeStateComponent"},
		{"AttackStateComponent", UNFINISHED, "AttackStateComponent"},
		{"AttackStateComponent", FORGOT, "RetreatStateComponent"},
		{"AttackStateComponent", ATTACKED, "AttackStateComponent"},
		{"AttackStateComponent", DEAD, "DeathStateComponent"},
		{"AttackStateComponent", SCARED, "FleeStateComponent"},
		{"AttackStateComponent", ALMOSTDEAD, "FleeStateComponent"},
		{"FleeStateComponent", FORGOT, "RetreatStateComponent"},
		{"FleeStateComponent", DEAD, "DeathStateComponent"},
		{"RetreatStateComponent", FINISHED, "AlertStateComponent"},
		{"RetreatStateComponent", DEAD, "DeathStateComponent"},
		{"DeathStateComponent", UNFINISHED, "DeathStateComponent"},
		{"DeathStateComponent", FINISHED, "SpawnStateComponent"}
	}
}

addAiTemplate("example", example)