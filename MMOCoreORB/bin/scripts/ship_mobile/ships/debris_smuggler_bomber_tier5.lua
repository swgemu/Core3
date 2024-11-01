debris_smuggler_bomber_tier5 = ShipAgent:new {
	template = "ywing_tier5",
	pilotTemplate = "bomber_tier5",
	shipType = "bomber",

	experience = 7046.43,

	lootChance = 0.1365,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 425,
	maxCredits = 850,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},
	color2 = 52,
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_bomber_tier5, "debris_smuggler_bomber_tier5")
