endor_trade_guild_mercenary_tier2 = ShipAgent:new {
	template = "blacksun_heavy_s02_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "fighter",

	experience = 480,

	lootChance = 0.192,
	lootRolls = 1,
	lootTable = "space_merchant_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 20,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_mercenary_tier2, "endor_trade_guild_mercenary_tier2")
