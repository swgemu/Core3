scavenger_collector_tier1 = ShipAgent:new {
	template = "droid_fighter_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "blacksun", "nym"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(scavenger_collector_tier1, "scavenger_collector_tier1")
