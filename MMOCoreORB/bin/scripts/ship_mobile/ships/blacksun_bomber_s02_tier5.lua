blacksun_bomber_s02_tier5 = ShipAgent:new {
	template = "blacksun_heavy_s02_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "bomber",

	experience = 8053.06,

	lootChance = 0.156,
	lootRolls = 1,
	lootTable = "space_blacksun_tier5",

	minCredits = 465,
	maxCredits = 900,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_bomber_s02_tier5, "blacksun_bomber_s02_tier5")
