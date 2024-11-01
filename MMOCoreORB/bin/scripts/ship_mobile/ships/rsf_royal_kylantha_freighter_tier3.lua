rsf_royal_kylantha_freighter_tier3 = ShipAgent:new {
	template = "transport_science_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_merchant_tier1",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "rsf",
	questLoot = "general_cargo",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rsf_royal_kylantha_freighter_tier3, "rsf_royal_kylantha_freighter_tier3")
