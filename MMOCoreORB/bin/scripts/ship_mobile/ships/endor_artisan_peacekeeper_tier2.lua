endor_artisan_peacekeeper_tier2 = ShipAgent:new {
	template = "hutt_light_s02_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 65,
	maxCredits = 130,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},
	enemyFactions = {"pirate"},

	color1 = 34,
	color2 = 53,
	texture = 3,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_peacekeeper_tier2, "endor_artisan_peacekeeper_tier2")
