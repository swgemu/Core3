rancor_clan_soldier_tier3 = ShipAgent:new {
	template = "hutt_light_s02_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "corsec", "rsf", "borvo", "nym"},

	color1 = 25,
	color2 = 59,
	texture = 3,
	appearance = "rancor_clan_pilots",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rancor_clan_soldier_tier3, "rancor_clan_soldier_tier3")
