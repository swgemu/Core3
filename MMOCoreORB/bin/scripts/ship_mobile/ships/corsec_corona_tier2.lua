corsec_corona_tier2 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "bomber",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 170,
	maxCredits = 368,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_corona_tier2, "corsec_corona_tier2")
