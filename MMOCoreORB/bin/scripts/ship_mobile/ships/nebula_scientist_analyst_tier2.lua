nebula_scientist_analyst_tier2 = ShipAgent:new {
	template = "ywing_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "fighter",

	experience = 420,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},
	color2 = 12,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_analyst_tier2, "nebula_scientist_analyst_tier2")
