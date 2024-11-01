blacksun_starkiller_leader = ShipAgent:new {
	template = "blacksun_heavy_s04_tier2",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "bomber",

	experience = 480,

	lootChance = 0.192,
	lootRolls = 1,
	lootTable = "space_blacksun_tier3",

	minCredits = 75,
	maxCredits = 160,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_starkiller_leader, "blacksun_starkiller_leader")
