smuggler_freighterheavy_tier4 = ShipAgent:new {
	template = "freighterheavy_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier4",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "smuggler",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(smuggler_freighterheavy_tier4, "smuggler_freighterheavy_tier4")
