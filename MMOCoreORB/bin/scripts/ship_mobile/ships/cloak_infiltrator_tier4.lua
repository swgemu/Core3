cloak_infiltrator_tier4 = ShipAgent:new {
	template = "awing_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 200,
	maxCredits = 500,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "corsec", "merchant", "civilian", "rsf"},

	color1 = 59,
	color2 = 59,
	texture = 5,
	formationLocation = 2,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(cloak_infiltrator_tier4, "cloak_infiltrator_tier4")
