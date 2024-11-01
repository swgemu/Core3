endor_artisan_peacekeeper_tier4_endor = ShipAgent:new {
	template = "hutt_light_s02_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_story_endor_artisan",

	minCredits = 200,
	maxCredits = 500,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},
	enemyFactions = {"pirate"},

	color1 = 34,
	color2 = 53,
	texture = 3,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_peacekeeper_tier4_endor, "endor_artisan_peacekeeper_tier4_endor")
