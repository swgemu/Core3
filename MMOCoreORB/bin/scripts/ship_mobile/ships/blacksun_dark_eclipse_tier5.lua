blacksun_dark_eclipse_tier5 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "capital",

	experience = 26843.55,

	lootChance = 0.52,
	lootRolls = 1,
	lootTable = "space_blacksun_tier5",

	minCredits = 617,
	maxCredits = 1100,

	aggressive = 1,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},
	appearance = "blacksun",

	tauntType = "blacksun",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacksun_dark_eclipse_tier5, "blacksun_dark_eclipse_tier5")
