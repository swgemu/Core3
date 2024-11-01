death_watch_assassin_tier2 = ShipAgent:new {
	template = "blacksun_light_s02_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 35,
	color2 = 35,
	texture = 3,
}

ShipAgentTemplates:addShipAgentTemplate(death_watch_assassin_tier2, "death_watch_assassin_tier2")
