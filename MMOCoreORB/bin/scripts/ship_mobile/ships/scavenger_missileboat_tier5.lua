scavenger_missileboat_tier5 = ShipAgent:new {
	template = "ywing_tier5",
	pilotTemplate = "bomber_tier5",
	shipType = "bomber",

	experience = 7046.43,

	lootChance = 0.1365,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 425,
	maxCredits = 850,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant"},
	color2 = 18,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(scavenger_missileboat_tier5, "scavenger_missileboat_tier5")
