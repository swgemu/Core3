imp_tie_aggressor_tier3 = ShipAgent:new {
	template = "tieaggressor_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 2048,

	lootChance = 0.24,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 160,
	maxCredits = 353,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -30,
	rebelFactionReward = 15,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_tie_aggressor_tier3, "imp_tie_aggressor_tier3")
