corsec_interdiction_craft_tier2 = ShipAgent:new {
	template = "firespray_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "fighter",

	experience = 520,

	lootChance = 0.208,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 80,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "corsec",
	alliedFactions = {"corsec", "civilian", "merchant"},
	enemyFactions = {"blacksun", "hutt", "pirate", "aynat", "borvo"},

	color1 = 44,
	color2 = 37,
	texture = 2,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(corsec_interdiction_craft_tier2, "corsec_interdiction_craft_tier2")
