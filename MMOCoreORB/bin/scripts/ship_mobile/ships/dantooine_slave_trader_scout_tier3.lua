dantooine_slave_trader_scout_tier3 = ShipAgent:new {
	template = "droid_fighter_tier3",
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
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_slave_trader_scout_tier3, "dantooine_slave_trader_scout_tier3")
