scavenger_guardian_tier2 = ShipAgent:new {
	template = "droid_fighter_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "blacksun", "nym"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(scavenger_guardian_tier2, "scavenger_guardian_tier2")
