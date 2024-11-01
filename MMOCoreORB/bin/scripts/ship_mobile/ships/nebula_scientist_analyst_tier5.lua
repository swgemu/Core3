nebula_scientist_analyst_tier5 = ShipAgent:new {
	template = "ywing_tier5",
	pilotTemplate = "bomber_tier5",
	shipType = "fighter",

	experience = 7046.43,

	lootChance = 0.1365,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 425,
	maxCredits = 850,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},
	color2 = 12,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_analyst_tier5, "nebula_scientist_analyst_tier5")
