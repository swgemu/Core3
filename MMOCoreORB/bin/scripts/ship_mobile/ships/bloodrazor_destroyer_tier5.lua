bloodrazor_destroyer_tier5 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "bomber",

	experience = 8053.06,

	lootChance = 0.156,
	lootRolls = 1,
	lootTable = "space_blacksun_tier5",

	minCredits = 465,
	maxCredits = 900,

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

ShipAgentTemplates:addShipAgentTemplate(bloodrazor_destroyer_tier5, "bloodrazor_destroyer_tier5")
