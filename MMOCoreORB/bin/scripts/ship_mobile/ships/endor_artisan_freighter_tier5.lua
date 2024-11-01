endor_artisan_freighter_tier5 = ShipAgent:new {
	template = "freighterlight_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "civilian",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_freighter_tier5, "endor_artisan_freighter_tier5")
