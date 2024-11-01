borvo_defender_tier1 = ShipAgent:new {
	template = "hutt_medium_s02_tier2",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_hutt_tier1",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian"},

	color1 = 3,
	color2 = 59,
	texture = 2,
	appearance = "hutt",

	tauntType = "hutt_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(borvo_defender_tier1, "borvo_defender_tier1")
