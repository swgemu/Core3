blacksun_gunship_tier5 = ShipAgent:new {
	template = "rebel_gunboat_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "bomber",

	experience = 26843.55,

	lootChance = 0.52,
	lootRolls = 1,
	lootTable = "space_blacksun_tier5",

	minCredits = 525,
	maxCredits = 1075,

	aggressive = 1,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},
	appearance = "blacksun",

	tauntType = "blacksun",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacksun_gunship_tier5, "blacksun_gunship_tier5")
