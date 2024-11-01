borvo_boss_tier2 = ShipAgent:new {
	template = "hutt_medium_s01_tier2",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_hutt_tier3",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(borvo_boss_tier2, "borvo_boss_tier2")
