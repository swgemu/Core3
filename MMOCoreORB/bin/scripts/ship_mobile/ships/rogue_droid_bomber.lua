rogue_droid_bomber = ShipAgent:new {
	template = "droid_fighter_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "bomber",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "rsf"},
}

ShipAgentTemplates:addShipAgentTemplate(rogue_droid_bomber, "rogue_droid_bomber")
