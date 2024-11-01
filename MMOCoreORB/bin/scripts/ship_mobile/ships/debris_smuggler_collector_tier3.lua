debris_smuggler_collector_tier3 = ShipAgent:new {
	template = "freighterheavy_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier3",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "pirate",
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_collector_tier3, "debris_smuggler_collector_tier3")
