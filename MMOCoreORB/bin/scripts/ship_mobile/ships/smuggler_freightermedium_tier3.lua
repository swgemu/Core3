smuggler_freightermedium_tier3 = ShipAgent:new {
	template = "freightermedium_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier3",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "smuggler",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(smuggler_freightermedium_tier3, "smuggler_freightermedium_tier3")
