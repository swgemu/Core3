spice_pirate_transport_tier3 = ShipAgent:new {
	template = "freightermedium_tier3",
	pilotTemplate = "heavy_tier3",
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

ShipAgentTemplates:addShipAgentTemplate(spice_pirate_transport_tier3, "spice_pirate_transport_tier3")
