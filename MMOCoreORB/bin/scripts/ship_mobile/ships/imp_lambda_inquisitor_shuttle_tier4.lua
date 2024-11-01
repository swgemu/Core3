imp_lambda_inquisitor_shuttle_tier4 = ShipAgent:new {
	template = "lambdashuttle_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "bomber",

	experience = 8192,

	lootChance = 0.35,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -64,
	rebelFactionReward = 32,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_lambda_inquisitor_shuttle_tier4, "imp_lambda_inquisitor_shuttle_tier4")
