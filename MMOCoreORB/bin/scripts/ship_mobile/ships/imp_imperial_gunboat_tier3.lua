imp_imperial_gunboat_tier3 = ShipAgent:new {
	template = "imperial_gunboat_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "bomber",

	experience = 6400,

	lootChance = 0.75,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 350,
	maxCredits = 750,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -128,
	rebelFactionReward = 64,
	formationLocation = 2,
	appearance = "imperial_officer",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_imperial_gunboat_tier3, "imp_imperial_gunboat_tier3")
