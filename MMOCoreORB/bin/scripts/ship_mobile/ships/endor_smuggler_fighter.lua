endor_smuggler_fighter = ShipAgent:new {
	template = "hutt_light_s01_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_hutt_tier4",

	minCredits = 200,
	maxCredits = 500,

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

ShipAgentTemplates:addShipAgentTemplate(endor_smuggler_fighter, "endor_smuggler_fighter")
