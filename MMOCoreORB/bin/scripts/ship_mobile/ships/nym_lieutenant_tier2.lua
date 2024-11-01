nym_lieutenant_tier2 = ShipAgent:new {
	template = "hutt_medium_s01_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_nym_tier1",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 0,

	spaceFaction = "nym",
	alliedFactions = {"rebel", "nym"},
	enemyFactions = {"imperial", "merchant", "corsair", "blacksun", "corsec", "rsf"},

	color1 = 36,
	color2 = 31,
	texture = 4,
	questLoot = "imperial_ss_1",
	appearance = "nym",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_lieutenant_tier2, "nym_lieutenant_tier2")
