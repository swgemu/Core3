dantooine_scavenger_bomber = ShipAgent:new {
	template = "droid_fighter_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "bomber",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "blacksun", "nym"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_scavenger_bomber, "dantooine_scavenger_bomber")
