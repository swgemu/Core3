imp_lambda_shuttle_tier2 = ShipAgent:new {
	template = "lambdashuttle_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "bomber",

	experience = 1000,

	lootChance = 0.4,
	lootRolls = 1,
	lootTable = "space_imperial_tier2",

	minCredits = 18,
	maxCredits = 230,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -25,
	rebelFactionReward = 13,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_lambda_shuttle_tier2, "imp_lambda_shuttle_tier2")
