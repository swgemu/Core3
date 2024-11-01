imp_tie_aggressor_tier2 = ShipAgent:new {
	template = "tieaggressor_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "fighter",

	experience = 640,

	lootChance = 0.256,
	lootRolls = 1,
	lootTable = "space_imperial_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -12,
	rebelFactionReward = 6,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_tie_aggressor_tier2, "imp_tie_aggressor_tier2")
