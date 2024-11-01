hidden_daggers_gunship_tier2 = ShipAgent:new {
	template = "imperial_gunboat_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "bomber",

	experience = 2000,

	lootChance = 0.8,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 180,
	maxCredits = 460,

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

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_gunship_tier2, "hidden_daggers_gunship_tier2")
