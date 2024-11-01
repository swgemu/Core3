nebula_scientist_bodyguard_tier4 = ShipAgent:new {
	template = "xwing_tier4",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "bomber",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 260,
	maxCredits = 575,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 58,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_bodyguard_tier4, "nebula_scientist_bodyguard_tier4")
