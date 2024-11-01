slave_trader_transport_tier3_dantooine = ShipAgent:new {
	template = "hutt_medium_s01_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_story_dantooine_slave",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "civilian",

	color1 = 7,
	color2 = 59,
	texture = 0,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(slave_trader_transport_tier3_dantooine, "slave_trader_transport_tier3_dantooine")
