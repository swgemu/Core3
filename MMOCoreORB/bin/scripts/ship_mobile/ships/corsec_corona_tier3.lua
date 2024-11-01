corsec_corona_tier3 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "bomber",

	experience = 5120,

	lootChance = 0.6,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 94,
	maxCredits = 700,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_corona_tier3, "corsec_corona_tier3")
