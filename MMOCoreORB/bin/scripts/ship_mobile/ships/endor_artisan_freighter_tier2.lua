endor_artisan_freighter_tier2 = ShipAgent:new {
	template = "freighterlight_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "civilian",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_freighter_tier2, "endor_artisan_freighter_tier2")
