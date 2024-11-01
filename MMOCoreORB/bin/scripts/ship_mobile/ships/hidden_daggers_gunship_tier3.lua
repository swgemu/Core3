hidden_daggers_gunship_tier3 = ShipAgent:new {
	template = "imperial_gunboat_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "bomber",

	experience = 6400,

	lootChance = 0.75,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 350,
	maxCredits = 750,

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

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_gunship_tier3, "hidden_daggers_gunship_tier3")
