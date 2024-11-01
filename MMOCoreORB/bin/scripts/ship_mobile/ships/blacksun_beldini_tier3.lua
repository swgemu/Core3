blacksun_beldini_tier3 = ShipAgent:new {
	template = "blacksun_light_s04_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_blacksun_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 1,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 42,
	color2 = 55,
	texture = 1,
	appearance = "blacksun",
}

ShipAgentTemplates:addShipAgentTemplate(blacksun_beldini_tier3, "blacksun_beldini_tier3")
