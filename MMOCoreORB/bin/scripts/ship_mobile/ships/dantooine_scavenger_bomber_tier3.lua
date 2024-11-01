dantooine_scavenger_bomber_tier3 = ShipAgent:new {
	template = "ywing_tier3",
	pilotTemplate = "bomber_tier3",
	shipType = "bomber",

	experience = 1344,

	lootChance = 0.1575,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 150,
	maxCredits = 309,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_scavenger_bomber_tier3, "dantooine_scavenger_bomber_tier3")
