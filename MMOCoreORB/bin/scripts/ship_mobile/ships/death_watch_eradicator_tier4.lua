death_watch_eradicator_tier4 = ShipAgent:new {
	template = "blacksun_heavy_s04_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "bomber",

	experience = 3932.16,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 275,
	maxCredits = 600,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 35,
	color2 = 35,
	texture = 3,
}

ShipAgentTemplates:addShipAgentTemplate(death_watch_eradicator_tier4, "death_watch_eradicator_tier4")
