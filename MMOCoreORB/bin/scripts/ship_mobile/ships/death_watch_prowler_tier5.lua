death_watch_prowler_tier5 = ShipAgent:new {
	template = "blacksun_medium_s01_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 7381.98,

	lootChance = 0.143,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 455,
	maxCredits = 875,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 35,
	color2 = 35,
	texture = 5,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(death_watch_prowler_tier5, "death_watch_prowler_tier5")
