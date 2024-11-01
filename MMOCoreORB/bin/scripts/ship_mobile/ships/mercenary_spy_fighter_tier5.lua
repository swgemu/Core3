mercenary_spy_fighter_tier5 = ShipAgent:new {
	template = "hutt_medium_s01_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian", "merchant"},
	enemyFactions = {"pirate", "nym", "hutt", "blacksun", "corsair", "valarian", "borvo", "imperial"},

	color1 = 61,
	color2 = 60,
	texture = 4,
	questLoot = "pirate_data",
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(mercenary_spy_fighter_tier5, "mercenary_spy_fighter_tier5")
