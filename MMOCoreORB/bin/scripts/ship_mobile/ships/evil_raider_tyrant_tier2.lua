evil_raider_tyrant_tier2 = ShipAgent:new {
	template = "hutt_heavy_s01_tier2",
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

ShipAgentTemplates:addShipAgentTemplate(evil_raider_tyrant_tier2, "evil_raider_tyrant_tier2")
