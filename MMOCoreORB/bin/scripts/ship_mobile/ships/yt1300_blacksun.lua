yt1300_blacksun = ShipAgent:new {
	template = "yt1300_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "fighter",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_blacksun_tier1",

	minCredits = 60,
	maxCredits = 120,

	aggressive = 0,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "nym"},

	color1 = 8,
	color2 = 48,
	texture = 1,
	appearance = "blacksun",

	tauntType = "blacksun_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(yt1300_blacksun, "yt1300_blacksun")
