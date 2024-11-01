corsec_gunship_tier4 = ShipAgent:new {
	template = "imperial_gunboat_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "bomber",

	experience = 16384,

	lootChance = 0.7,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 500,
	maxCredits = 1000,

	aggressive = 0,

	spaceFaction = "corsec",
	alliedFactions = {"corsec", "civilian", "merchant"},
	enemyFactions = {"blacksun", "hutt", "pirate", "aynat", "borvo"},
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(corsec_gunship_tier4, "corsec_gunship_tier4")
