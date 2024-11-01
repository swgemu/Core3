endor_trade_guild_mercenary_tier5 = ShipAgent:new {
	template = "blacksun_heavy_s02_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "fighter",

	experience = 8053.06,

	lootChance = 0.156,
	lootRolls = 1,
	lootTable = "space_merchant_tier5",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 20,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_mercenary_tier5, "endor_trade_guild_mercenary_tier5")
