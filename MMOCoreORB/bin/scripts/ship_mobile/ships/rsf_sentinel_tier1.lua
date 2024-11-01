rsf_sentinel_tier1 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier1",
	pilotTemplate = "slow_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(rsf_sentinel_tier1, "rsf_sentinel_tier1")
