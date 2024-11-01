dantooine_slave_trader_guard_tier5 = ShipAgent:new {
	template = "z95_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_story_dantooine_slave",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "imperial"},
	enemyFactions = {"rebel", "nym", "merchant"},

	color1 = 23,
	color2 = 47,
	texture = 3,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_slave_trader_guard_tier5, "dantooine_slave_trader_guard_tier5")
