corsec_gunship_tier1 = ShipAgent:new {
	template = "imperial_gunboat_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "bomber",

	experience = 500,

	lootChance = 0.85,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 80,
	maxCredits = 200,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_gunship_tier1, "corsec_gunship_tier1")
