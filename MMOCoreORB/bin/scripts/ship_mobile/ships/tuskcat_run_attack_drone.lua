tuskcat_run_attack_drone = ShipAgent:new {
	template = "droid_fighter_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "pirate",
	enemyFactions = {"rebel", "corsec", "rsf", "hutt", "valarian"},
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(tuskcat_run_attack_drone, "tuskcat_run_attack_drone")
