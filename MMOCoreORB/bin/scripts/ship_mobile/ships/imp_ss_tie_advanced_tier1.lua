imp_ss_tie_advanced_tier1 = ShipAgent:new {
	template = "tieadvanced_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 120,

	lootChance = 0.204,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -4,
	rebelFactionReward = 2,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_ss_tie_advanced_tier1, "imp_ss_tie_advanced_tier1")
