massassi_damaged_fighter_tier2 = ShipAgent:new {
	template = "firespray_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "fighter",

	experience = 520,

	lootChance = 0.208,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 80,
	maxCredits = 200,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 37,
	color2 = 50,
	texture = 4,
	questLoot = "massassi_manifesto",
	formationLocation = 3,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(massassi_damaged_fighter_tier2, "massassi_damaged_fighter_tier2")
