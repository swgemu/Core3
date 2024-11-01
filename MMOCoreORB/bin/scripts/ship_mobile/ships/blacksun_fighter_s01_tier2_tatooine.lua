blacksun_fighter_s01_tier2_tatooine = ShipAgent:new {
	template = "blacksun_light_s01_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_story_tatooine_blacksun",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "blacksun",
	alliedFactions = {"blacksun"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 3,
	color2 = 4,
	texture = 3,
	appearance = "blacksun",

	tauntType = "blacksun_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacksun_fighter_s01_tier2_tatooine, "blacksun_fighter_s01_tier2_tatooine")
