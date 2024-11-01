debris_smuggler_transport_tier3 = ShipAgent:new {
	template = "hutt_transport_tier3",
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
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_transport_tier3, "debris_smuggler_transport_tier3")
