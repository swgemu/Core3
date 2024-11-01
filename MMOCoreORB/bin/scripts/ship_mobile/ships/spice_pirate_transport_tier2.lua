spice_pirate_transport_tier2 = ShipAgent:new {
	template = "freightermedium_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "pirate",
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(spice_pirate_transport_tier2, "spice_pirate_transport_tier2")
