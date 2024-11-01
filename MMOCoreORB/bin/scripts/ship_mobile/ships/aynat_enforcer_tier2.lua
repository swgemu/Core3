aynat_enforcer_tier2 = ShipAgent:new {
	template = "xwing_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "fighter",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian"},

	color1 = 63,
	color2 = 31,
	texture = 1,
	appearance = "aynat_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
	tauntAggressiveness = 0.05,
}

ShipAgentTemplates:addShipAgentTemplate(aynat_enforcer_tier2, "aynat_enforcer_tier2")
