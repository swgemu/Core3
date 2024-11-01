endor_artisan_diplomat_boss = ShipAgent:new {
	template = "droid_fighter_tier4",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_artisan_diplomat_boss, "endor_artisan_diplomat_boss")
