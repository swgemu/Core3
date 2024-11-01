force_bomber_tier5 = ShipAgent:new {
	template = "hutt_heavy_s02_tier5",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "bomber",

	experience = 8724.15,

	lootChance = 0.169,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 465,
	maxCredits = 925,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant"},

	color1 = 8,
	color2 = 63,
	texture = 4,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(force_bomber_tier5, "force_bomber_tier5")
