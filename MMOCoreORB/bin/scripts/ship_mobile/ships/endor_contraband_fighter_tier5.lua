endor_contraband_fighter_tier5 = ShipAgent:new {
	template = "hutt_light_s01_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6039.8,

	lootChance = 0.117,
	lootRolls = 1,
	lootTable = "space_hutt_tier5",

	minCredits = 350,
	maxCredits = 750,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"civilian", "rebel", "imperial", "merchant", "pirate"},

	color1 = 0,
	color2 = 15,
	texture = 6,
	appearance = "hutt",

	tauntType = "hutt_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(endor_contraband_fighter_tier5, "endor_contraband_fighter_tier5")
