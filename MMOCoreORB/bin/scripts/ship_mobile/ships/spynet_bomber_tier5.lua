spynet_bomber_tier5 = ShipAgent:new {
	template = "ywing_tier5",
	pilotTemplate = "bomber_tier5",
	shipType = "bomber",

	experience = 7046.43,

	lootChance = 0.1365,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 425,
	maxCredits = 850,

	aggressive = 0,

	spaceFaction = "spynet",
	alliedFactions = {"spynet"},
	enemyFactions = {"imperial", "pirate"},
	color2 = 3,
	appearance = "bothan_spynet_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(spynet_bomber_tier5, "spynet_bomber_tier5")
