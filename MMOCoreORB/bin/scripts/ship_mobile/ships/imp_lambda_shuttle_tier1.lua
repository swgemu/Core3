imp_lambda_shuttle_tier1 = ShipAgent:new {
	template = "lambdashuttle_tier1",
	pilotTemplate = "bomber_tier1",
	shipType = "bomber",

	experience = 250,

	lootChance = 0.425,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 4,
	maxCredits = 57,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -8,
	rebelFactionReward = 4,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_lambda_shuttle_tier1, "imp_lambda_shuttle_tier1")
