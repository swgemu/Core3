nebula_scientist_bodyguard_tier2 = ShipAgent:new {
	template = "xwing_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "bomber",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 58,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_bodyguard_tier2, "nebula_scientist_bodyguard_tier2")
