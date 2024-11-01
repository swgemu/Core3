nebula_assassin_bomber = ShipAgent:new {
	template = "blacksun_heavy_s04_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "bomber",

	experience = 3932.16,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 275,
	maxCredits = 600,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},

	color1 = 53,
	color2 = 3,
	texture = 4,
	appearance = "nebula_assassin",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_assassin_bomber, "nebula_assassin_bomber")
