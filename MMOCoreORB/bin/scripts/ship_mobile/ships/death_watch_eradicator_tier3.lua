death_watch_eradicator_tier3 = ShipAgent:new {
	template = "blacksun_heavy_s04_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "bomber",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 160,
	maxCredits = 353,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 35,
	color2 = 35,
	texture = 3,
}

ShipAgentTemplates:addShipAgentTemplate(death_watch_eradicator_tier3, "death_watch_eradicator_tier3")
