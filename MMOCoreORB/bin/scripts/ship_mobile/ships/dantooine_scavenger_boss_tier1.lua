dantooine_scavenger_boss_tier1 = ShipAgent:new {
	template = "hutt_heavy_s01_tier2",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "bomber",

	experience = 520,

	lootChance = 0.208,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 80,
	maxCredits = 200,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_scavenger_boss_tier1, "dantooine_scavenger_boss_tier1")
