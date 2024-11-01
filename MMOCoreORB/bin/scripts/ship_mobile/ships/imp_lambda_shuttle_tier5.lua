imp_lambda_shuttle_tier5 = ShipAgent:new {
	template = "lambdashuttle_tier5",
	pilotTemplate = "bomber_tier5",
	shipType = "bomber",

	experience = 16777.22,

	lootChance = 0.325,
	lootRolls = 1,
	lootTable = "space_imperial_tier5",

	minCredits = 500,
	maxCredits = 1050,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -239,
	rebelFactionReward = 120,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_lambda_shuttle_tier5, "imp_lambda_shuttle_tier5")
