nym_blastboat_tier5 = ShipAgent:new {
	template = "hutt_heavy_s02_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "bomber",

	experience = 8724.15,

	lootChance = 0.169,
	lootRolls = 1,
	lootTable = "space_nym_tier5",

	minCredits = 465,
	maxCredits = 925,

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

ShipAgentTemplates:addShipAgentTemplate(nym_blastboat_tier5, "nym_blastboat_tier5")
