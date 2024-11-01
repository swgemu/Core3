bh_target_guard_elite = ShipAgent:new {
	template = "hutt_medium_s01_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant"},

	color1 = 29,
	color2 = 58,
	texture = 3,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(bh_target_guard_elite, "bh_target_guard_elite")
