bloodrazor_destroyer_tier4 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "bomber",

	experience = 3932.16,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_blacksun_tier4",

	minCredits = 275,
	maxCredits = 600,

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

ShipAgentTemplates:addShipAgentTemplate(bloodrazor_destroyer_tier4, "bloodrazor_destroyer_tier4")
