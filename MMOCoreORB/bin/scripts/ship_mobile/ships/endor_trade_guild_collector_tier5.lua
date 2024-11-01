endor_trade_guild_collector_tier5 = ShipAgent:new {
	template = "yt1300_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "fighter",

	experience = 13421.77,

	lootChance = 0.26,
	lootRolls = 1,
	lootTable = "space_merchant_tier5",

	minCredits = 465,
	maxCredits = 975,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},

	color1 = 28,
	color2 = 14,
	texture = 1,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_collector_tier5, "endor_trade_guild_collector_tier5")
