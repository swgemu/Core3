death_watch_assassin = ShipAgent:new {
	template = "z95_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 35,
	color2 = 26,
	texture = 5,
}

ShipAgentTemplates:addShipAgentTemplate(death_watch_assassin, "death_watch_assassin")
