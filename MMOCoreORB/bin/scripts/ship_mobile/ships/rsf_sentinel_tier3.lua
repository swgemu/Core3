rsf_sentinel_tier3 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier3",
	pilotTemplate = "slow_tier4",
	shipType = "fighter",

	experience = 5120,

	lootChance = 0.6,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 94,
	maxCredits = 700,

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

ShipAgentTemplates:addShipAgentTemplate(rsf_sentinel_tier3, "rsf_sentinel_tier3")
