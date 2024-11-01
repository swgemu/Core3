illegal_delivery_shuttle_tier2 = ShipAgent:new {
	template = "transport_science_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier3",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "merchant",
	appearance = "hutt",
}

ShipAgentTemplates:addShipAgentTemplate(illegal_delivery_shuttle_tier2, "illegal_delivery_shuttle_tier2")
