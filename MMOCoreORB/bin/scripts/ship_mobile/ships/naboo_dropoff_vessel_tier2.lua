naboo_dropoff_vessel_tier2 = ShipAgent:new {
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
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(naboo_dropoff_vessel_tier2, "naboo_dropoff_vessel_tier2")
