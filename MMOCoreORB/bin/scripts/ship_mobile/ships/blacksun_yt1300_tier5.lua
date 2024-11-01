blacksun_yt1300_tier5 = ShipAgent:new {
	template = "yt1300_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "fighter",

	experience = 13421.77,

	lootChance = 0.26,
	lootRolls = 1,
	lootTable = "space_blacksun_tier5",

	minCredits = 465,
	maxCredits = 975,

	aggressive = 0,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 51,
	color2 = 6,
	texture = 2,
	appearance = "blacksun",

	tauntType = "blacksun_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacksun_yt1300_tier5, "blacksun_yt1300_tier5")
