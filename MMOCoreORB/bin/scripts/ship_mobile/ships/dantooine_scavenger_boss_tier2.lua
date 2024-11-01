dantooine_scavenger_boss_tier2 = ShipAgent:new {
	template = "hutt_heavy_s01_tier3",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "bomber",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 170,
	maxCredits = 382,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "blacksun", "nym"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 3,
	color2 = 28,
	texture = 6,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_scavenger_boss_tier2, "dantooine_scavenger_boss_tier2")
