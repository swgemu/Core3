nym_gunship_tier1 = ShipAgent:new {
	template = "rebel_gunboat_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "bomber",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_nym_tier1",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(nym_gunship_tier1, "nym_gunship_tier1")
