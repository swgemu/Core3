valarian_freighterlight_mining_tier1 = ShipAgent:new {
	template = "freighterlight_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_valarian_tier1",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "valarian",
	appearance = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(valarian_freighterlight_mining_tier1, "valarian_freighterlight_mining_tier1")
