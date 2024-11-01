spice_pirate_boss = ShipAgent:new {
	template = "z95_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 0,
	color2 = 31,
	texture = 0,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(spice_pirate_boss, "spice_pirate_boss")
