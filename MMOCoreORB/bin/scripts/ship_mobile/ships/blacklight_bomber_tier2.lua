blacklight_bomber_tier2 = ShipAgent:new {
	template = "hutt_heavy_s01_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "bomber",

	experience = 520,

	lootChance = 0.208,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 80,
	maxCredits = 200,

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

ShipAgentTemplates:addShipAgentTemplate(blacklight_bomber_tier2, "blacklight_bomber_tier2")
