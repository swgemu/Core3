endor_trade_guild_bodyguard_tier1 = ShipAgent:new {
	template = "blacksun_light_s01_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "bomber",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_merchant_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 13,
	color2 = 36,
	texture = 4,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_bodyguard_tier1, "endor_trade_guild_bodyguard_tier1")
