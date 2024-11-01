kimogila_scrapper_tier2 = ShipAgent:new {
	template = "hutt_light_s02_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 65,
	maxCredits = 130,

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

ShipAgentTemplates:addShipAgentTemplate(kimogila_scrapper_tier2, "kimogila_scrapper_tier2")
