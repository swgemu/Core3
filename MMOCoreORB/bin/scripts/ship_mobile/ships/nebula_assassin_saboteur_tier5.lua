nebula_assassin_saboteur_tier5 = ShipAgent:new {
	template = "blacksun_medium_s03_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "bomber",

	experience = 7381.98,

	lootChance = 0.143,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 455,
	maxCredits = 875,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 53,
	color2 = 3,
	texture = 4,
	appearance = "nebula_assassin",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_assassin_saboteur_tier5, "nebula_assassin_saboteur_tier5")
