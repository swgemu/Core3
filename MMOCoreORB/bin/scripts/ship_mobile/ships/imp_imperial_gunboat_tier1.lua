imp_imperial_gunboat_tier1 = ShipAgent:new {
	template = "imperial_gunboat_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "bomber",

	experience = 500,

	lootChance = 0.85,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 80,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -16,
	rebelFactionReward = 8,
	formationLocation = 2,
	appearance = "imperial_officer",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_imperial_gunboat_tier1, "imp_imperial_gunboat_tier1")
