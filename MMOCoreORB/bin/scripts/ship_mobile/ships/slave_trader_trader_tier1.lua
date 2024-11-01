slave_trader_trader_tier1 = ShipAgent:new {
	template = "hutt_light_s01_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 90,

	lootChance = 0.153,
	lootRolls = 1,
	lootTable = "space_hutt_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "civilian",
	alliedFactions = {"hutt", "imperial", "civilian"},
	enemyFactions = {"rebel", "merchant", "pirate"},

	color1 = 7,
	color2 = 59,
	texture = 0,
}

ShipAgentTemplates:addShipAgentTemplate(slave_trader_trader_tier1, "slave_trader_trader_tier1")
