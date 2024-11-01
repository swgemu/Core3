endor_trade_guild_collector_tier4 = ShipAgent:new {
	template = "yt1300_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "fighter",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_merchant_tier4",

	minCredits = 400,
	maxCredits = 800,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},

	color1 = 28,
	color2 = 14,
	texture = 1,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_collector_tier4, "endor_trade_guild_collector_tier4")
