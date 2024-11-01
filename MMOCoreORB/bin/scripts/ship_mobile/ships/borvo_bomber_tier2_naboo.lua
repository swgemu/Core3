borvo_bomber_tier2_naboo = ShipAgent:new {
	template = "hutt_heavy_s02_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "bomber",

	experience = 520,

	lootChance = 0.208,
	lootRolls = 1,
	lootTable = "space_story_naboo_borvo",

	minCredits = 80,
	maxCredits = 200,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian"},

	color1 = 4,
	color2 = 3,
	texture = 2,
	appearance = "hutt",

	tauntType = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(borvo_bomber_tier2_naboo, "borvo_bomber_tier2_naboo")
