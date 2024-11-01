nebula_assassin_fighter_tier4 = ShipAgent:new {
	template = "blacksun_light_s01_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 53,
	color2 = 3,
	texture = 4,
	appearance = "nebula_assassin",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_assassin_fighter_tier4, "nebula_assassin_fighter_tier4")
