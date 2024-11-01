debris_smuggler_bomber_tier2 = ShipAgent:new {
	template = "ywing_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "bomber",

	experience = 420,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},
	color2 = 52,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_bomber_tier2, "debris_smuggler_bomber_tier2")
