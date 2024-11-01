endor_trade_guild_mercenary_tier4 = ShipAgent:new {
	template = "blacksun_heavy_s02_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "fighter",

	experience = 3932.16,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_merchant_tier4",

	minCredits = 275,
	maxCredits = 600,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 20,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_mercenary_tier4, "endor_trade_guild_mercenary_tier4")
