hidden_blackrazorcat = ShipAgent:new {
	template = "awing_tier3",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "rsf", "corsec"},

	color1 = 63,
	color2 = 3,
	texture = 3,
	appearance = "hiddendagger_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hidden_blackrazorcat, "hidden_blackrazorcat")
