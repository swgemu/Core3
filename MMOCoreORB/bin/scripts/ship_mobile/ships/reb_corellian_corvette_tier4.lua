reb_corellian_corvette_tier4 = ShipAgent:new {
	template = "corvette",
	pilotTemplate = "slow_tier5",
	shipType = "capital",

	experience = 43000,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier5",

	minCredits = 791,
	maxCredits = 1300,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 94,
	rebelFactionReward = -187,
	appearance = "rebel_officer",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_corellian_corvette_tier4, "reb_corellian_corvette_tier4")
