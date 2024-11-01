nebula_assassin_saboteur_tier3 = ShipAgent:new {
	template = "blacksun_medium_s03_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "bomber",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 53,
	color2 = 3,
	texture = 4,
	appearance = "nebula_assassin",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_assassin_saboteur_tier3, "nebula_assassin_saboteur_tier3")
