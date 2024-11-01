spynet_bomber_tier3 = ShipAgent:new {
	template = "ywing_tier3",
	pilotTemplate = "bomber_tier3",
	shipType = "bomber",

	experience = 1344,

	lootChance = 0.1575,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 150,
	maxCredits = 309,

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

ShipAgentTemplates:addShipAgentTemplate(spynet_bomber_tier3, "spynet_bomber_tier3")
