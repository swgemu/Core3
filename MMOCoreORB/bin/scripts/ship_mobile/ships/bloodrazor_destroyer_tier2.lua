bloodrazor_destroyer_tier2 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "bomber",

	experience = 480,

	lootChance = 0.192,
	lootRolls = 1,
	lootTable = "space_blacksun_tier2",

	minCredits = 75,
	maxCredits = 160,

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

ShipAgentTemplates:addShipAgentTemplate(bloodrazor_destroyer_tier2, "bloodrazor_destroyer_tier2")
