endor_trade_guild_collector_tier1 = ShipAgent:new {
	template = "yt1300_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "fighter",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_merchant_tier1",

	minCredits = 60,
	maxCredits = 120,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},

	color1 = 28,
	color2 = 14,
	texture = 1,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_collector_tier1, "endor_trade_guild_collector_tier1")
