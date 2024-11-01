nebula_assassin_bomber_tier5 = ShipAgent:new {
	template = "blacksun_heavy_s04_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "bomber",

	experience = 8053.06,

	lootChance = 0.156,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 53,
	color2 = 3,
	texture = 4,
	appearance = "nebula_assassin",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_assassin_bomber_tier5, "nebula_assassin_bomber_tier5")
