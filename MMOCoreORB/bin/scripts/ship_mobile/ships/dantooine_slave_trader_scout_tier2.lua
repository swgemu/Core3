dantooine_slave_trader_scout_tier2 = ShipAgent:new {
	template = "droid_fighter_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_story_dantooine_slave",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "imperial"},
	enemyFactions = {"rebel", "nym", "merchant"},
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_slave_trader_scout_tier2, "dantooine_slave_trader_scout_tier2")
