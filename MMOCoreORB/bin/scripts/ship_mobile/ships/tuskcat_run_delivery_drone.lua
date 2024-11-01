tuskcat_run_delivery_drone = ShipAgent:new {
	template = "hutt_heavy_s01_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "bomber",

	experience = 130,

	lootChance = 0.221,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 0,

	spaceFaction = "merchant",

	color1 = 3,
	color2 = 5,
	texture = 6,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(tuskcat_run_delivery_drone, "tuskcat_run_delivery_drone")
