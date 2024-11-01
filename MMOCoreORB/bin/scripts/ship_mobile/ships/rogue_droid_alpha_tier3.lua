rogue_droid_alpha_tier3 = ShipAgent:new {
	template = "droid_fighter_tier3",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "rsf"},
}

ShipAgentTemplates:addShipAgentTemplate(rogue_droid_alpha_tier3, "rogue_droid_alpha_tier3")
