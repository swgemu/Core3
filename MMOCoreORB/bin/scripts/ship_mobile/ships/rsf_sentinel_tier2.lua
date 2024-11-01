rsf_sentinel_tier2 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier2",
	pilotTemplate = "slow_tier3",
	shipType = "fighter",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 170,
	maxCredits = 368,

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

ShipAgentTemplates:addShipAgentTemplate(rsf_sentinel_tier2, "rsf_sentinel_tier2")
