endor_trade_guild_collector_tier3 = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "fighter",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_merchant_tier3",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},

	color1 = 28,
	color2 = 14,
	texture = 1,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_collector_tier3, "endor_trade_guild_collector_tier3")
