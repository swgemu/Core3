death_watch_eradicator_tier1 = ShipAgent:new {
	template = "blacksun_heavy_s04_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "bomber",

	experience = 120,

	lootChance = 0.204,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 35,
	color2 = 35,
	texture = 3,
}

ShipAgentTemplates:addShipAgentTemplate(death_watch_eradicator_tier1, "death_watch_eradicator_tier1")
