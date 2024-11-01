imp_imperial_gunboat_tier2 = ShipAgent:new {
	template = "imperial_gunboat_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "bomber",

	experience = 2000,

	lootChance = 0.8,
	lootRolls = 1,
	lootTable = "space_imperial_tier2",

	minCredits = 180,
	maxCredits = 460,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -50,
	rebelFactionReward = 25,
	formationLocation = 2,
	appearance = "imperial_officer",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_imperial_gunboat_tier2, "imp_imperial_gunboat_tier2")
