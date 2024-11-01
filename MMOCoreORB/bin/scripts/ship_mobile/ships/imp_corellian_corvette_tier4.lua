imp_corellian_corvette_tier4 = ShipAgent:new {
	template = "corvette",
	pilotTemplate = "slow_tier5",
	shipType = "capital",

	experience = 43000,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier5",

	minCredits = 791,
	maxCredits = 1300,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"civilian", "imperial", "merchant"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -191,
	rebelFactionReward = 96,
	appearance = "imperial_officer",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_corellian_corvette_tier4, "imp_corellian_corvette_tier4")
