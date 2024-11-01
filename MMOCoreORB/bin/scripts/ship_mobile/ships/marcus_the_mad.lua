marcus_the_mad = ShipAgent:new {
	template = "ywing_tier2",
	pilotTemplate = "bomber_tier3",
	shipType = "fighter",

	experience = 420,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"rebel", "merchant"},
	color2 = 9,
	texture = 1,
	questLoot = "robot_sidequest",
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(marcus_the_mad, "marcus_the_mad")
