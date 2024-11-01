erkon_the_vile = ShipAgent:new {
	template = "hutt_medium_s02_tier3",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "bomber",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 5,
	color2 = 3,
	texture = 2,
	appearance = "corsair",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(erkon_the_vile, "erkon_the_vile")
