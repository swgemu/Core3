nebula_assassin_bomber_tier2 = ShipAgent:new {
	template = "blacksun_heavy_s04_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "bomber",

	experience = 480,

	lootChance = 0.192,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 53,
	color2 = 3,
	texture = 4,
	appearance = "nebula_assassin",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_assassin_bomber_tier2, "nebula_assassin_bomber_tier2")
