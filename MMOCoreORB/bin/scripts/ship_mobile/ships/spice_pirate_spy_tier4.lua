spice_pirate_spy_tier4 = ShipAgent:new {
	template = "z95_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 0,
	color2 = 31,
	texture = 0,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(spice_pirate_spy_tier4, "spice_pirate_spy_tier4")
