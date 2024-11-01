borvo_bomber_tier5 = ShipAgent:new {
	template = "hutt_heavy_s02_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "bomber",

	experience = 8724.15,

	lootChance = 0.169,
	lootRolls = 1,
	lootTable = "space_hutt_tier5",

	minCredits = 465,
	maxCredits = 925,

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

ShipAgentTemplates:addShipAgentTemplate(borvo_bomber_tier5, "borvo_bomber_tier5")
