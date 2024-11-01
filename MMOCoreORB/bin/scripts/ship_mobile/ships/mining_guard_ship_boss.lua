mining_guard_ship_boss = ShipAgent:new {
	template = "z95_tier4",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_merchant_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "civilian"},
	enemyFactions = {"blacksun"},

	color1 = 22,
	color2 = 30,
	texture = 4,
	appearance = "civilian",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(mining_guard_ship_boss, "mining_guard_ship_boss")
