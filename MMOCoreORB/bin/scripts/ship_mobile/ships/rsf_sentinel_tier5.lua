rsf_sentinel_tier5 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "fighter",

	experience = 26843.55,

	lootChance = 0.52,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 525,
	maxCredits = 1075,

	aggressive = 0,

	spaceFaction = "rsf",
	alliedFactions = {"civilian", "merchant", "corsec", "rsf", "imperial"},
	enemyFactions = {"hutt", "blacksun", "pirate", "valarian"},

	color1 = 3,
	color2 = 42,
	texture = 1,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rsf_sentinel_tier5, "rsf_sentinel_tier5")
