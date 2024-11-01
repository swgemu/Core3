hidden_daggers_nebula_stalker_tier5 = ShipAgent:new {
	template = "hutt_medium_s01_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "rsf", "corsec"},

	color1 = 3,
	color2 = 55,
	texture = 3,
	appearance = "hiddendagger_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_nebula_stalker_tier5, "hidden_daggers_nebula_stalker_tier5")
