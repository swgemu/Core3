valarian_bomber_tier1_tatooine = ShipAgent:new {
	template = "hutt_heavy_s01_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "bomber",

	experience = 130,

	lootChance = 0.221,
	lootRolls = 1,
	lootTable = "space_story_tatooine_valarian",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 1,

	spaceFaction = "valarian",
	alliedFactions = {"valarian"},
	enemyFactions = {"imperial", "civilian", "merchant", "hutt", "pirate", "rebel", "blacksun", "borvo", "corsec", "rsf"},

	color1 = 32,
	color2 = 35,
	texture = 3,
	appearance = "valarian",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(valarian_bomber_tier1_tatooine, "valarian_bomber_tier1_tatooine")
