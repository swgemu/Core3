borvo_bomber_tier1 = ShipAgent:new {
	template = "hutt_heavy_s02_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "bomber",

	experience = 130,

	lootChance = 0.221,
	lootRolls = 1,
	lootTable = "space_hutt_tier1",

	minCredits = 55,
	maxCredits = 110,

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

ShipAgentTemplates:addShipAgentTemplate(borvo_bomber_tier1, "borvo_bomber_tier1")
