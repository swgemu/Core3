endor_trade_guild_mercenary_tier3 = ShipAgent:new {
	template = "blacksun_heavy_s02_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "fighter",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_merchant_tier3",

	minCredits = 160,
	maxCredits = 353,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 20,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_mercenary_tier3, "endor_trade_guild_mercenary_tier3")
