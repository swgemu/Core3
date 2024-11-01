massassi_command_ship_tier2 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier3",
	pilotTemplate = "slow_tier2",
	shipType = "fighter",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 170,
	maxCredits = 368,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 37,
	color2 = 50,
	texture = 4,
	formationLocation = 1,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(massassi_command_ship_tier2, "massassi_command_ship_tier2")
