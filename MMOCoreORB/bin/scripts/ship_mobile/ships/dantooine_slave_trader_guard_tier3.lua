dantooine_slave_trader_guard_tier3 = ShipAgent:new {
	template = "z95_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_story_dantooine_slave",

	minCredits = 120,
	maxCredits = 294,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_slave_trader_guard_tier3, "dantooine_slave_trader_guard_tier3")
