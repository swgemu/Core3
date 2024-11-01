hidden_daggers_gunship_tier4 = ShipAgent:new {
	template = "imperial_gunboat_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "bomber",

	experience = 16384,

	lootChance = 0.7,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 500,
	maxCredits = 1000,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "rsf", "corsec"},
	appearance = "hiddendagger_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_gunship_tier4, "hidden_daggers_gunship_tier4")
