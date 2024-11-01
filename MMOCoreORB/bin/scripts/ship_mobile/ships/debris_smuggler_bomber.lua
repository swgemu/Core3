debris_smuggler_bomber = ShipAgent:new {
	template = "z95_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "bomber",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 6,
	color2 = 40,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_bomber, "debris_smuggler_bomber")
