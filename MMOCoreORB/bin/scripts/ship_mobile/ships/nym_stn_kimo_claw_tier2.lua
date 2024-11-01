nym_stn_kimo_claw_tier2 = ShipAgent:new {
	template = "yt1300_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "fighter",

	experience = 800,

	lootChance = 0.32,
	lootRolls = 1,
	lootTable = "space_nym_tier2",

	minCredits = 95,
	maxCredits = 240,

	aggressive = 0,

	spaceFaction = "nym",
	alliedFactions = {"rebel", "corsec", "hut", "valarian"},
	enemyFactions = {"imperial", "rsf"},
	color2 = 6,
	texture = 1,
	appearance = "nym",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_stn_kimo_claw_tier2, "nym_stn_kimo_claw_tier2")
