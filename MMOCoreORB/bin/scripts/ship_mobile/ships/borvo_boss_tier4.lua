borvo_boss_tier4 = ShipAgent:new {
	template = "hutt_medium_s01_tier4",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_hutt_tier5",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian"},

	color1 = 9,
	color2 = 18,
	texture = 1,
	appearance = "hutt",

	tauntType = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(borvo_boss_tier4, "borvo_boss_tier4")
