endor_artisan_freighter = ShipAgent:new {
	template = "freighterlight_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "civilian",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_freighter, "endor_artisan_freighter")
