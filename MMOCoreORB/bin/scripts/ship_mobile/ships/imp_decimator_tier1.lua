imp_decimator_tier1 = ShipAgent:new {
	template = "decimator_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "fighter",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 60,
	maxCredits = 120,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -6,
	rebelFactionReward = 3,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_decimator_tier1, "imp_decimator_tier1")
