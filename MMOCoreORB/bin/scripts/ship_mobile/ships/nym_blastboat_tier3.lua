nym_blastboat_tier3 = ShipAgent:new {
	template = "hutt_heavy_s02_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "bomber",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_nym_tier3",

	minCredits = 170,
	maxCredits = 382,

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

ShipAgentTemplates:addShipAgentTemplate(nym_blastboat_tier3, "nym_blastboat_tier3")
