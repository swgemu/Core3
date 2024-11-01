vsin_starbomber_tier2 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "fighter",

	experience = 480,

	lootChance = 0.192,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt"},

	color1 = 5,
	color2 = 42,
	texture = 1,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(vsin_starbomber_tier2, "vsin_starbomber_tier2")
