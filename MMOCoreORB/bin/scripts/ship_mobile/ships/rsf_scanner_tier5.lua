rsf_scanner_tier5 = ShipAgent:new {
	template = "transport_science_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier5",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "rsf",
	formationLocation = 3,
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rsf_scanner_tier5, "rsf_scanner_tier5")
