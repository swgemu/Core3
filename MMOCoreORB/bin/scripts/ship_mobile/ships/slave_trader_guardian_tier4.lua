slave_trader_guardian_tier4 = ShipAgent:new {
	template = "hutt_medium_s02_tier4",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_hutt_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 1,

	spaceFaction = "civilian",
	alliedFactions = {"hutt", "imperial", "civilian"},
	enemyFactions = {"rebel", "merchant", "pirate"},

	color1 = 7,
	color2 = 59,
	texture = 0,
}

ShipAgentTemplates:addShipAgentTemplate(slave_trader_guardian_tier4, "slave_trader_guardian_tier4")
