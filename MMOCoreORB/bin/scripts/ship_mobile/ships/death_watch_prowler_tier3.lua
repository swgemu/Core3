death_watch_prowler_tier3 = ShipAgent:new {
	template = "blacksun_medium_s01_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 35,
	color2 = 35,
	texture = 5,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(death_watch_prowler_tier3, "death_watch_prowler_tier3")
