nebula_scientist_bodyguard_hire = ShipAgent:new {
	template = "xwing_tier5",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "bomber",

	experience = 7381.98,

	lootChance = 0.143,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 455,
	maxCredits = 875,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 58,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_bodyguard_hire, "nebula_scientist_bodyguard_hire")
