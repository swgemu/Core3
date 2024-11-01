scavenger_hunter_tier5 = ShipAgent:new {
	template = "blacksun_medium_s01_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 7381.98,

	lootChance = 0.143,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 455,
	maxCredits = 875,

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

ShipAgentTemplates:addShipAgentTemplate(scavenger_hunter_tier5, "scavenger_hunter_tier5")
