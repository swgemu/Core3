blacksun_bomber_s03_tier1 = ShipAgent:new {
	template = "blacksun_heavy_s03_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "bomber",

	experience = 120,

	lootChance = 0.204,
	lootRolls = 1,
	lootTable = "space_blacksun_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 1,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 7,
	color2 = 3,
	texture = 4,
	appearance = "blacksun",

	tauntType = "blacksun",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacksun_bomber_s03_tier1, "blacksun_bomber_s03_tier1")
