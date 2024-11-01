nebula_scientist_bodyguard_tier1 = ShipAgent:new {
	template = "xwing_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "bomber",

	experience = 110,

	lootChance = 0.187,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 58,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_bodyguard_tier1, "nebula_scientist_bodyguard_tier1")
