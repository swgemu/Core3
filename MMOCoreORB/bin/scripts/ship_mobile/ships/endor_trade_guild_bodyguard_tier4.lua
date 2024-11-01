endor_trade_guild_bodyguard_tier4 = ShipAgent:new {
	template = "blacksun_light_s01_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "bomber",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_merchant_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 13,
	color2 = 36,
	texture = 4,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_bodyguard_tier4, "endor_trade_guild_bodyguard_tier4")
