rogue_droid_alpha_tier2_naboo = ShipAgent:new {
	template = "droid_fighter_tier2",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_story_naboo_droid",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "rsf"},
}

ShipAgentTemplates:addShipAgentTemplate(rogue_droid_alpha_tier2_naboo, "rogue_droid_alpha_tier2_naboo")
