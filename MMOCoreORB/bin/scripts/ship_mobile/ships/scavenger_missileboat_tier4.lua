scavenger_missileboat_tier4 = ShipAgent:new {
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
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant"},
	color2 = 18,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(scavenger_missileboat_tier4, "scavenger_missileboat_tier4")
