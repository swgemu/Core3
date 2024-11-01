freighterlight_mining_nym = ShipAgent:new {
	template = "freighterlight_tier3",
	pilotTemplate = "heavy_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_nym_tier1",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "nym",
	appearance = "nym",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freighterlight_mining_nym, "freighterlight_mining_nym")
