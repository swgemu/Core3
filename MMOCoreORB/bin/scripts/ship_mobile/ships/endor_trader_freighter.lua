endor_trader_freighter = ShipAgent:new {
	template = "freighterheavy_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "merchant",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trader_freighter, "endor_trader_freighter")
