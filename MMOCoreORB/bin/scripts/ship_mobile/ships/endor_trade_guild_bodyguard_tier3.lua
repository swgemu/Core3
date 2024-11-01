endor_trade_guild_bodyguard_tier3 = ShipAgent:new {
	template = "blacksun_light_s01_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "bomber",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_merchant_tier3",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 13,
	color2 = 36,
	texture = 4,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_bodyguard_tier3, "endor_trade_guild_bodyguard_tier3")
