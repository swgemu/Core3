mercenary_spy_fighter_tier2 = ShipAgent:new {
	template = "hutt_medium_s01_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(mercenary_spy_fighter_tier2, "mercenary_spy_fighter_tier2")
