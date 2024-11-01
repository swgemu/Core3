corsec_lancer_tier3 = ShipAgent:new {
	template = "hutt_heavy_s01_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "bomber",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 170,
	maxCredits = 382,

	aggressive = 0,

	spaceFaction = "corsec",
	alliedFactions = {"corsec", "civilian", "merchant"},
	enemyFactions = {"blacksun", "hutt", "pirate", "aynat", "borvo"},

	color1 = 44,
	color2 = 30,
	texture = 4,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(corsec_lancer_tier3, "corsec_lancer_tier3")
