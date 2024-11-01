blacksun_ace_s04_tier2 = ShipAgent:new {
	template = "blacksun_light_s04_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_blacksun_tier3",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 42,
	color2 = 55,
	texture = 1,
	appearance = "blacksun",

	tauntType = "blacksun_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacksun_ace_s04_tier2, "blacksun_ace_s04_tier2")
