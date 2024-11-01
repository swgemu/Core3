endor_trade_guild_collector_tier2 = ShipAgent:new {
	template = "yt1300_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "fighter",

	experience = 800,

	lootChance = 0.32,
	lootRolls = 1,
	lootTable = "space_merchant_tier2",

	minCredits = 95,
	maxCredits = 240,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},

	color1 = 28,
	color2 = 14,
	texture = 1,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_collector_tier2, "endor_trade_guild_collector_tier2")
