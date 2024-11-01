death_watch_assassin_tier1 = ShipAgent:new {
	template = "blacksun_light_s02_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 35,
	color2 = 35,
	texture = 3,
}

ShipAgentTemplates:addShipAgentTemplate(death_watch_assassin_tier1, "death_watch_assassin_tier1")
