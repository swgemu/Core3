nebula_scientist_analyst_tier3 = ShipAgent:new {
	template = "ywing_tier3",
	pilotTemplate = "bomber_tier3",
	shipType = "fighter",

	experience = 1344,

	lootChance = 0.1575,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 150,
	maxCredits = 309,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},
	color2 = 12,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_analyst_tier3, "nebula_scientist_analyst_tier3")
