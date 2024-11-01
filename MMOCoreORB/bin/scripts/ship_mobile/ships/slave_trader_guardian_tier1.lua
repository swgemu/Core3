slave_trader_guardian_tier1 = ShipAgent:new {
	template = "hutt_medium_s02_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
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

ShipAgentTemplates:addShipAgentTemplate(slave_trader_guardian_tier1, "slave_trader_guardian_tier1")
