rancor_clan_soldier_tier4 = ShipAgent:new {
	template = "hutt_light_s02_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 200,
	maxCredits = 500,

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

ShipAgentTemplates:addShipAgentTemplate(rancor_clan_soldier_tier4, "rancor_clan_soldier_tier4")
