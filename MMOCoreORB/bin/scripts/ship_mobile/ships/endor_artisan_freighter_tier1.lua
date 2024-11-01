endor_artisan_freighter_tier1 = ShipAgent:new {
	template = "freighterlight_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "civilian",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_freighter_tier1, "endor_artisan_freighter_tier1")
