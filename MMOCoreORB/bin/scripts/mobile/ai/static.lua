static = {
	defaultState = "StandingStateComponent",
	transitions = {
		{"SpawnStateComponent", FINISHED, "StandingStateComponent"},
		{"StandingStateComponent", DEAD, "DeathStateComponent"},
		{"DeathStateComponent", FINISHED, "SpawnStateComponent"}
	}
}

addAiTemplate("static", static)