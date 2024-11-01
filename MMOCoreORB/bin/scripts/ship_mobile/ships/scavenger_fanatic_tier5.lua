scavenger_fanatic_tier5 = ShipAgent:new {
	template = "hutt_light_s01_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6039.8,

	lootChance = 0.117,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 350,
	maxCredits = 750,

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

ShipAgentTemplates:addShipAgentTemplate(scavenger_fanatic_tier5, "scavenger_fanatic_tier5")
