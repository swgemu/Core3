blacksun_krayt_bane_tier3 = ShipAgent:new {
	template = "blacksun_heavy_s04_tier3",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "fighter",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_blacksun_tier5",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 1,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 7,
	color2 = 3,
	texture = 4,
	appearance = "blacksun",
}

ShipAgentTemplates:addShipAgentTemplate(blacksun_krayt_bane_tier3, "blacksun_krayt_bane_tier3")
