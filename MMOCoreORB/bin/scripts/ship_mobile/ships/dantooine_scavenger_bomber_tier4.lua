dantooine_scavenger_bomber_tier4 = ShipAgent:new {
	template = "ywing_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "bomber",

	experience = 3440.64,

	lootChance = 0.147,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 240,
	maxCredits = 550,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "blacksun", "nym"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},
	color2 = 16,
	texture = 1,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_scavenger_bomber_tier4, "dantooine_scavenger_bomber_tier4")
