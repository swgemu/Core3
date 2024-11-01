endor_artisan_freighter_tier4_endor = ShipAgent:new {
	template = "freighterlight_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_endor_artisan",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "civilian",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_freighter_tier4_endor, "endor_artisan_freighter_tier4_endor")
