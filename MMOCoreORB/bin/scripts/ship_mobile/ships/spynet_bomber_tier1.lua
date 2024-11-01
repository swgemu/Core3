spynet_bomber_tier1 = ShipAgent:new {
	template = "ywing_tier1",
	pilotTemplate = "bomber_tier1",
	shipType = "bomber",

	experience = 105,

	lootChance = 0.1785,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 51,
	maxCredits = 103,

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

ShipAgentTemplates:addShipAgentTemplate(spynet_bomber_tier1, "spynet_bomber_tier1")
