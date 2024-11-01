corsec_corona_tier4 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "bomber",

	experience = 13107.2,

	lootChance = 0.56,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 465,
	maxCredits = 950,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_corona_tier4, "corsec_corona_tier4")
