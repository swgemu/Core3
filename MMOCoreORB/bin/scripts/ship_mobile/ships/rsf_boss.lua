rsf_boss = ShipAgent:new {
	template = "z95_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "rsf",
	alliedFactions = {"civilian", "merchant", "corsec", "rsf", "imperial"},
	enemyFactions = {"hutt", "blacksun", "pirate", "valarian"},

	color1 = 63,
	color2 = 20,
	texture = 14,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rsf_boss, "rsf_boss")
