dantooine_scavenger_boss_tier5 = ShipAgent:new {
	template = "hutt_heavy_s01_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "bomber",

	experience = 8724.15,

	lootChance = 0.169,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 465,
	maxCredits = 925,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_scavenger_boss_tier5, "dantooine_scavenger_boss_tier5")
