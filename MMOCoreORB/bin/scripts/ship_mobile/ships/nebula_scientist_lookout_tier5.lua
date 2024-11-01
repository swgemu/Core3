nebula_scientist_lookout_tier5 = ShipAgent:new {
	template = "z95_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 58,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_lookout_tier5, "nebula_scientist_lookout_tier5")
