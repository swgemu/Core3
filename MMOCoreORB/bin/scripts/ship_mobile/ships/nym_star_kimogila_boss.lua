nym_star_kimogila_boss = ShipAgent:new {
	template = "rebel_gunboat_tier3",
	pilotTemplate = "heavy_tier4",
	shipType = "bomber",

	experience = 5120,

	lootChance = 0.6,
	lootRolls = 1,
	lootTable = "space_nym_tier4",

	minCredits = 94,
	maxCredits = 700,

	aggressive = 0,

	spaceFaction = "nym",
	alliedFactions = {"rebel", "nym"},
	enemyFactions = {"imperial", "merchant", "corsair", "blacksun", "corsec", "rsf"},
	appearance = "nym",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_star_kimogila_boss, "nym_star_kimogila_boss")
