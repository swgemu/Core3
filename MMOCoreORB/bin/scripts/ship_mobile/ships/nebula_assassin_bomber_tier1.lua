nebula_assassin_bomber_tier1 = ShipAgent:new {
	template = "blacksun_heavy_s04_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "bomber",

	experience = 120,

	lootChance = 0.204,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 53,
	color2 = 3,
	texture = 4,
	appearance = "nebula_assassin",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_assassin_bomber_tier1, "nebula_assassin_bomber_tier1")
