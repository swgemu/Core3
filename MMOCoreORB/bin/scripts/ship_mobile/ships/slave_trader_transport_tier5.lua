slave_trader_transport_tier5 = ShipAgent:new {
	template = "hutt_medium_s01_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_hutt_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 1,

	spaceFaction = "civilian",

	color1 = 7,
	color2 = 59,
	texture = 0,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(slave_trader_transport_tier5, "slave_trader_transport_tier5")
