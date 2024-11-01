corsec_interceptor_tier5 = ShipAgent:new {
	template = "awing_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6039.8,

	lootChance = 0.117,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 350,
	maxCredits = 750,

	aggressive = 0,

	spaceFaction = "corsec",
	alliedFactions = {"corsec", "civilian", "merchant"},
	enemyFactions = {"blacksun", "hutt", "pirate", "aynat", "borvo"},

	color1 = 22,
	color2 = 22,
	texture = 2,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(corsec_interceptor_tier5, "corsec_interceptor_tier5")
