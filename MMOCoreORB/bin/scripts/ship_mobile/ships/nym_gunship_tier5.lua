nym_gunship_tier5 = ShipAgent:new {
	template = "rebel_gunboat_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "bomber",

	experience = 26843.55,

	lootChance = 0.52,
	lootRolls = 1,
	lootTable = "space_nym_tier5",

	minCredits = 525,
	maxCredits = 1075,

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

ShipAgentTemplates:addShipAgentTemplate(nym_gunship_tier5, "nym_gunship_tier5")
