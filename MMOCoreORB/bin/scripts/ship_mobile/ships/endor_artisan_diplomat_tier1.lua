endor_artisan_diplomat_tier1 = ShipAgent:new {
	template = "droid_fighter_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_diplomat_tier1, "endor_artisan_diplomat_tier1")
