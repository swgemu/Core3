scavenger_hunter_tier3_dantooine = ShipAgent:new {
	template = "blacksun_medium_s01_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_story_dantooine_scavengers",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant"},

	color1 = 56,
	color2 = 12,
	texture = 2,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(scavenger_hunter_tier3_dantooine, "scavenger_hunter_tier3_dantooine")
