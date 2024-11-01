endor_trade_guild_freighter_tier5 = ShipAgent:new {
	template = "freighterheavy_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "merchant",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_freighter_tier5, "endor_trade_guild_freighter_tier5")
