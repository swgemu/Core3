kimogila_champion_tier1 = ShipAgent:new {
	template = "hutt_medium_s02_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "bomber",

	experience = 100,

	lootChance = 0.17,
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

ShipAgentTemplates:addShipAgentTemplate(kimogila_champion_tier1, "kimogila_champion_tier1")
