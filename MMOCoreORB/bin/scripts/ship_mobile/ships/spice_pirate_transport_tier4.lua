spice_pirate_transport_tier4 = ShipAgent:new {
	template = "freightermedium_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier4",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "pirate",
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(spice_pirate_transport_tier4, "spice_pirate_transport_tier4")
