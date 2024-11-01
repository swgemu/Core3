hidden_daggers_executioner_tier5 = ShipAgent:new {
	template = "xwing_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 7381.98,

	lootChance = 0.143,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 455,
	maxCredits = 875,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "rsf", "corsec"},

	color1 = 33,
	color2 = 55,
	texture = 2,
	appearance = "hiddendagger_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_executioner_tier5, "hidden_daggers_executioner_tier5")
