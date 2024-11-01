debris_smuggler_bomber_tier3 = ShipAgent:new {
	template = "ywing_tier3",
	pilotTemplate = "bomber_tier3",
	shipType = "bomber",

	experience = 1344,

	lootChance = 0.1575,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 150,
	maxCredits = 309,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},
	color2 = 52,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_bomber_tier3, "debris_smuggler_bomber_tier3")
