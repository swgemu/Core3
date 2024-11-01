mercenary_guard_tier4 = ShipAgent:new {
	template = "ywing_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "fighter",

	experience = 3440.64,

	lootChance = 0.147,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 240,
	maxCredits = 550,

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

ShipAgentTemplates:addShipAgentTemplate(mercenary_guard_tier4, "mercenary_guard_tier4")
