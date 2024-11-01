kimogila_scrapper_tier1 = ShipAgent:new {
	template = "hutt_light_s02_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 90,

	lootChance = 0.153,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "nym"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec", "blacksun"},

	color1 = 38,
	color2 = 22,
	texture = 6,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(kimogila_scrapper_tier1, "kimogila_scrapper_tier1")
