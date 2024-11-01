bloodrazor_destroyer_tier3 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "bomber",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_blacksun_tier3",

	minCredits = 160,
	maxCredits = 353,

	aggressive = 0,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun", "nym"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec", "pirate"},

	color1 = 7,
	color2 = 3,
	texture = 4,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(bloodrazor_destroyer_tier3, "bloodrazor_destroyer_tier3")
