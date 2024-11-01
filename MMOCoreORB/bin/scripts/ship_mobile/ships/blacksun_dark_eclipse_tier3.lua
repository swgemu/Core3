blacksun_dark_eclipse_tier3 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "capital",

	experience = 5120,

	lootChance = 0.6,
	lootRolls = 1,
	lootTable = "space_blacksun_tier3",

	minCredits = 94,
	maxCredits = 700,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_dark_eclipse_tier3, "blacksun_dark_eclipse_tier3")
