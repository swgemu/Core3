endor_trader_bodyguard_boss = ShipAgent:new {
	template = "z95_tier5",
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
	alliedFactions = {"merchant", "civilian"},
	enemyFactions = {"pirate"},

	color1 = 39,
	color2 = 13,
	texture = 4,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trader_bodyguard_boss, "endor_trader_bodyguard_boss")
