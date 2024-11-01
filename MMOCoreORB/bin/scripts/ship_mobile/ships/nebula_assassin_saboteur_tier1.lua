nebula_assassin_saboteur_tier1 = ShipAgent:new {
	template = "blacksun_medium_s03_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "bomber",

	experience = 110,

	lootChance = 0.187,
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

ShipAgentTemplates:addShipAgentTemplate(nebula_assassin_saboteur_tier1, "nebula_assassin_saboteur_tier1")
