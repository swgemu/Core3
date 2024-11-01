nebula_scientist_analyst_tier4 = ShipAgent:new {
	template = "ywing_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "fighter",

	experience = 3440.64,

	lootChance = 0.147,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 240,
	maxCredits = 550,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},
	color2 = 12,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_analyst_tier4, "nebula_scientist_analyst_tier4")
