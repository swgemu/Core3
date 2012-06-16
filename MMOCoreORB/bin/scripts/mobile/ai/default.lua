default = {
	defaultState = "StandingStateComponent",
	transitions = {
		{"SpawnStateComponent", FINISHED, "StandingStateComponent"},
		{"StandingStateComponent", FINISHED, "WanderingStateComponent"},
		{"StandingStateComponent", ATTACKED, "AttackStateComponent"},
		{"StandingStateComponent", INTERESTED, "AlertStateComponent"},
		{"StandingStateComponent", DEAD, "DeathStateComponent"},
		{"WanderingStateComponent", FINISHED, "StandingStateComponent"},
		{"WanderingStateComponent", ATTACKED, "AttackStateComponent"},
		{"WanderingStateComponent", INTERESTED, "AlertStateComponent"},
		{"WanderingStateComponent", DEAD, "DeathStateComponent"},
		{"AlertStateComponent", FORGOT, "StandingStateComponent"},
		{"AlertStateComponent", ATTACKED, "AttackStateComponent"},
		{"AlertStateComponent", DEAD, "DeathStateComponent"},
		{"AlertStateComponent", SCARED, "FleeStateComponent"},
		{"AttackStateComponent", FORGOT, "RetreatStateComponent"},
		{"AttackStateComponent", ATTACKED, "AttackStateComponent"},
		{"AttackStateComponent", DEAD, "DeathStateComponent"},
		{"AttackStateComponent", SCARED, "FleeStateComponent"},
		{"AttackStateComponent", ALMOSTDEAD, "FleeStateComponent"},
		{"FleeStateComponent", FORGOT, "RetreatStateComponent"},
		{"FleeStateComponent", DEAD, "DeathStateComponent"},
		{"RetreatStateComponent", FINISHED, "StandingStateComponent"},
		{"RetreatStateComponent", DEAD, "DeathStateComponent"},
		{"DeathStateComponent", FINISHED, "SpawnStateComponent"}
	}
}

addAiTemplate("default", default)