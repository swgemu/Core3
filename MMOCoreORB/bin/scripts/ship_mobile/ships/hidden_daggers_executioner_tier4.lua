hidden_daggers_executioner_tier4 = ShipAgent:new {
	template = "xwing_tier4",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "fighter",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 260,
	maxCredits = 575,

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

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_executioner_tier4, "hidden_daggers_executioner_tier4")
