nym_gunship_tier2 = ShipAgent:new {
	template = "rebel_gunboat_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "bomber",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_nym_tier2",

	minCredits = 170,
	maxCredits = 368,

	aggressive = 0,

	spaceFaction = "nym",
	alliedFactions = {"rebel", "nym"},
	enemyFactions = {"imperial", "merchant", "corsair", "blacksun", "corsec", "rsf"},
	appearance = "nym",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_gunship_tier2, "nym_gunship_tier2")
