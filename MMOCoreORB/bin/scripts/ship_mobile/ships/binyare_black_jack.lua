binyare_black_jack = ShipAgent:new {
	template = "hutt_heavy_s01_tier2",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "fighter",

	experience = 520,

	lootChance = 0.208,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 80,
	maxCredits = 200,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant"},

	color1 = 54,
	color2 = 51,
	texture = 2,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(binyare_black_jack, "binyare_black_jack")
