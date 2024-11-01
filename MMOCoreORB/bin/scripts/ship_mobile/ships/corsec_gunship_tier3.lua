corsec_gunship_tier3 = ShipAgent:new {
	template = "imperial_gunboat_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "bomber",

	experience = 6400,

	lootChance = 0.75,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 350,
	maxCredits = 750,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_gunship_tier3, "corsec_gunship_tier3")
