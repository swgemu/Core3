slave_trader_trader_tier3_dantooine = ShipAgent:new {
	template = "hutt_light_s01_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_story_dantooine_slave",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 1,

	spaceFaction = "civilian",
	alliedFactions = {"hutt", "imperial", "civilian"},
	enemyFactions = {"rebel", "merchant", "pirate"},

	color1 = 7,
	color2 = 59,
	texture = 0,
}

ShipAgentTemplates:addShipAgentTemplate(slave_trader_trader_tier3_dantooine, "slave_trader_trader_tier3_dantooine")
