hidden_daggers_gunship_tier1 = ShipAgent:new {
	template = "imperial_gunboat_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "bomber",

	experience = 500,

	lootChance = 0.85,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 80,
	maxCredits = 200,

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

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_gunship_tier1, "hidden_daggers_gunship_tier1")
