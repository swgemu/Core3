corsec_interdiction_craft_tier1 = ShipAgent:new {
	template = "firespray_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "fighter",

	experience = 130,

	lootChance = 0.221,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 55,
	maxCredits = 110,

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

ShipAgentTemplates:addShipAgentTemplate(corsec_interdiction_craft_tier1, "corsec_interdiction_craft_tier1")
