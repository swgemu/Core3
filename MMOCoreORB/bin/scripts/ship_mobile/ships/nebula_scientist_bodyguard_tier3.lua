nebula_scientist_bodyguard_tier3 = ShipAgent:new {
	template = "xwing_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "bomber",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 58,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_bodyguard_tier3, "nebula_scientist_bodyguard_tier3")
