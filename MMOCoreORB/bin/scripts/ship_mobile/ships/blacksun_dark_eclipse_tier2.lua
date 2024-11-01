blacksun_dark_eclipse_tier2 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "capital",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_blacksun_tier2",

	minCredits = 170,
	maxCredits = 368,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_dark_eclipse_tier2, "blacksun_dark_eclipse_tier2")
