shinss_escort_fighters_tier3 = ShipAgent:new {
	template = "hutt_heavy_s02_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "fighter",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 170,
	maxCredits = 382,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"civilian", "merchant"},
	enemyFactions = {"imperial", "rebel", "hutt"},

	color1 = 29,
	color2 = 40,
	texture = 1,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(shinss_escort_fighters_tier3, "shinss_escort_fighters_tier3")
