rsf_stinger_tier2 = ShipAgent:new {
	template = "z95_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 0,

	spaceFaction = "rsf",
	alliedFactions = {"civilian", "merchant", "corsec", "rsf", "imperial"},
	enemyFactions = {"hutt", "blacksun", "pirate", "valarian"},

	color1 = 63,
	color2 = 20,
	texture = 14,
	formationLocation = 3,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rsf_stinger_tier2, "rsf_stinger_tier2")
