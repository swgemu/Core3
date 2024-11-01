mining_guard_ship_tier3 = ShipAgent:new {
	template = "z95_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_merchant_tier3",

	minCredits = 120,
	maxCredits = 294,

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

ShipAgentTemplates:addShipAgentTemplate(mining_guard_ship_tier3, "mining_guard_ship_tier3")
