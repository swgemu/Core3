nym_blastboat_tier2 = ShipAgent:new {
	template = "hutt_heavy_s02_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "bomber",

	experience = 520,

	lootChance = 0.208,
	lootRolls = 1,
	lootTable = "space_nym_tier2",

	minCredits = 80,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "nym",
	alliedFactions = {"rebel", "nym"},
	enemyFactions = {"imperial", "merchant", "corsair", "blacksun", "corsec", "rsf", "pirate"},

	color1 = 36,
	color2 = 31,
	texture = 4,
	appearance = "nym",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_blastboat_tier2, "nym_blastboat_tier2")
