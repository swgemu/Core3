mercenary_guard_tier5 = ShipAgent:new {
	template = "ywing_tier5",
	pilotTemplate = "bomber_tier5",
	shipType = "fighter",

	experience = 7046.43,

	lootChance = 0.1365,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 425,
	maxCredits = 850,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian", "merchant"},
	enemyFactions = {"pirate", "nym", "hutt", "blacksun", "corsair", "valarian", "borvo", "imperial"},
	color2 = 52,
	texture = 1,
	appearance = "civilian",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(mercenary_guard_tier5, "mercenary_guard_tier5")
