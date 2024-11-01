kimogila_champion_tier2 = ShipAgent:new {
	template = "hutt_medium_s02_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "bomber",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(kimogila_champion_tier2, "kimogila_champion_tier2")
