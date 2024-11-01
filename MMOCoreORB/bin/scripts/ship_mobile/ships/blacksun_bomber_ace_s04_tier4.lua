blacksun_bomber_ace_s04_tier4 = ShipAgent:new {
	template = "blacksun_heavy_s04_tier4",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "bomber",

	experience = 3932.16,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_blacksun_tier5",

	minCredits = 275,
	maxCredits = 600,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_bomber_ace_s04_tier4, "blacksun_bomber_ace_s04_tier4")
