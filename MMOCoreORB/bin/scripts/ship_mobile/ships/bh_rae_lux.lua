bh_rae_lux = ShipAgent:new {
	template = "ywing_tier1",
	pilotTemplate = "bomber_tier1",
	shipType = "fighter",

	experience = 105,

	lootChance = 0.1785,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant"},

	color1 = 0,
	color2 = 20,
	texture = 1,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(bh_rae_lux, "bh_rae_lux")
