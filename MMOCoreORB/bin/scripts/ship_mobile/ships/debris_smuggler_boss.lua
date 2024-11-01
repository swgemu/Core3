debris_smuggler_boss = ShipAgent:new {
	template = "ywing_tier4",
	pilotTemplate = "bomber_tier5",
	shipType = "bomber",

	experience = 3440.64,

	lootChance = 0.147,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 240,
	maxCredits = 550,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},
	color2 = 52,
}

ShipAgentTemplates:addShipAgentTemplate(debris_smuggler_boss, "debris_smuggler_boss")
