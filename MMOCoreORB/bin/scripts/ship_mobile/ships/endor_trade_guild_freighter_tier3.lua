endor_trade_guild_freighter_tier3 = ShipAgent:new {
	template = "freighterheavy_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "merchant",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_freighter_tier3, "endor_trade_guild_freighter_tier3")
