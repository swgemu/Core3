valarian_freighterlight_mining_tier5 = ShipAgent:new {
	template = "freighterlight_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_valarian_tier5",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "valarian",
	appearance = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(valarian_freighterlight_mining_tier5, "valarian_freighterlight_mining_tier5")
