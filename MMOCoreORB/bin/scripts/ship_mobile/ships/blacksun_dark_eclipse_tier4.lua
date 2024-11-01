blacksun_dark_eclipse_tier4 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "capital",

	experience = 13107.2,

	lootChance = 0.56,
	lootRolls = 1,
	lootTable = "space_blacksun_tier4",

	minCredits = 465,
	maxCredits = 950,

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

ShipAgentTemplates:addShipAgentTemplate(blacksun_dark_eclipse_tier4, "blacksun_dark_eclipse_tier4")
