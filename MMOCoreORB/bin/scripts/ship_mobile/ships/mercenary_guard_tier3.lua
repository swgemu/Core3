mercenary_guard_tier3 = ShipAgent:new {
	template = "ywing_tier3",
	pilotTemplate = "bomber_tier3",
	shipType = "fighter",

	experience = 1344,

	lootChance = 0.1575,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 150,
	maxCredits = 309,

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

ShipAgentTemplates:addShipAgentTemplate(mercenary_guard_tier3, "mercenary_guard_tier3")
