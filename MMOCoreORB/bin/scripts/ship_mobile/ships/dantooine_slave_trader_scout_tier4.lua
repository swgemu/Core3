dantooine_slave_trader_scout_tier4 = ShipAgent:new {
	template = "droid_fighter_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_story_dantooine_slave",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "imperial"},
	enemyFactions = {"rebel", "nym", "merchant"},
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_slave_trader_scout_tier4, "dantooine_slave_trader_scout_tier4")
