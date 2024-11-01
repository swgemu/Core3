endor_smuggler_transport = ShipAgent:new {
	template = "hutt_heavy_s02_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "bomber",

	experience = 4259.84,

	lootChance = 0.182,
	lootRolls = 1,
	lootTable = "space_hutt_tier4",

	minCredits = 280,
	maxCredits = 650,

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

ShipAgentTemplates:addShipAgentTemplate(endor_smuggler_transport, "endor_smuggler_transport")
