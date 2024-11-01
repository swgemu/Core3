blacklight_bomber_tier3 = ShipAgent:new {
	template = "hutt_heavy_s01_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "bomber",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 170,
	maxCredits = 382,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"spynet"},

	color1 = 3,
	color2 = 5,
	texture = 6,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacklight_bomber_tier3, "blacklight_bomber_tier3")
