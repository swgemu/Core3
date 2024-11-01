corsec_corona_tier5 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "bomber",

	experience = 26843.55,

	lootChance = 0.52,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 525,
	maxCredits = 1075,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_corona_tier5, "corsec_corona_tier5")
