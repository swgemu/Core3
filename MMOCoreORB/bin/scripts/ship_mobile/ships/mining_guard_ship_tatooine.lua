mining_guard_ship_tatooine = ShipAgent:new {
	template = "z95_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_story_tatooine_mining",

	minCredits = 51,
	maxCredits = 103,

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

ShipAgentTemplates:addShipAgentTemplate(mining_guard_ship_tatooine, "mining_guard_ship_tatooine")
