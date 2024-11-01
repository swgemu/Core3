evil_raider_tyrant_tier4 = ShipAgent:new {
	template = "hutt_heavy_s01_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "fighter",

	experience = 4259.84,

	lootChance = 0.182,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 280,
	maxCredits = 650,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "rsf", "corsec"},

	color1 = 23,
	color2 = 56,
	texture = 3,
	questLoot = "stolen_data",
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(evil_raider_tyrant_tier4, "evil_raider_tyrant_tier4")
