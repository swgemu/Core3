endor_artisan_freighter_tier3 = ShipAgent:new {
	template = "freighterlight_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "civilian",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_freighter_tier3, "endor_artisan_freighter_tier3")
