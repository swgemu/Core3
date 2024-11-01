valarian_gunship_tier3 = ShipAgent:new {
	template = "hutt_heavy_s02_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "fighter",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_valarian_tier3",

	minCredits = 170,
	maxCredits = 382,

	aggressive = 1,

	spaceFaction = "valarian",
	alliedFactions = {"valarian"},
	enemyFactions = {"imperial", "civilian", "merchant", "hutt", "pirate", "rebel", "blacksun", "borvo", "corsec", "rsf"},

	color1 = 32,
	color2 = 35,
	texture = 3,
	appearance = "valarian",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(valarian_gunship_tier3, "valarian_gunship_tier3")
