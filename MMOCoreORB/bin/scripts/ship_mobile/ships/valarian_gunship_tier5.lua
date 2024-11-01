valarian_gunship_tier5 = ShipAgent:new {
	template = "hutt_heavy_s02_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "fighter",

	experience = 8724.15,

	lootChance = 0.169,
	lootRolls = 1,
	lootTable = "space_valarian_tier5",

	minCredits = 465,
	maxCredits = 925,

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

ShipAgentTemplates:addShipAgentTemplate(valarian_gunship_tier5, "valarian_gunship_tier5")
