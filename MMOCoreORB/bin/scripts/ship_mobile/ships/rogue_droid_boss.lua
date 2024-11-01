rogue_droid_boss = ShipAgent:new {
	template = "droid_fighter_tier2",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "rsf"},
}

ShipAgentTemplates:addShipAgentTemplate(rogue_droid_boss, "rogue_droid_boss")
