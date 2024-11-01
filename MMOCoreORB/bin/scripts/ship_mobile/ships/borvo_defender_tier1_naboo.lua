borvo_defender_tier1_naboo = ShipAgent:new {
	template = "hutt_medium_s02_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_story_naboo_borvo",

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

ShipAgentTemplates:addShipAgentTemplate(borvo_defender_tier1_naboo, "borvo_defender_tier1_naboo")
