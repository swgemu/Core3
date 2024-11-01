endor_trader_bodyguard_hire = ShipAgent:new {
	template = "z95_tier4",
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
	alliedFactions = {"merchant", "civilian"},
	enemyFactions = {"pirate"},

	color1 = 39,
	color2 = 13,
	texture = 4,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trader_bodyguard_hire, "endor_trader_bodyguard_hire")
