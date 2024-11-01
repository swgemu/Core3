blacksun_dark_eclipse_tier1 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "capital",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_blacksun_tier1",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_dark_eclipse_tier1, "blacksun_dark_eclipse_tier1")
