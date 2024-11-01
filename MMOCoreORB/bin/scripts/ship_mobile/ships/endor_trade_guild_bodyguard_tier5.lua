endor_trade_guild_bodyguard_tier5 = ShipAgent:new {
	template = "blacksun_light_s01_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "bomber",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_merchant_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 13,
	color2 = 36,
	texture = 4,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_bodyguard_tier5, "endor_trade_guild_bodyguard_tier5")
