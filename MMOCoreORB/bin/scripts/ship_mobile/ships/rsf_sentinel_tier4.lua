rsf_sentinel_tier4 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier4",
	pilotTemplate = "slow_tier5",
	shipType = "fighter",

	experience = 13107.2,

	lootChance = 0.56,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 465,
	maxCredits = 950,

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

ShipAgentTemplates:addShipAgentTemplate(rsf_sentinel_tier4, "rsf_sentinel_tier4")
