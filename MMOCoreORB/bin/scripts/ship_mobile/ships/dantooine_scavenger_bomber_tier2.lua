dantooine_scavenger_bomber_tier2 = ShipAgent:new {
	template = "ywing_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "bomber",

	experience = 420,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_scavenger_bomber_tier2, "dantooine_scavenger_bomber_tier2")
