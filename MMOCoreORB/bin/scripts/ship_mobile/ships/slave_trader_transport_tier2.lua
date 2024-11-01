slave_trader_transport_tier2 = ShipAgent:new {
	template = "hutt_medium_s01_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_hutt_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "civilian",

	color1 = 7,
	color2 = 59,
	texture = 0,
}

ShipAgentTemplates:addShipAgentTemplate(slave_trader_transport_tier2, "slave_trader_transport_tier2")
