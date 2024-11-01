endor_trade_guild_freighter_tier1 = ShipAgent:new {
	template = "freighterheavy_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "merchant",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_freighter_tier1, "endor_trade_guild_freighter_tier1")
