spice_pirate_transport_tier5 = ShipAgent:new {
	template = "freightermedium_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier5",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "pirate",
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(spice_pirate_transport_tier5, "spice_pirate_transport_tier5")
