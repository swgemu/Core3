blacksun_gunship_tier2 = ShipAgent:new {
	template = "rebel_gunboat_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "bomber",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_blacksun_tier2",

	minCredits = 170,
	maxCredits = 368,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_gunship_tier2, "blacksun_gunship_tier2")
