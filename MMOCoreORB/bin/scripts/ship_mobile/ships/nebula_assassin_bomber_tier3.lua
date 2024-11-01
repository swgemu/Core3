nebula_assassin_bomber_tier3 = ShipAgent:new {
	template = "blacksun_heavy_s04_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "bomber",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 160,
	maxCredits = 353,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 53,
	color2 = 3,
	texture = 4,
	appearance = "nebula_assassin",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_assassin_bomber_tier3, "nebula_assassin_bomber_tier3")
