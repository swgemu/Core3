corsec_gunship_tier5 = ShipAgent:new {
	template = "imperial_gunboat_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "bomber",

	experience = 33554.43,

	lootChance = 0.65,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 617,
	maxCredits = 1100,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_gunship_tier5, "corsec_gunship_tier5")
