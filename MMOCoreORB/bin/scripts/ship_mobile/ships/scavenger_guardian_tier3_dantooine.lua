scavenger_guardian_tier3_dantooine = ShipAgent:new {
	template = "droid_fighter_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_story_dantooine_scavengers",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "blacksun", "nym"},
	enemyFactions = {"civilian", "rebel", "imperial", "hutt", "merchant"},
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(scavenger_guardian_tier3_dantooine, "scavenger_guardian_tier3_dantooine")
