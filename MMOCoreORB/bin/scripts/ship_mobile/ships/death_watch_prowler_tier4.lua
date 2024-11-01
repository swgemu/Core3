death_watch_prowler_tier4 = ShipAgent:new {
	template = "blacksun_medium_s01_tier4",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "fighter",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 260,
	maxCredits = 575,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 35,
	color2 = 35,
	texture = 5,
	appearance = "generic_pirate",
}

ShipAgentTemplates:addShipAgentTemplate(death_watch_prowler_tier4, "death_watch_prowler_tier4")
