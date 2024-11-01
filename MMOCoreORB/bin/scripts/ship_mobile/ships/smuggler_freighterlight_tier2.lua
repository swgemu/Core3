smuggler_freighterlight_tier2 = ShipAgent:new {
	template = "freighterlight_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "smuggler",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(smuggler_freighterlight_tier2, "smuggler_freighterlight_tier2")
