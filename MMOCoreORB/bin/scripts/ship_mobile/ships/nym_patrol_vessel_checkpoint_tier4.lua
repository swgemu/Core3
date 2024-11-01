nym_patrol_vessel_checkpoint_tier4 = ShipAgent:new {
	template = "ykl37r_tier4",
	pilotTemplate = "heavy_tier3",
	shipType = "fighter",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_nym_tier3",

	minCredits = 400,
	maxCredits = 800,

	aggressive = 0,

	spaceFaction = "nym",
	alliedFactions = {"rebel", "nym"},
	enemyFactions = {"imperial", "merchant", "corsair", "blacksun", "corsec", "rsf"},

	color1 = 43,
	color2 = 47,
	texture = 5,
	appearance = "nym",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_patrol_vessel_checkpoint_tier4, "nym_patrol_vessel_checkpoint_tier4")
