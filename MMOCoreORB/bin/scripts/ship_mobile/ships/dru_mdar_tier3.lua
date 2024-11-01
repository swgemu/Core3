dru_mdar_tier3 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "fighter",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 160,
	maxCredits = 353,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"rsf"},

	color1 = 30,
	color2 = 24,
	texture = 1,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(dru_mdar_tier3, "dru_mdar_tier3")
