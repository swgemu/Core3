nebula_scientist_analyst_tier1 = ShipAgent:new {
	template = "ywing_tier1",
	pilotTemplate = "bomber_tier1",
	shipType = "fighter",

	experience = 105,

	lootChance = 0.1785,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},
	color2 = 12,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_analyst_tier1, "nebula_scientist_analyst_tier1")
