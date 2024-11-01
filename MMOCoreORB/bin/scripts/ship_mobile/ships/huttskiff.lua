huttskiff = ShipAgent:new {
	template = "hutt_light_s02_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 90,

	lootChance = 0.153,
	lootRolls = 1,
	lootTable = "space_hutt_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "valarian", "pirate", "rsf", "corsec", "blacksun"},

	color1 = 37,
	color2 = 23,
	texture = 3,
	appearance = "hutt",

	tauntType = "hutt_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(huttskiff, "huttskiff")
