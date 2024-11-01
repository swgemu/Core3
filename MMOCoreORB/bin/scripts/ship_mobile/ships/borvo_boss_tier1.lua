borvo_boss_tier1 = ShipAgent:new {
	template = "hutt_medium_s01_tier1",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_hutt_tier2",

	minCredits = 51,
	maxCredits = 103,

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

ShipAgentTemplates:addShipAgentTemplate(borvo_boss_tier1, "borvo_boss_tier1")
