slave_trader_trader_tier5 = ShipAgent:new {
	template = "hutt_light_s01_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6039.8,

	lootChance = 0.117,
	lootRolls = 1,
	lootTable = "space_hutt_tier5",

	minCredits = 350,
	maxCredits = 750,

	aggressive = 1,

	spaceFaction = "civilian",
	alliedFactions = {"hutt", "imperial", "civilian"},
	enemyFactions = {"rebel", "merchant", "pirate"},

	color1 = 7,
	color2 = 59,
	texture = 0,
}

ShipAgentTemplates:addShipAgentTemplate(slave_trader_trader_tier5, "slave_trader_trader_tier5")
