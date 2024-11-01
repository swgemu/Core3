endor_trade_guild_freighter_tier2 = ShipAgent:new {
	template = "freighterheavy_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "merchant",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_freighter_tier2, "endor_trade_guild_freighter_tier2")
