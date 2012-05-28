example = {
	defaultState = "StandingStateComponent",
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
		{"AlertStateComponent", UNFINISHED, "AlertStateComponent"},
		{"AlertStateComponent", FINISHED, "StandingStateComponent"},
		{"AlertStateComponent", ATTACKED, "AttackStateComponent"},
		{"AlertStateComponent", DEAD, "DeathStateComponent"},
		{"AttackStateComponent", UNFINISHED, "AttackStateComponent"},
		{"AttackStateComponent", FORGOT, "StandingStateComponent"},
		{"AttackStateComponent", ATTACKED, "AttackStateComponent"},
		{"AttackStateComponent", DEAD, "DeathStateComponent"},
		{"AttackStateComponent", SCARED, "FleeStateComponent"},
		{"AttackStateComponent", ALMOSTDEAD, "FleeStateComponent"},
		{"FleeStateComponent", FORGOT, "AlertStateComponent"},
		{"FleeStateComponent", DEAD, "DeathStateComponent"},
		{"DeathStateComponent", UNFINISHED, "DeathStateComponent"},
		{"DeathStateComponent", FINISHED, "SpawnStateComponent"}
	}
}

addAiTemplate("example", example)