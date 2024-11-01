dantooine_warrens_boss = ShipAgent:new {
	template = "tiebomber_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "bomber",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 260,
	maxCredits = 575,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_warrens_boss, "dantooine_warrens_boss")
