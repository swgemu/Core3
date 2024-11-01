corsec_corona_tier1 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "bomber",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_corona_tier1, "corsec_corona_tier1")
