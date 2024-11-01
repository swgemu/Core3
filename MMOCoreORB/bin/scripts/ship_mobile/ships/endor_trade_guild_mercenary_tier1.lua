endor_trade_guild_mercenary_tier1 = ShipAgent:new {
	template = "blacksun_heavy_s02_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "fighter",

	experience = 120,

	lootChance = 0.204,
	lootRolls = 1,
	lootTable = "space_merchant_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 12,
	color2 = 20,
	texture = 2,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_mercenary_tier1, "endor_trade_guild_mercenary_tier1")
