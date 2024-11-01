rsf_prison_ship_tier2 = ShipAgent:new {
	template = "freighterheavy_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_merchant_tier1",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "rsf",
	questLoot = "general_cargo",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rsf_prison_ship_tier2, "rsf_prison_ship_tier2")
