endor_artisan_peacekeeper_tier3 = ShipAgent:new {
	template = "hutt_light_s02_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},
	enemyFactions = {"pirate"},

	color1 = 34,
	color2 = 53,
	texture = 3,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_peacekeeper_tier3, "endor_artisan_peacekeeper_tier3")
