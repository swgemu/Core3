debris_smuggler_collector_tier1 = ShipAgent:new {
	template = "freighterheavy_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier1",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "pirate",
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_collector_tier1, "debris_smuggler_collector_tier1")
