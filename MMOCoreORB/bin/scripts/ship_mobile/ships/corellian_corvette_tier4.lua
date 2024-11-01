corellian_corvette_tier4 = ShipAgent:new {
	template = "corvette",
	pilotTemplate = "slow_tier4",
	shipType = "capital",

	experience = 43000,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier4",

	minCredits = 791,
	maxCredits = 1300,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun"},
	rebelFactionReward = -40,
	appearance = "rebel_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(corellian_corvette_tier4, "corellian_corvette_tier4")
