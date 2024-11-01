corellian_corvette_interior = ShipAgent:new {
	template = "corvette_interior",
	pilotTemplate = "slow_tier1",
	shipType = "capital",

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier1",

	minCredits = 791,
	maxCredits = 1300,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun"},
	imperialFactionReward = 100,
	rebelFactionReward = -200,
	interiorChassis = "corvette_interior_1",
	appearance = "rebel_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(corellian_corvette_interior, "corellian_corvette_interior")
