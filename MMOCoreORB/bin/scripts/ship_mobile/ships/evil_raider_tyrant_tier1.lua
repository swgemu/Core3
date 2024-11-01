evil_raider_tyrant_tier1 = ShipAgent:new {
	template = "hutt_heavy_s01_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "fighter",

	experience = 130,

	lootChance = 0.221,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 55,
	maxCredits = 110,

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

ShipAgentTemplates:addShipAgentTemplate(evil_raider_tyrant_tier1, "evil_raider_tyrant_tier1")
