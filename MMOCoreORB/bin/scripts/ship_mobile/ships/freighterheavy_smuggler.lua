freighterheavy_smuggler = ShipAgent:new {
	template = "freighterheavy_tier3",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier1",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "civilian",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freighterheavy_smuggler, "freighterheavy_smuggler")
