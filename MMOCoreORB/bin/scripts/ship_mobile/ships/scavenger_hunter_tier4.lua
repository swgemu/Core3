scavenger_hunter_tier4 = ShipAgent:new {
	template = "blacksun_medium_s01_tier4",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "fighter",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 260,
	maxCredits = 575,

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

ShipAgentTemplates:addShipAgentTemplate(scavenger_hunter_tier4, "scavenger_hunter_tier4")
