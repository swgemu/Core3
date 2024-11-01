deserted_freighter_tier4 = ShipAgent:new {
	template = "freightermedium_tier4",
	pilotTemplate = "heavy_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier1",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "civilian",

	color1 = 5,
	color2 = 42,
	texture = 1,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(deserted_freighter_tier4, "deserted_freighter_tier4")
