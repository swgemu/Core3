debris_smuggler_fighter_tier4 = ShipAgent:new {
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

	color1 = 6,
	color2 = 40,
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_fighter_tier4, "debris_smuggler_fighter_tier4")
