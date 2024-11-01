rancor_clan_elite = ShipAgent:new {
	template = "hutt_medium_s02_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "corsec", "rsf", "borvo", "nym"},

	color1 = 25,
	color2 = 59,
	texture = 3,
	appearance = "rancor_clan_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rancor_clan_elite, "rancor_clan_elite")
