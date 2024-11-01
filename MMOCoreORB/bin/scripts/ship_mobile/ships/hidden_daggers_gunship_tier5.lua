hidden_daggers_gunship_tier5 = ShipAgent:new {
	template = "imperial_gunboat_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "bomber",

	experience = 33554.43,

	lootChance = 0.65,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 617,
	maxCredits = 1100,

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

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_gunship_tier5, "hidden_daggers_gunship_tier5")
