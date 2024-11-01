spice_pirate_transport_tier1 = ShipAgent:new {
	template = "freightermedium_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier1",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "pirate",
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(spice_pirate_transport_tier1, "spice_pirate_transport_tier1")
