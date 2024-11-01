corsec_gunship_tier2 = ShipAgent:new {
	template = "imperial_gunboat_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "bomber",

	experience = 2000,

	lootChance = 0.8,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 180,
	maxCredits = 460,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_gunship_tier2, "corsec_gunship_tier2")
