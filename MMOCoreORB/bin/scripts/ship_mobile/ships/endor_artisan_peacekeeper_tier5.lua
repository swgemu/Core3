endor_artisan_peacekeeper_tier5 = ShipAgent:new {
	template = "hutt_light_s02_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6039.8,

	lootChance = 0.117,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 350,
	maxCredits = 750,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},
	enemyFactions = {"pirate"},

	color1 = 34,
	color2 = 53,
	texture = 3,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_peacekeeper_tier5, "endor_artisan_peacekeeper_tier5")
