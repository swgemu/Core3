bloodrazor_destroyer_tier1 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "bomber",

	experience = 120,

	lootChance = 0.204,
	lootRolls = 1,
	lootTable = "space_blacksun_tier1",

	minCredits = 55,
	maxCredits = 110,

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

ShipAgentTemplates:addShipAgentTemplate(bloodrazor_destroyer_tier1, "bloodrazor_destroyer_tier1")
