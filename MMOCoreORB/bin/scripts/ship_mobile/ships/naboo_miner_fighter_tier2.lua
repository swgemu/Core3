naboo_miner_fighter_tier2 = ShipAgent:new {
	template = "z95_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian", "imperial", "hutt", "rebel"},
	enemyFactions = {"pirate"},

	color1 = 22,
	color2 = 30,
	texture = 4,
	appearance = "civilian",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(naboo_miner_fighter_tier2, "naboo_miner_fighter_tier2")
