obsidian_torpedo_boss = ShipAgent:new {
	template = "hutt_heavy_s01_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "bomber",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 170,
	maxCredits = 382,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "rsf", "corsec"},

	color1 = 3,
	color2 = 3,
	formationLocation = 3,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(obsidian_torpedo_boss, "obsidian_torpedo_boss")
