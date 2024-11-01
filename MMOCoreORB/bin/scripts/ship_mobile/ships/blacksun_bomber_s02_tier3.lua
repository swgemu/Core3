blacksun_bomber_s02_tier3 = ShipAgent:new {
	template = "blacksun_heavy_s02_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "bomber",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_blacksun_tier3",

	minCredits = 160,
	maxCredits = 353,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_bomber_s02_tier3, "blacksun_bomber_s02_tier3")
