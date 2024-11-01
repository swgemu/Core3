endor_artisan_peacekeeper = ShipAgent:new {
	template = "z95_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},

	color1 = 12,
	color2 = 41,
	texture = 4,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_peacekeeper, "endor_artisan_peacekeeper")
