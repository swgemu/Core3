blacksun_gunship_tier1 = ShipAgent:new {
	template = "rebel_gunboat_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "bomber",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_blacksun_tier1",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_gunship_tier1, "blacksun_gunship_tier1")
