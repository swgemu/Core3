massassi_light_fighter_tier3 = ShipAgent:new {
	template = "hutt_light_s02_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 80,
	maxCredits = 200,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 37,
	color2 = 50,
	texture = 4,
	formationLocation = 3,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(massassi_light_fighter_tier3, "massassi_light_fighter_tier3")
