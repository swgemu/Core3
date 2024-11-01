bloodrazor_berzerker_tier3 = ShipAgent:new {
	template = "blacksun_medium_s01_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_blacksun_tier3",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun", "nym"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec", "pirate"},

	color1 = 2,
	color2 = 4,
	texture = 5,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(bloodrazor_berzerker_tier3, "bloodrazor_berzerker_tier3")
