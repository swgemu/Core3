debris_smuggler_fighter_tier1 = ShipAgent:new {
	template = "z95_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 6,
	color2 = 40,
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_fighter_tier1, "debris_smuggler_fighter_tier1")
