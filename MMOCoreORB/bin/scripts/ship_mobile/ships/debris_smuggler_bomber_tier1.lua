debris_smuggler_bomber_tier1 = ShipAgent:new {
	template = "ywing_tier1",
	pilotTemplate = "bomber_tier1",
	shipType = "bomber",

	experience = 105,

	lootChance = 0.1785,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},
	color2 = 52,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_bomber_tier1, "debris_smuggler_bomber_tier1")
