imp_tie_aggressor_tier5 = ShipAgent:new {
	template = "tieaggressor_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 10737.42,

	lootChance = 0.208,
	lootRolls = 1,
	lootTable = "space_imperial_tier5",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -115,
	rebelFactionReward = 58,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_tie_aggressor_tier5, "imp_tie_aggressor_tier5")
