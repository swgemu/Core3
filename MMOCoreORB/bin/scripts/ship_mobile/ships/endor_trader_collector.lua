endor_trader_collector = ShipAgent:new {
	template = "freightermedium_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_merchant_tier4",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "merchant",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trader_collector, "endor_trader_collector")
