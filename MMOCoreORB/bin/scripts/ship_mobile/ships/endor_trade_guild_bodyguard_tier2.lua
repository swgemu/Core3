endor_trade_guild_bodyguard_tier2 = ShipAgent:new {
	template = "blacksun_light_s01_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "bomber",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_merchant_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"pirate"},

	color1 = 13,
	color2 = 36,
	texture = 4,
}

ShipAgentTemplates:addShipAgentTemplate(endor_trade_guild_bodyguard_tier2, "endor_trade_guild_bodyguard_tier2")
